#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"
# include <bits/stdc++.h>

using namespace std::chrono_literals;

class DiffDriveNode : public rclcpp::Node {
public:

    //public変数を宣言
    std::string type_;
    std::double_t rad_;
    std::double_t dis_;

    //cmd_velからモータの制御値を計算
    void diffDrive(float cmd[2],float lx,float az){ //cmd[0]:右輪rps,cmd[1]:左輪rps,lx:m/s,az:rad/s

        //線形速度と回転速度の加算
        cmd[0] = (lx + dis_*az/2)/(2.0*M_PI*rad_);
        cmd[1] = (lx - dis_*az/2)/(2.0*M_PI*rad_);
        
    }

    DiffDriveNode() : Node("diff_drive_node") {
        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("wheel_radious", -1.0);
        declare_parameter("wheel_distance", -1.0);

        //パラメータの取得
        type_ = get_parameter("robot_type").as_string();
        rad_ = get_parameter("wheel_radious").as_double();
        dis_ = get_parameter("wheel_distance").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type_.c_str());
        RCLCPP_INFO(this->get_logger(), "wheel radious:%f\r\n",rad_);
        RCLCPP_INFO(this->get_logger(), "wheel distance:%f\r\n",dis_);
        
        //通信周りの記述
        publisher_ = this->create_publisher<drive_msgs::msg::DiffDrive>("cmd_motor", 10);

        auto topic_callback = [this](const geometry_msgs::msg::Twist &msg) -> void {

            auto message = drive_msgs::msg::DiffDrive();
            float ans[] = {0,0}; //ans[0]:右輪rps,ans[1]:左輪rps
            diffDrive(ans, msg.linear.x, msg.angular.z); //(配列のポインタ渡し,x軸方向の速度m/s,z軸回りの角速度rad/s)

            message.name = "differencial drive";
            message.m1 = ans[0];
            message.m2 = ans[1];

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
    rclcpp::spin(std::make_shared<DiffDriveNode>());
    rclcpp::shutdown();
    return 0;
}