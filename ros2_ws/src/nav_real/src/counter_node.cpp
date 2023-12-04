#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "string"
#include "iostream"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "geometry_msgs/msg/pose_with_covariance_stamped.hpp"


using namespace std::chrono_literals;

class CounterNode : public rclcpp::Node {
public:

    int count = 0;

    CounterNode() : Node("counter_node") {
        
        publisher_ = this->create_publisher<std_msgs::msg::String>("counts", 10);

        auto publish_msg_callback = [this]() -> void {
            auto message = std_msgs::msg::String();
            message.data = std::to_string(count);

            RCLCPP_INFO(this->get_logger(), "count:%d\r\n",count);

            count = 0;

            this->publisher_->publish(message); 
        }; 


        timer_ = this->create_wall_timer(1000ms, publish_msg_callback);

        auto topic_callback = [this](const std_msgs::msg::String &msg) -> void {
            count ++;
        }; 

        auto sensor_callback = [this](const sensor_msgs::msg::LaserScan &msg) -> void {
                //count ++;
            };

        auto amcl_callback = [this](const geometry_msgs::msg::PoseWithCovarianceStamped &msg) -> void {
                count ++;
            };

        subscription_ = this->create_subscription<std_msgs::msg::String>
                ("practice_topic", 10, topic_callback);

        sensorsub_ = this->create_subscription<sensor_msgs::msg::LaserScan>
                ("/scan", 10, sensor_callback);
        
        amclsub_ = this->create_subscription<geometry_msgs::msg::PoseWithCovarianceStamped>
                ("/amcl_pose", 10, amcl_callback);
            
    }
private:
    // 上記の動作に必要なprivateメンバ
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr sensorsub_;
    rclcpp::Subscription<geometry_msgs::msg::PoseWithCovarianceStamped>::SharedPtr amclsub_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CounterNode>());
    rclcpp::shutdown();
    return 0;

}