// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_test_msgs:msg/AddThreeInts.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__STRUCT_HPP_
#define CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__custom_test_msgs__msg__AddThreeInts __attribute__((deprecated))
#else
# define DEPRECATED__custom_test_msgs__msg__AddThreeInts __declspec(deprecated)
#endif

namespace custom_test_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AddThreeInts_
{
  using Type = AddThreeInts_<ContainerAllocator>;

  explicit AddThreeInts_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num = 0ll;
    }
  }

  explicit AddThreeInts_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->num = 0ll;
    }
  }

  // field types and members
  using _num_type =
    int64_t;
  _num_type num;

  // setters for named parameter idiom
  Type & set__num(
    const int64_t & _arg)
  {
    this->num = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_test_msgs::msg::AddThreeInts_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_test_msgs::msg::AddThreeInts_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_test_msgs::msg::AddThreeInts_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_test_msgs::msg::AddThreeInts_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_test_msgs__msg__AddThreeInts
    std::shared_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_test_msgs__msg__AddThreeInts
    std::shared_ptr<custom_test_msgs::msg::AddThreeInts_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AddThreeInts_ & other) const
  {
    if (this->num != other.num) {
      return false;
    }
    return true;
  }
  bool operator!=(const AddThreeInts_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AddThreeInts_

// alias to use template instance with default allocator
using AddThreeInts =
  custom_test_msgs::msg::AddThreeInts_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_test_msgs

#endif  // CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__STRUCT_HPP_
