// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from drive_msgs:msg/DiffDrive.idl
// generated code does not contain a copyright notice

#ifndef DRIVE_MSGS__MSG__DETAIL__DIFF_DRIVE__STRUCT_HPP_
#define DRIVE_MSGS__MSG__DETAIL__DIFF_DRIVE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__drive_msgs__msg__DiffDrive __attribute__((deprecated))
#else
# define DEPRECATED__drive_msgs__msg__DiffDrive __declspec(deprecated)
#endif

namespace drive_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct DiffDrive_
{
  using Type = DiffDrive_<ContainerAllocator>;

  explicit DiffDrive_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->m1 = 0.0;
      this->m2 = 0.0;
    }
  }

  explicit DiffDrive_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->m1 = 0.0;
      this->m2 = 0.0;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _m1_type =
    double;
  _m1_type m1;
  using _m2_type =
    double;
  _m2_type m2;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__m1(
    const double & _arg)
  {
    this->m1 = _arg;
    return *this;
  }
  Type & set__m2(
    const double & _arg)
  {
    this->m2 = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    drive_msgs::msg::DiffDrive_<ContainerAllocator> *;
  using ConstRawPtr =
    const drive_msgs::msg::DiffDrive_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      drive_msgs::msg::DiffDrive_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      drive_msgs::msg::DiffDrive_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__drive_msgs__msg__DiffDrive
    std::shared_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__drive_msgs__msg__DiffDrive
    std::shared_ptr<drive_msgs::msg::DiffDrive_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const DiffDrive_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->m1 != other.m1) {
      return false;
    }
    if (this->m2 != other.m2) {
      return false;
    }
    return true;
  }
  bool operator!=(const DiffDrive_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct DiffDrive_

// alias to use template instance with default allocator
using DiffDrive =
  drive_msgs::msg::DiffDrive_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace drive_msgs

#endif  // DRIVE_MSGS__MSG__DETAIL__DIFF_DRIVE__STRUCT_HPP_
