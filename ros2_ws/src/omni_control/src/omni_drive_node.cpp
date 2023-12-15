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

    //パラメータ保存用
    std::string type; //ロボットの種類
    std::double_t rad; //車輪の半径 
    std::double_t dis; //車輪ーロボットの中心間の距離

    //cmd_velからモータの制御値を計算
    void OmniDrive(float cmd[4],float lx,float ly, float az){ //cmd[0]:右前,cmd[1]:左前,cmd[2]:右後,cmd[3]:左後、lx:線形速度、az:回転速度

        //モーターの制御値を初期化
        for(int i = 0;i < 4;i++){
            cmd[i] = 0;
        }

        //モーターの制御値を計算
        //もし、lxが正なら、前輪は順転、後輪は逆転する
        if(lx > 0){
            cmd[0] = -1;
            cmd[1] = 1;
            cmd[2] = -1;
            cmd[3] = 1;
        }else if(lx < 0){ //もし、lxが負なら、前輪は逆転、後輪は順転する
            cmd[0] = 1;
            cmd[1] = -1;
            cmd[2] = 1;
            cmd[3] = -1;
        }

        //もし、lyが正なら、右輪は順転、左輪は逆転する
        if(ly > 0){
            cmd[0] = -1;
            cmd[1] = -1;
            cmd[2] = 1;
            cmd[3] = 1;
        }else if(ly < 0){ //もし、lyが負なら、右輪は逆転、左輪は順転する
            cmd[0] = 1;
            cmd[1] = 1;
            cmd[2] = -1;
            cmd[3] = -1;
        }

        //もし、azが正なら、全ての輪は順転する
        if(az > 0){
            cmd[0] = -1;
            cmd[1] = -1;
            cmd[2] = -1;
            cmd[3] = -1;
        }else if(az < 0){ //もし、azが負なら、全ての輪は逆転する
            cmd[0] = 1;
            cmd[1] = 1;
            cmd[2] = 1;
            cmd[3] = 1;
        }

    }

    OmniDriveNode() : Node("omni_drive_node") {
        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("wheel_radious", -1.0);
        declare_parameter("wheel_distance", -1.0);

        //パラメータの取得
        type = get_parameter("robot_type").as_string();
        rad = get_parameter("wheel_radious").as_double();
        dis = get_parameter("wheel_distance").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type.c_str());
        RCLCPP_INFO(this->get_logger(), "wheel radious:%f\r\n",rad);
        RCLCPP_INFO(this->get_logger(), "wheel distance:%f\r\n",dis);
        
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