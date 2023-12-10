// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_test_msgs:msg/AddThreeInts.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__STRUCT_H_
#define CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AddThreeInts in the package custom_test_msgs.
typedef struct custom_test_msgs__msg__AddThreeInts
{
  int64_t num;
} custom_test_msgs__msg__AddThreeInts;

// Struct for a sequence of custom_test_msgs__msg__AddThreeInts.
typedef struct custom_test_msgs__msg__AddThreeInts__Sequence
{
  custom_test_msgs__msg__AddThreeInts * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_test_msgs__msg__AddThreeInts__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__STRUCT_H_
