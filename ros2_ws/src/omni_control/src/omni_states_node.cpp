#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/omni.hpp"
#include "drive_msgs/msg/omni_enc.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "nav_msgs/msg/odometry.hpp"
#include <cmath>
#include "rclcpp/qos.hpp"

using namespace std::chrono_literals;

class OmniStatesNode : public rclcpp::Node {
public:

    //ロボットの種類
    std::string type;
    //車輪の半径
    std::double_t w_rad;
    //車輪-中心間距離
    std::double_t w_dis;
    //エンコーダの半径
    std::double_t e_rad;
    //回転エンコーダー-中心間距離
    std::double_t e_dis;

    //lxエンコーダの回転数
    float lx = 0;
    //azエンコーダの回転数
    float az = 0;
    //lxエンコーダの回転数の差分
    float lx_d = 0;
    //ロボットのx座標
    float x = 0;
    //ロボットのy座標
    float y = 0;
    //ロボットの向き(rad)
    float th = 0;

    //ロボットの姿勢を計算
    void calcPose(){
        //azはエンコーダーの回転数、enc2はエンコーダーの半径、enc2disはロボットの中心からエンコーダーまでの距離
        //azをラジアンに変換してロボットの姿勢を計算
        th = az/(e_dis);

        //xはロボットのx座標、yはロボットのy座標
        //thはロボットの向き
        //x,yからthの向きにx_dだけ進んだ座標を計算
        x = x + lx_d * cos(th);
        y = y + lx_d * sin(th);
    }

    OmniStatesNode() : Node("omni_states_node") {
        //パラメータの宣言
        declare_parameter("robot_type", "default");
        declare_parameter("wheel_radious", -1.0);
        declare_parameter("wheel_distance", -1.0);
        declare_parameter("enc_radious", -1.0);
        declare_parameter("enc_distance", -1.0);

        //パラメータの取得
        type = get_parameter("robot_type").as_string();
        w_rad= get_parameter("wheel_radious").as_double();
        w_dis = get_parameter("wheel_distance").as_double();
        e_rad = get_parameter("enc_radious").as_double();
        e_dis = get_parameter("enc_distance").as_double();

        //パラメータの表示
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type.c_str());
        RCLCPP_INFO(this->get_logger(), "wheel radious:%f\r\n",w_rad);
        RCLCPP_INFO(this->get_logger(), "wheel distance:%f\r\n",w_dis);
        RCLCPP_INFO(this->get_logger(), "enc radious:%f\r\n",e_rad);
        RCLCPP_INFO(this->get_logger(), "enc distance:%f\r\n",e_dis);

        //publisherの作成
        jointpub_ = this->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
        odompub_ = this->create_publisher<nav_msgs::msg::Odometry>("odom", 10);
        //tfをpublishするためのtf_broadcasterを作成
        tf_broadcaster_ =std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        //joint statesをpublish
        auto joint_publisher = [this](float m1enc, float m2enc) -> void {
            //joint statesを作成
            auto joint = sensor_msgs::msg::JointState();

            //joint statesの値を設定
            joint.header.stamp = this->get_clock()->now();
            joint.name.resize(6);
            joint.name[0] = "base_joint";
            joint.name[1] = "lidar_joint";
            joint.name[2] = "wheel_left_joint";
            joint.name[3] = "wheel_right_joint";
            joint.name[4] = "caster_back_right_joint";
            joint.name[5] = "caster_back_left_joint";
            joint.position.resize(6);
            joint.position[0] = 0.0;
            joint.position[1] = 0.0;
            //m1encは右輪エンコーダーの回転数、m2encは左輪エンコーダの回転数
            //rad_は右輪と左輪の半径
            //m1encとm2encから右輪と左輪の角度を計算
            joint.position[2] = m1enc*2*M_PI*w_rad;
            joint.position[3] = m2enc*2*M_PI*w_rad;
            joint.position[4] = 0.0;
            joint.position[5] = 0.0;

            //joint statesをpublish
            this->jointpub_->publish(joint);
        };

        //odomをpublish
        auto odom_publisher = [this]() -> void {
            auto odom = nav_msgs::msg::Odometry();

            odom.header.stamp = this->get_clock()->now();
            odom.header.frame_id = "/odom";

            odom.child_frame_id = "base_footprint";

            odom.pose.pose.position.x = x;
            odom.pose.pose.position.y = y;
            odom.pose.pose.position.z = 0;

            //ロボットの向きをクォータニオンで表現
            tf2::Quaternion r;
            r.setRPY(0, 0, th);

            //クォータニオンをodomに設定
            odom.pose.pose.orientation.x = r.x();
            odom.pose.pose.orientation.y = r.y();
            odom.pose.pose.orientation.z = r.z();
            odom.pose.pose.orientation.w = r.w();

            //twistを設定
            odom.twist.twist.linear.x = 0;
            odom.twist.twist.linear.y = 0;
            odom.twist.twist.linear.z = 0;
            odom.twist.twist.angular.x = 0;
            odom.twist.twist.angular.y = 0;
            odom.twist.twist.angular.z = 0;

            //odomをpublish
            this->odompub_->publish(odom);
        };

        auto tf_publisher = [this]() -> void {
            auto tf = geometry_msgs::msg::TransformStamped();

            tf.header.stamp = this->get_clock()->now();
            tf.header.frame_id = "odom";
            tf.child_frame_id = "base_footprint";

            tf.transform.translation.x = x;
            tf.transform.translation.y = y;
            tf.transform.translation.z = 0;

            tf2::Quaternion q;
            q.setRPY(0, 0, th);

            tf.transform.rotation.x = q.x();
            tf.transform.rotation.y = q.y();
            tf.transform.rotation.z = q.z();
            tf.transform.rotation.w = q.w();

            //<geometry_msgs::msg::TransformStamped>をtfに変換してpublish
            tf_broadcaster_->sendTransform(tf);

            auto maptf = geometry_msgs::msg::TransformStamped();

            maptf.header.stamp = this->get_clock()->now();
            maptf.header.frame_id = "map";
            maptf.child_frame_id = "odom";

            maptf.transform.translation.x = 0;
            maptf.transform.translation.y = 0;
            maptf.transform.translation.z = 0;

            tf2::Quaternion p;
            p.setRPY(0, 0, 0);

            maptf.transform.rotation.x = p.x();
            maptf.transform.rotation.y = p.y();
            maptf.transform.rotation.z = p.z();
            maptf.transform.rotation.w = p.w();

            tf_broadcaster_->sendTransform(maptf);
        };

        //subscriptionのコールバック関数
        auto sub_callback = [this, joint_publisher]
            (const drive_msgs::msg::OmniEnc &msg) -> void {
            //joint statesをpublish
            //msg.m1encは右輪エンコーダーの回転数、msg.m2encは左輪エンコーダの回転数
            joint_publisher(msg.encfontright, msg.encfrontleft);

            //lxエンコーダの回転数の差分を計算
            lx_d = msg.enclx - lx;
            //エンコーダの値を更新
            lx = msg.enclx;
            az = msg.encadditional;
        }; 
        //subscriptionを作成
        subscription_ = this->create_subscription<drive_msgs::msg::OmniEnc>("enc_val",10,sub_callback);
        
        //timerのコールバック関数
        auto pub_callback = [this, odom_publisher,tf_publisher]() -> void {
            //ロボットの姿勢を計算
            calcPose();
            
            //odomをpublish
            odom_publisher();
            //tfをpublish
            tf_publisher();
        }; 
        
        //timerを作成
        timer_ = this->create_wall_timer(2ms, pub_callback);
    }
private:
    rclcpp::Subscription<drive_msgs::msg::OmniEnc>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr jointpub_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odompub_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_; 
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OmniStatesNode>());
    rclcpp::shutdown();
    return 0;
}