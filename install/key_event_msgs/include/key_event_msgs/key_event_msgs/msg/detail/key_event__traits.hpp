// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice

#ifndef KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__TRAITS_HPP_
#define KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "key_event_msgs/msg/detail/key_event__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace key_event_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const KeyEvent & msg,
  std::ostream & out)
{
  out << "{";
  // member: key
  {
    out << "key: ";
    rosidl_generator_traits::value_to_yaml(msg.key, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const KeyEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "key: ";
    rosidl_generator_traits::value_to_yaml(msg.key, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const KeyEvent & msg, bool use_flow_style = false)
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

}  // namespace key_event_msgs

namespace rosidl_generator_traits
{

[[deprecated("use key_event_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const key_event_msgs::msg::KeyEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  key_event_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use key_event_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const key_event_msgs::msg::KeyEvent & msg)
{
  return key_event_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<key_event_msgs::msg::KeyEvent>()
{
  return "key_event_msgs::msg::KeyEvent";
}

template<>
inline const char * name<key_event_msgs::msg::KeyEvent>()
{
  return "key_event_msgs/msg/KeyEvent";
}

template<>
struct has_fixed_size<key_event_msgs::msg::KeyEvent>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<key_event_msgs::msg::KeyEvent>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<key_event_msgs::msg::KeyEvent>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__TRAITS_HPP_
