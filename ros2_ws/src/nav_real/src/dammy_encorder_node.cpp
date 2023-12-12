#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/diff_drive.hpp"
#include "drive_msgs/msg/diff_drive_enc.hpp"

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

    //cmd_motorからエンコーダの値を計算
    void diffEnc(float enc[4],float m1,float m2){

        //線形速度と回転速度の加算
        enc[0] = m1;
        enc[1] = m2;
        enc[2] = (m1+m2)/2*rad_/enc1;
        enc[3] = (m1-m2)/2*rad_/dis_*enc2dis/enc2;
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

        auto topic_callback = [this](const drive_msgs::msg::DiffDrive &msg) -> void {

            auto message = drive_msgs::msg::DiffDriveEnc();
            float ans[] = {0,0,0,0}; //ans[0]:右輪rps,ans[1]:左輪rps
            diffEnc(ans, msg.m1, msg.m2); //(配列のポインタ渡し

            message.name = "differencial drive";
            message.m1enc = ans[0];
            message.m2enc = ans[1];
            message.lxenc = ans[2];
            message.azenc = ans[3];

            this->publisher_->publish(message);
        }; 

        subscription_ = this->create_subscription<drive_msgs::msg::DiffDrive>
                ("cmd_motor", 10, topic_callback);
    }
private:
    rclcpp::Subscription<drive_msgs::msg::DiffDrive>::SharedPtr subscription_;
    rclcpp::Publisher<drive_msgs::msg::DiffDriveEnc>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DammyEncorderNode>());
    rclcpp::shutdown();
    return 0;
}