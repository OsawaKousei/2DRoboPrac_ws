#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"
#include "drive_msgs/msg/diff_drive_enc.hpp"
#include "cmath"

using namespace std::chrono_literals;

class DammyEncorderNode : public rclcpp::Node {
public:

    //public変数を宣言
    std::string type_;
    std::double_t rad_;
    std::double_t dis_;
    std::double_t enc1;
    std::double_t enc2;
    std::double_t enc2dis;

    //モーターの速度司令保存用
    float cmdM[2] = {0,0};
    //ロボットの速度司令保存用
    float cmdV[2] = {0,0};
    //エンコーダの値保存用
    float enc[4] = {0,0,0,0};
    //エンコーダの値更新レート
    float rate = 2; //回/ms

    //cmd_motorからエンコーダの値を計算
    void diffEnc(){
        enc[0] = enc[0] + cmdM[0]/(1000/rate);
        enc[1] = enc[1] + cmdM[1]/(1000/rate);
        enc[2] = enc[2] +  cmdV[0]*(1000/rate)*(2*M_PI*enc1);
        enc[3] = enc[3] + cmdV[1]*(1000/rate)*enc2dis*(2*M_PI*enc2);
    }

    DammyEncorderNode() : Node("dammy_encorder_node") {
        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("wheel_radious", -1.0);
        declare_parameter("wheel_distance", -1.0);
        declare_parameter("lxenc_radious", -1.0);
        declare_parameter("azenc_radious", -1.0);
        declare_parameter("azenc_distance", -1.0);

        //パラメータの取得
        type_ = get_parameter("robot_type").as_string();
        rad_ = get_parameter("wheel_radious").as_double();
        dis_ = get_parameter("wheel_distance").as_double();
        enc1 = get_parameter("lxenc_radious").as_double();
        enc2 = get_parameter("azenc_radious").as_double();
        enc2dis = get_parameter("azenc_distance").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type_.c_str());
        RCLCPP_INFO(this->get_logger(), "wheel radious:%f\r\n",rad_);
        RCLCPP_INFO(this->get_logger(), "wheel distance:%f\r\n",dis_);
        RCLCPP_INFO(this->get_logger(), "lxenc_radious:%f\r\n",enc1);
        RCLCPP_INFO(this->get_logger(), "azenc_radious:%f\r\n",enc2);
        RCLCPP_INFO(this->get_logger(), "azenc_distnace:%f\r\n",enc2dis);
        
        //通信周りの記述
        publisher_ = this->create_publisher<drive_msgs::msg::DiffDriveEnc>("enc_val", 10);

        auto sub_callback = [this](const drive_msgs::msg::DiffDrive &msg) -> void {
            cmdM[0] = msg.m1;
            cmdM[1] = msg.m2;
        }; 

        subscription_ = this->create_subscription<drive_msgs::msg::DiffDrive>("cmd_motor", 10, sub_callback);

        auto cmd_callback = [this](const geometry_msgs::msg::Twist &msg) -> void {
            //ロボットの速度司令を代入
            cmdV[0] = msg.linear.x;
            cmdV[1] = msg.angular.z;
        }; 

        cmdsub_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_motor", 10, cmd_callback);

        auto tim_callback = [this]() -> void{
            auto message = drive_msgs::msg::DiffDriveEnc();
            diffEnc();

            message.name = "differencial drive";
            message.m1enc = enc[0];
            message.m2enc = enc[1];
            message.lxenc = enc[2];
            message.azenc = enc[3];

            this->publisher_->publish(message);
        };

        timer_ = this->create_wall_timer(2ms, tim_callback);
    }
private:
    rclcpp::Subscription<drive_msgs::msg::DiffDrive>::SharedPtr subscription_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmdsub_;
    rclcpp::Publisher<drive_msgs::msg::DiffDriveEnc>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DammyEncorderNode>());
    rclcpp::shutdown();
    return 0;
}