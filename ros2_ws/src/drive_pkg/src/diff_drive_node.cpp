#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_pkg/msg/diff_drive.hpp"

using namespace std::chrono_literals;

class DiffDriveNode : public rclcpp::Node {
    std::string type_;
    size_t rad_;
    size_t dis_;
public:
    DiffDriveNode() : Node("diff_drive_node") {
        
        publisher_ = this->create_publisher<drive_pkg::msg::DiffDrive>("cmd_motor", 10);

        auto topic_callback = [this](const geometry_msgs::msg::Twist &msg) -> void {
            auto message = drive_pkg::msg::DiffDrive();
            
            this->publisher_->publish(message);
        }; 

        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>
                ("cmd_vel", 10, topic_callback);

        auto publish_callback = [this]() -> void {
            RCLCPP_INFO(this->get_logger(), "type:%s\r\n",type_.c_str());
            RCLCPP_INFO(this->get_logger(), "type:%ld\r\n",rad_);
            RCLCPP_INFO(this->get_logger(), "type:%ld\r\n",dis_);
        }; 

        timer_ = this->create_wall_timer(1000ms, publish_callback);
    }
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<drive_pkg::msg::DiffDrive>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DiffDriveNode>());
    rclcpp::shutdown();
    return 0;
}