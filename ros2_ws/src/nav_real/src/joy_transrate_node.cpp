#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
# include <bits/stdc++.h>
#include "sensor_msgs/msg/joy.hpp"

using namespace std::chrono_literals;

class JoyTransrateNode : public rclcpp::Node {
public:

    JoyTransrateNode() : Node("joy_transrate_node") {
  
        //通信周りの記述
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

        auto topic_callback = [this](const sensor_msgs::msg::Joy &msg) -> void {

            auto message = geometry_msgs::msg::Twist();

            message.linear.x = 0;
            message.angular.z = 0;

            if(msg.axes[5] > 0){
                message.linear.x = 1;
            }else if (msg.axes[5] < 0)
            {
                message.linear.x = -1;
            }

            if(msg.axes[4] > 0){
                message.angular.z = 1;
            }else if (msg.axes[4] < 0)
            {
                message.angular.z = -1;
            }
            
            this->publisher_->publish(message);
        }; 

        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>
                ("joy", 10, topic_callback);
    }
private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JoyTransrateNode>());
    rclcpp::shutdown();
    return 0;
}