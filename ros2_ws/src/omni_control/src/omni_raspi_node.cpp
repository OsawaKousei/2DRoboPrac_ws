#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "drive_msgs/msg/omni.hpp"

using namespace std::chrono_literals;

class RaspiNode : public rclcpp::Node {
public:
    RaspiNode() : Node("raspi_node") {
        
        publisher_ = this->create_publisher<drive_msgs::msg::Omni>("/cmd_ras", 10);

        auto topic_callback = [this](const drive_msgs::msg::Omni &msg) -> void {

            auto message = drive_msgs::msg::Omni();

            message.name = msg.name;
            message.mbackright = msg.mbackright;
            message.mbackleft = msg.mbackleft;
            message.mfontright = msg.mfontright;
            message.mfrontleft = msg.mfrontleft;

            this->publisher_->publish(message);

            RCLCPP_INFO(this->get_logger(), "I'm hearing\r\n");
        }; 

        subscription_ = this->create_subscription<drive_msgs::msg::Omni>("/cmd_motor", 10,topic_callback);

    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<drive_msgs::msg::Omni>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<drive_msgs::msg::Omni>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RaspiNode>());
    rclcpp::shutdown();
    return 0;
}