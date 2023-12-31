#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

using namespace std::chrono_literals;

class LidarNode : public rclcpp::Node {
public:
    LidarNode() : Node("lidar_node") {
        
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

        auto topic_callback = [this](const sensor_msgs::msg::LaserScan &msg) -> void {

            auto message = geometry_msgs::msg::Twist();

            bool allMore = true;

            for (int i = 0; i < (int)sizeof(msg.ranges); i++)
            {
                if (msg.ranges[i] < 0.5)
                {
                allMore = false;
                RCLCPP_INFO(this->get_logger(), "detect:%f\r\n", msg.ranges[i]);
                break;
                }
            }
            if (allMore) //if all bigger than one
            {
                message.linear.x = -1;
                message.angular.z = 0;
            }
            else
            {   
                message.linear.x = 0;
                message.angular.z = 1;
            }

            this->publisher_->publish(message);
        }; 

        subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>
                ("/scan", 10, topic_callback);

    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<LidarNode>());
    rclcpp::shutdown();
    return 0;
}