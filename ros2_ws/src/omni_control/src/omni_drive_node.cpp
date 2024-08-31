#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "drive_msgs/msg/omni.hpp"
#include <cmath>

using namespace std::chrono_literals;

class OmniDriveNode : public rclcpp::Node {
public:

    //cmd_velからモータの制御値を計算
    void OmniDrive(float cmd[4],float lx,float ly, float az){ //cmd[0]:右前,cmd[1]:左前,cmd[2]:右後,cmd[3]:左後、lx:線形速度、az:回転速度

        //モーターの制御値を初期化
        for(int i = 0;i < 4;i++){
            cmd[i] = 0;
        }

        //モーターの制御値を計算
        //lx
        if(lx != 0){
            cmd[0] = -lx/sin(M_PI/4);
            cmd[1] = lx/sin(M_PI/4);
            cmd[2] = -lx/sin(M_PI/4);
            cmd[3] = lx/sin(M_PI/4);    
        }
        

        //ly
        if(ly != 0){
            cmd[0] = -ly/cos(M_PI/4);
            cmd[1] = -ly/cos(M_PI/4);
            cmd[2] = ly/cos(M_PI/4);
            cmd[3] = ly/cos(M_PI/4);
        }

        //az
        if(az != 0){
            cmd[0] = az;
            cmd[1] = az;
            cmd[2] = az;
            cmd[3] = az;
        }
    }

    OmniDriveNode() : Node("omni_drive_node") {

        //各モーターの速度司令を送るパブリッシャーの設定
        publisher_ = this->create_publisher<drive_msgs::msg::Omni>("cmd_motor", 10);

        //cmd_velを受け取ったらcmd_motorを送る
        auto topic_callback = [this](const geometry_msgs::msg::Twist &msg) -> void {

            //DiffDrive型のメッセージを作成
            auto message = drive_msgs::msg::Omni();
            //cmd_velからモータの制御値を計算
            float ans[] = {0,0,0,0};
            OmniDrive(ans, msg.linear.x, msg.linear.y, msg.angular.z);

            //モータの制御値をメッセージに格納
            message.name = "omni";
            message.mfontright = ans[0];
            message.mfrontleft = ans[1];
            message.mbackright = ans[2];
            message.mbackleft = ans[3];

            //メッセージを送信
            this->publisher_->publish(message);
        }; 

        //ロボットの速度司令を受け取るサブスクライバーの設定
        subscription_ = this->create_subscription<geometry_msgs::msg::Twist>
                ("cmd_vel", 10, topic_callback);
    }
private:
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr subscription_;
    rclcpp::Publisher<drive_msgs::msg::Omni>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OmniDriveNode>());
    rclcpp::shutdown();
    return 0;
}