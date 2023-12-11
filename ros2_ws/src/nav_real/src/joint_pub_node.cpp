#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
# include <bits/stdc++.h>

using namespace std::chrono_literals;

class JointPubNode : public rclcpp::Node {
public:

    //public変数を宣言
    std::string type_;
    std::double_t rad_;
    std::double_t dis_;

    JointPubNode() : Node("joint_pub_node") {
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
        publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("cmd_motor", 10);

        auto pub_callback = [this]() -> void {

            auto message = sensor_msgs::msg::JointState();

            message.header.stamp = this->get_clock()->now();

            message.name.resize(6);
            message.name[0] = "base_joint";
            message.name[1] = "lidar_joint";
            message.name[2] = "wheel_left_joint";
            message.name[3] = "wheel_right_joint";
            message.name[4] = "caster_back_right_joint";
            message.name[5] = "caster_back_left_joint";

            message.position.resize(6);
            message.position[0] = 0.0;
            message.position[1] = 0.0;
            message.position[2] = 0.0;
            message.position[3] = 0.0;
            message.position[4] = 0.0;
            message.position[5] = 0.0;



            this->publisher_->publish(message);
        }; 

        timer_ = this->create_wall_timer(1000ms, pub_callback);
    }
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JointPubNode>());
    rclcpp::shutdown();
    return 0;
}