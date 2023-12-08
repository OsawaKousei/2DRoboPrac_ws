#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
//#include "drive_pkg/msg/diff_drive.hpp"

using namespace std::chrono_literals;

class DiffDriveNode : public rclcpp::Node {
public:
    DiffDriveNode() : Node("diff_drive_node") {
        
        publisher_ = this->create_publisher<std_msgs::msg::String>("motor_vel", 10);

        
        auto topic_callback = [this](const std_msgs::msg::String &msg) -> void {
            RCLCPP_INFO(this->get_logger(), "I'm hearing");
        }; 

        subscription_ = this->create_subscription<std_msgs::msg::String>
                ("cmd_vel", 10, topic_callback);
    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DiffDriveNode>());
    rclcpp::shutdown();
    return 0;
}