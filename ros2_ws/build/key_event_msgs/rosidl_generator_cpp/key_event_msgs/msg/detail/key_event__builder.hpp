// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice

#ifndef KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__BUILDER_HPP_
#define KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "key_event_msgs/msg/detail/key_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace key_event_msgs
{

namespace msg
{

namespace builder
{

class Init_KeyEvent_key
{
public:
  Init_KeyEvent_key()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::key_event_msgs::msg::KeyEvent key(::key_event_msgs::msg::KeyEvent::_key_type arg)
  {
    msg_.key = std::move(arg);
    return std::move(msg_);
  }

private:
  ::key_event_msgs::msg::KeyEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::key_event_msgs::msg::KeyEvent>()
{
  return key_event_msgs::msg::builder::Init_KeyEvent_key();
}

}  // namespace key_event_msgs

#endif  // KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__BUILDER_HPP_
