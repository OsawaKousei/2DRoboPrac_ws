// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice

#ifndef KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__STRUCT_HPP_
#define KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__key_event_msgs__msg__KeyEvent __attribute__((deprecated))
#else
# define DEPRECATED__key_event_msgs__msg__KeyEvent __declspec(deprecated)
#endif

namespace key_event_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct KeyEvent_
{
  using Type = KeyEvent_<ContainerAllocator>;

  explicit KeyEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->key = 0;
    }
  }

  explicit KeyEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->key = 0;
    }
  }

  // field types and members
  using _key_type =
    uint8_t;
  _key_type key;

  // setters for named parameter idiom
  Type & set__key(
    const uint8_t & _arg)
  {
    this->key = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    key_event_msgs::msg::KeyEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const key_event_msgs::msg::KeyEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      key_event_msgs::msg::KeyEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      key_event_msgs::msg::KeyEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__key_event_msgs__msg__KeyEvent
    std::shared_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__key_event_msgs__msg__KeyEvent
    std::shared_ptr<key_event_msgs::msg::KeyEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const KeyEvent_ & other) const
  {
    if (this->key != other.key) {
      return false;
    }
    return true;
  }
  bool operator!=(const KeyEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct KeyEvent_

// alias to use template instance with default allocator
using KeyEvent =
  key_event_msgs::msg::KeyEvent_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace key_event_msgs

#endif  // KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__STRUCT_HPP_
