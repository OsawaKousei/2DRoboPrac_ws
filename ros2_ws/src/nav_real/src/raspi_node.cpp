#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

using namespace std::chrono_literals;

class RaspiNode : public rclcpp::Node {
public:
    RaspiNode() : Node("raspi_node") {
        
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_ras", 10);

        auto topic_callback = [this](const geometry_msgs::msg::Twist &msg) -> void {

            auto message = geometry_msgs::msg::Twist();

            message.angular = msg.angular;
            message.linear = msg.linear;

            this->publisher_->publish(message);

            RCLCPP_INFO(this->get_logger(), "I'm hearing\r\n");
        }; 

        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>("/cmd_vel", 10,topic_callback);

    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RaspiNode>());
    rclcpp::shutdown();
    return 0;
}