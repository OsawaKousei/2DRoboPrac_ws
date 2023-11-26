#include <rclcpp/rclcpp.hpp>
#include <rclcpp/qos.hpp>
#include <chrono>
#include "rclcpp_components/register_node_macro.hpp"
#include "key_event_nodes/key_hit_event_node.hpp"
#include "key_event_msgs/msg/key_event.hpp"

// for _kbhit
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


namespace key_event{

KeyHitEventNode::KeyHitEventNode(
  const rclcpp::NodeOptions& options
): KeyHitEventNode("",options){}


KeyHitEventNode::KeyHitEventNode(
  const std::string& name_space,
  const rclcpp::NodeOptions& options
): Node("key_hit_event_node", name_space, options){
  using namespace std::chrono_literals;

  declare_parameter("interval_ms", 100);
  auto interval_ms = this->get_parameter("interval_ms").as_int();

  _pub = this->create_publisher<key_event_msgs::msg::KeyEvent>("key_hit_event", rclcpp::QoS(10));
  _pub_timer = this-> create_wall_timer(
    std::chrono::milliseconds(interval_ms),
    std::bind(&KeyHitEventNode::_pub_callback,this)
  );
}

void KeyHitEventNode::_pub_callback(void){
  auto msg = std::make_shared<key_event_msgs::msg::KeyEvent>();
  if(_kbhit()){
    msg->key = getchar();
  }else{
    msg->key = '\0';
  }
//  RCLCPP_INFO(this->get_logger(), "key:%c", msg->key);
  _pub->publish(*msg);
}

int KeyHitEventNode::_kbhit(void){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

} // end of namespace

RCLCPP_COMPONENTS_REGISTER_NODE(key_event::KeyHitEventNode)

