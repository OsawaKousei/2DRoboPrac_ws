// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice

#ifndef KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__STRUCT_H_
#define KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/KeyEvent in the package key_event_msgs.
typedef struct key_event_msgs__msg__KeyEvent
{
  uint8_t key;
} key_event_msgs__msg__KeyEvent;

// Struct for a sequence of key_event_msgs__msg__KeyEvent.
typedef struct key_event_msgs__msg__KeyEvent__Sequence
{
  key_event_msgs__msg__KeyEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} key_event_msgs__msg__KeyEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__STRUCT_H_
