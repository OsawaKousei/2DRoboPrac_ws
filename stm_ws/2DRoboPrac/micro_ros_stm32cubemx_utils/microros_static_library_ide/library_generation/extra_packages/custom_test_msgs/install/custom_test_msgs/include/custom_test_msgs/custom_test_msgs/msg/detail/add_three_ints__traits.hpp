// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from custom_test_msgs:msg/AddThreeInts.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__TRAITS_HPP_
#define CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "custom_test_msgs/msg/detail/add_three_ints__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace custom_test_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AddThreeInts & msg,
  std::ostream & out)
{
  out << "{";
  // member: num
  {
    out << "num: ";
    rosidl_generator_traits::value_to_yaml(msg.num, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AddThreeInts & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num: ";
    rosidl_generator_traits::value_to_yaml(msg.num, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AddThreeInts & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace custom_test_msgs

namespace rosidl_generator_traits
{

[[deprecated("use custom_test_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const custom_test_msgs::msg::AddThreeInts & msg,
  std::ostream & out, size_t indentation = 0)
{
  custom_test_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use custom_test_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const custom_test_msgs::msg::AddThreeInts & msg)
{
  return custom_test_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<custom_test_msgs::msg::AddThreeInts>()
{
  return "custom_test_msgs::msg::AddThreeInts";
}

template<>
inline const char * name<custom_test_msgs::msg::AddThreeInts>()
{
  return "custom_test_msgs/msg/AddThreeInts";
}

template<>
struct has_fixed_size<custom_test_msgs::msg::AddThreeInts>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<custom_test_msgs::msg::AddThreeInts>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<custom_test_msgs::msg::AddThreeInts>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__TRAITS_HPP_
