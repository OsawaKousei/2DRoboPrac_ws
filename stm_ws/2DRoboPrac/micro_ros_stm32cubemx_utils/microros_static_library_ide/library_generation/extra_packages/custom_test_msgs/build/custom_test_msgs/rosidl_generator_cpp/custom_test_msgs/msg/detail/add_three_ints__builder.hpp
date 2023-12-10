// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_test_msgs:msg/AddThreeInts.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__BUILDER_HPP_
#define CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "custom_test_msgs/msg/detail/add_three_ints__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace custom_test_msgs
{

namespace msg
{

namespace builder
{

class Init_AddThreeInts_num
{
public:
  Init_AddThreeInts_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_test_msgs::msg::AddThreeInts num(::custom_test_msgs::msg::AddThreeInts::_num_type arg)
  {
    msg_.num = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_test_msgs::msg::AddThreeInts msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_test_msgs::msg::AddThreeInts>()
{
  return custom_test_msgs::msg::builder::Init_AddThreeInts_num();
}

}  // namespace custom_test_msgs

#endif  // CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__BUILDER_HPP_
