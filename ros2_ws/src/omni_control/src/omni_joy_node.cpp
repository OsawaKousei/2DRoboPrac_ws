#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "sensor_msgs/msg/joy.hpp"

using namespace std::chrono_literals;

class OmniJoyNode : public rclcpp::Node {
public:
    //パラメータ保存用
    std::string type; //ロボットの種類
    double lx; //x方向の速度の最大値
    double ly; //y方向の速度の最大値
    double az; //z周りの角速度の最大値

    OmniJoyNode() : Node("omni_joy_node") {

        //使用するパラメータの宣言(param名,初期値)、小数点を入れないとint型になるので注意
        declare_parameter("robot_type", "default");
        declare_parameter("max_lx", -1.0);
        declare_parameter("max_ly", -1.0);
        declare_parameter("max_az", -1.0);

        //パラメータの取得
        type = get_parameter("robot_type").as_string();
        lx = get_parameter("max_lx").as_double();
        ly = get_parameter("max_ly").as_double();
        az = get_parameter("max_az").as_double();

        //パラメータの確認
        RCLCPP_INFO(this->get_logger(), "robot type:%s\r\n",type.c_str());
        RCLCPP_INFO(this->get_logger(), "max lx:%f\r\n",lx);
        RCLCPP_INFO(this->get_logger(), "max ly:%f\r\n",ly);
        RCLCPP_INFO(this->get_logger(), "max az:%f\r\n",az);
  
        //パブリッシャーの設定
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

        auto topic_callback = [this](const sensor_msgs::msg::Joy &msg) -> void {

            //twist型のメッセージを作成
            auto message = geometry_msgs::msg::Twist();

            //ジョイコンの入力を速度に変換
            message.linear.x = lx * msg.axes[1];
            message.linear.y = ly * msg.axes[0];

            //十字キーでの操作を上書き
            if(msg.axes[5] != 0){
                message.linear.x = lx * msg.axes[5];
            }
            if (msg.axes[4] != 0)
            {
                message.linear.y = ly * msg.axes[4];
            }
            
            //z軸周りの角速度を設定
            message.angular.z = az * msg.axes[2];

            //メッセージを送信
            this->publisher_->publish(message);
        }; 

        //ジョイコンの入力を受け取るトピックの設定
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
    rclcpp::spin(std::make_shared<OmniJoyNode>());
    rclcpp::shutdown();
    return 0;
}