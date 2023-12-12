#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"
#include "drive_msgs/msg/diff_drive_enc.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "nav_msgs/msg/odometry.hpp"
# include <bits/stdc++.h>
#include "rclcpp/qos.hpp"

using namespace std::chrono_literals;

class StatesPubNode : public rclcpp::Node {
public:

    //public変数を宣言
    std::string type_;
    std::double_t rad_;
    std::double_t dis_;
    std::double_t enc1;
    std::double_t enc2;
    std::double_t enc2dis;

    StatesPubNode() : Node("states_pub_node") {
        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("wheel_radious", -1.0);
        declare_parameter("wheel_distance", -1.0);
        declare_parameter("lxenc_radious", -1.0);
        declare_parameter("azenc_radious", -1.0);
        declare_parameter("azenc_distance", -1.0);

        //パラメータの取得
        type_ = get_parameter("robot_type").as_string();
        rad_ = get_parameter("wheel_radious").as_double();
        dis_ = get_parameter("wheel_distance").as_double();
        enc1 = get_parameter("lxenc_radious").as_double();
        enc2 = get_parameter("azenc_radious").as_double();
        enc2dis = get_parameter("azenc_distance").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type_.c_str());
        RCLCPP_INFO(this->get_logger(), "wheel radious:%f\r\n",rad_);
        RCLCPP_INFO(this->get_logger(), "wheel distance:%f\r\n",dis_);
        RCLCPP_INFO(this->get_logger(), "lxenc_radious:%f\r\n",enc1);
        RCLCPP_INFO(this->get_logger(), "azenc_radious:%f\r\n",enc2);
        RCLCPP_INFO(this->get_logger(), "azenc_distnace:%f\r\n",enc2dis);

        //publisher
        jointpub_ = this->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
        odompub_ = this->create_publisher<nav_msgs::msg::Odometry>("odom", 10);
        //tf publishのためのbroadcasterS
        tf_broadcaster_ =std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        //joint statesをrobot state publisherに向けてpublish
        auto joint_publisher = [this]() -> void {
            auto joint = sensor_msgs::msg::JointState();

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
            joint.position[2] = 0.0;
            joint.position[3] = 0.0;
            joint.position[4] = 0.0;
            joint.position[5] = 0.0;

            this->jointpub_->publish(joint);
        };

        //odomをpublish
        auto odom_publisher = [this]() -> void {
            auto odom = nav_msgs::msg::Odometry();

            odom.header.stamp = this->get_clock()->now();
            odom.header.frame_id = "/odom";

            odom.child_frame_id = "base_footprint";

            odom.pose.pose.position.x = 0;
            odom.pose.pose.position.y = 0;
            odom.pose.pose.position.z = 0;

            //RPYをクオータニオンに変換
            tf2::Quaternion r;
            r.setRPY(0, 0, 0);

            odom.pose.pose.orientation.x = r.x();
            odom.pose.pose.orientation.y = r.y();
            odom.pose.pose.orientation.z = r.z();
            odom.pose.pose.orientation.w = r.w();

            odom.twist.twist.linear.x = 0;
            odom.twist.twist.linear.y = 0;
            odom.twist.twist.linear.z = 0;
            odom.twist.twist.angular.x = 0;
            odom.twist.twist.angular.y = 0;
            odom.twist.twist.angular.z = 0;

            this->odompub_->publish(odom);
        };

        auto tf_publisher = [this]() -> void {
            auto tf = geometry_msgs::msg::TransformStamped();

            tf.header.stamp = this->get_clock()->now();
            tf.header.frame_id = "odom";
            tf.child_frame_id = "base_footprint";

            tf.transform.translation.x = 0;
            tf.transform.translation.y = 0;
            tf.transform.translation.z = 0;

            tf2::Quaternion q;
            q.setRPY(0, 0, 0);

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

            maptf.transform.rotation.x = q.x();
            maptf.transform.rotation.y = q.y();
            maptf.transform.rotation.z = q.z();
            maptf.transform.rotation.w = q.w();

            tf_broadcaster_->sendTransform(maptf);
        };

        auto pub_callback = [this]() -> void {
            
        }; 
        
        timer_ = this->create_wall_timer(1000ms, pub_callback);

        auto sub_callback = [this, joint_publisher,odom_publisher,tf_publisher]
            (const drive_msgs::msg::DiffDriveEnc &msg) -> void {
            joint_publisher();
            odom_publisher();
            tf_publisher();
        }; 

        subscription_ = this->create_subscription<drive_msgs::msg::DiffDriveEnc>("enc_val",10,sub_callback);
    }
private:
    rclcpp::Subscription<drive_msgs::msg::DiffDriveEnc>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr jointpub_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odompub_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_; 
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StatesPubNode>());
    rclcpp::shutdown();
    return 0;
}