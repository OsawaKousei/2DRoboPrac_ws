#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"

using namespace std::chrono_literals;

class SimpleDdNode : public rclcpp::Node {
public:

    SimpleDdNode() : Node("simple_dd_node") {
        
        //通信周りの記述
        publisher_ = this->create_publisher<drive_msgs::msg::DiffDrive>("cmd_motor", 10);

        auto topic_callback = [this](const geometry_msgs::msg::Twist &msg) -> void {

            auto message = drive_msgs::msg::DiffDrive();

            message.m1 = 0;
            message.m2 = 0;

            if(abs(msg.linear.x) >= abs(msg.angular.z)){ //abs():引数の絶対値を返す
                if(msg.linear.x > 0){
                    message.m1 = 1;
                    message.m2 =1;
                }else if (msg.linear.x < 0){
                    message.m1 = -1;
                    message.m2 = -1;
                }
            }else{
                if(msg.angular.z > 0){
                    message.m1 = 1;
                    message.m2 = 0;
                }else if (msg.angular.z < 0)
                {
                    message.m1 = 0;
                    message.m2 = 1;
                }
            }
            
            this->publisher_->publish(message);
        }; 

        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>
                ("cmd_vel", 10, topic_callback);
    }
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<drive_msgs::msg::DiffDrive>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SimpleDdNode>());
    rclcpp::shutdown();
    return 0;
}