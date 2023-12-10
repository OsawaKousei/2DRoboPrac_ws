#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "drive_msgs/msg/diff_drive.hpp"

using namespace std::chrono_literals;

class RaspiNode : public rclcpp::Node {
public:
    RaspiNode() : Node("raspi_node") {
        
        publisher_ = this->create_publisher<drive_msgs::msg::DiffDrive>("/cmd_ras", 10);

        auto topic_callback = [this](const drive_msgs::msg::DiffDrive &msg) -> void {

            auto message = drive_msgs::msg::DiffDrive();

            message.name = msg.name;
            message.m1 = msg.m1;
            message.m2 = msg.m2;

            this->publisher_->publish(message);

            RCLCPP_INFO(this->get_logger(), "I'm hearing\r\n");
        }; 

        subscription_ = this->create_subscription<drive_msgs::msg::DiffDrive>("/cmd_motor", 10,topic_callback);

    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<drive_msgs::msg::DiffDrive>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<drive_msgs::msg::DiffDrive>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RaspiNode>());
    rclcpp::shutdown();
    return 0;
}