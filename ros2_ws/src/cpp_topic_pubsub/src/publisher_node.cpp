#include <chrono>  
#include <memory>  
#include "rclcpp/rclcpp.hpp"  
#include "cpp_topic_pubsub/msg/practice_msg.hpp"  // msgのinclude
  
using namespace std::chrono_literals; // 500msとか書けるようにするため  
  
class PublisherNode : public rclcpp::Node {  
public:  
    PublisherNode() : Node("publisher_node") { // rclcpp::Nodeを継承してpublisher_nodeというNodeを作成  
        publisher_ = this->create_publisher<cpp_topic_pubsub::msg::PracticeMsg>("practice_topic", 10);  
        // Topicにpublishする為の設定
  
        auto publish_msg_callback = [this]() -> void {  
            auto message = cpp_topic_pubsub::msg::PracticeMsg();  
            message.name = "PortCharlot"; // 6500円のウイスキー (実在)  
            message.price = 6500;  
            message.product_type = cpp_topic_pubsub::msg::PracticeMsg::PRODUCT_TYPE_WHISKEY; 
            // ここまでmsgの代入  
            
            this->publisher_->publish(message); // publish  
        }; // messageをpublish(送信)するcallback関数  

        timer_ = this->create_wall_timer(500ms, publish_msg_callback); // 500msに一度callbackが呼ばれる  
    }  
private:
    // 上記の動作に必要なprivateメンバ  
    rclcpp::TimerBase::SharedPtr timer_;  
    rclcpp::Publisher<cpp_topic_pubsub::msg::PracticeMsg>::SharedPtr publisher_;  
};  
  
int main(int argc, char *argv[]) {  
    rclcpp::init(argc, argv);  
    rclcpp::spin(std::make_shared<PublisherNode>());  
    rclcpp::shutdown();  
    return 0;  
}