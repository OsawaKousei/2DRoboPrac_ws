#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class TestNode : public rclcpp::Node {
public:
    TestNode() : Node("test_node") {
        
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/diff_drive/cmd_vel", 10);

        auto publish_msg_callback = [this]() -> void {
            auto message = geometry_msgs::msg::Twist();
            message.linear.x = 10;
            message.angular.z = 0;

            this->publisher_->publish(message);  // publishする
        }; 
        timer_ = this->create_wall_timer(500ms, publish_msg_callback);

        auto topic_callback = [this](const std_msgs::msg::String &msg) -> void {

            RCLCPP_INFO(this->get_logger(), "catch:%s\r\n", msg.data.c_str());
        }; 

        subscription_ = this->create_subscription<std_msgs::msg::String>
                ("practice_topic", 10, topic_callback);

    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TestNode>());
    rclcpp::shutdown();
    return 0;
}