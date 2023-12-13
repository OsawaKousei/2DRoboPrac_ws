#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
# include <bits/stdc++.h>
#include "sensor_msgs/msg/joy.hpp"

using namespace std::chrono_literals;

class JoyTransrateNode : public rclcpp::Node {
public:
    //public変数を宣言
    std::string type_;
    double lx_;
    double az_;

    JoyTransrateNode() : Node("joy_transrate_node") {

        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("max_lx", -1.0);
        declare_parameter("max_az", -1.0);

        //パラメータの取得
        type_ = get_parameter("robot_type").as_string();
        lx_ = get_parameter("max_lx").as_double();
        az_ = get_parameter("max_az").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type_.c_str());
        RCLCPP_INFO(this->get_logger(), "max lx:%f\r\n",lx_);
        RCLCPP_INFO(this->get_logger(), "max az:%f\r\n",az_);
  
        //通信周りの記述
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

        auto topic_callback = [this](const sensor_msgs::msg::Joy &msg) -> void {

            auto message = geometry_msgs::msg::Twist();

            //最大値に-1~1を乗算
            message.linear.x = lx_ * msg.axes[1];
            message.angular.z = az_ * msg.axes[0];

            //十字キーでの操作を上書き
            if(msg.axes[5] != 0){
                message.linear.x = lx_ * msg.axes[5];
            }
            if (msg.axes[4] != 0)
            {
                message.angular.z = az_ * msg.axes[4];
            }
            
            this->publisher_->publish(message);
        }; 

        subscription_ = this->create_subscription<sensor_msgs::msg::Joy>
                ("joy", 10, topic_callback);
    }
private:
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<JoyTransrateNode>());
    rclcpp::shutdown();
    return 0;
}