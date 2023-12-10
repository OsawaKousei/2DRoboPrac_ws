#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class TestPubNode : public rclcpp::Node {
public:

    TestPubNode() : Node("test_pub_node") {
        
        publisher_ = this->create_publisher<std_msgs::msg::String>("practice_topic", 10);

        auto publish_msg_callback = [this]() -> void {
            auto message = std_msgs::msg::String();

            message.data = "testting";

            this->publisher_->publish(message); 
        }; 

        timer_ = this->create_wall_timer(1ms, publish_msg_callback);
    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TestPubNode>());
    rclcpp::shutdown();
    return 0;
}