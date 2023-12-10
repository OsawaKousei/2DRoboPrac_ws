// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from drive_msgs:msg/DiffDrive.idl
// generated code does not contain a copyright notice

#ifndef DRIVE_MSGS__MSG__DETAIL__DIFF_DRIVE__BUILDER_HPP_
#define DRIVE_MSGS__MSG__DETAIL__DIFF_DRIVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "drive_msgs/msg/detail/diff_drive__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace drive_msgs
{

namespace msg
{

namespace builder
{

class Init_DiffDrive_m2
{
public:
  explicit Init_DiffDrive_m2(::drive_msgs::msg::DiffDrive & msg)
  : msg_(msg)
  {}
  ::drive_msgs::msg::DiffDrive m2(::drive_msgs::msg::DiffDrive::_m2_type arg)
  {
    msg_.m2 = std::move(arg);
    return std::move(msg_);
  }

private:
  ::drive_msgs::msg::DiffDrive msg_;
};

class Init_DiffDrive_m1
{
public:
  explicit Init_DiffDrive_m1(::drive_msgs::msg::DiffDrive & msg)
  : msg_(msg)
  {}
  Init_DiffDrive_m2 m1(::drive_msgs::msg::DiffDrive::_m1_type arg)
  {
    msg_.m1 = std::move(arg);
    return Init_DiffDrive_m2(msg_);
  }

private:
  ::drive_msgs::msg::DiffDrive msg_;
};

class Init_DiffDrive_name
{
public:
  Init_DiffDrive_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DiffDrive_m1 name(::drive_msgs::msg::DiffDrive::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_DiffDrive_m1(msg_);
  }

private:
  ::drive_msgs::msg::DiffDrive msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::drive_msgs::msg::DiffDrive>()
{
  return drive_msgs::msg::builder::Init_DiffDrive_name();
}

}  // namespace drive_msgs

#endif  // DRIVE_MSGS__MSG__DETAIL__DIFF_DRIVE__BUILDER_HPP_
