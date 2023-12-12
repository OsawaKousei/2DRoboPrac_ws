#include <functional>
#include <memory>
#include <sstream>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "tf2_msgs/msg/tf_message.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "nav_msgs/msg/odometry.hpp"
# include <bits/stdc++.h>

using namespace std::chrono_literals;

class StatesPubNode : public rclcpp::Node {
public:

    //public変数を宣言
    std::string type_;
    std::double_t rad_;
    std::double_t dis_;

    StatesPubNode() : Node("joint_pub_node") {
        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("wheel_radious", -1.0);
        declare_parameter("wheel_distance", -1.0);

        //パラメータの取得
        type_ = get_parameter("robot_type").as_string();
        rad_ = get_parameter("wheel_radious").as_double();
        dis_ = get_parameter("wheel_distance").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type_.c_str());
        RCLCPP_INFO(this->get_logger(), "wheel radious:%f\r\n",rad_);
        RCLCPP_INFO(this->get_logger(), "wheel distance:%f\r\n",dis_);
        
        //通信周りの記述
        jointpub_ = this->create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
        odompub_ = this->create_publisher<nav_msgs::msg::Odometry>("odom",10);
        tfpub_ = this->create_publisher<tf2_msgs::msg::TFMessage>("tf",10);

        tf_broadcaster_ =std::make_unique<tf2_ros::TransformBroadcaster>(*this);

        auto pub_callback = [this]() -> void {

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

            auto odom = nav_msgs::msg::Odometry();

            odom.header.stamp = this->get_clock()->now();
            odom.header.frame_id = "/odom";

            odom.child_frame_id = "base_footprint";

            odom.pose.pose.position.x = 0;
            odom.pose.pose.position.y = 0;
            odom.pose.pose.position.z = 0;
            odom.pose.pose.orientation.x = 0;
            odom.pose.pose.orientation.y = 0;
            odom.pose.pose.orientation.z = 0;
            odom.pose.pose.orientation.w = 0;

            odom.twist.twist.linear.x = 0;
            odom.twist.twist.linear.y = 0;
            odom.twist.twist.linear.z = 0;
            odom.twist.twist.angular.x = 0;
            odom.twist.twist.angular.y = 0;
            odom.twist.twist.angular.z = 0;

            this->odompub_->publish(odom);

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

            tf_broadcaster_->sendTransform(tf);
        }; 

        timer_ = this->create_wall_timer(1.25ms, pub_callback);
    }
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr jointpub_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odompub_;
    rclcpp::Publisher<tf2_msgs::msg::TFMessage>::SharedPtr tfpub_;
    std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StatesPubNode>());
    rclcpp::shutdown();
    return 0;
}