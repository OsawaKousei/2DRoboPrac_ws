// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "key_event_msgs/msg/detail/key_event__rosidl_typesupport_introspection_c.h"
#include "key_event_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "key_event_msgs/msg/detail/key_event__functions.h"
#include "key_event_msgs/msg/detail/key_event__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  key_event_msgs__msg__KeyEvent__init(message_memory);
}

void key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_fini_function(void * message_memory)
{
  key_event_msgs__msg__KeyEvent__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_member_array[1] = {
  {
    "key",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(key_event_msgs__msg__KeyEvent, key),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_members = {
  "key_event_msgs__msg",  // message namespace
  "KeyEvent",  // message name
  1,  // number of fields
  sizeof(key_event_msgs__msg__KeyEvent),
  key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_member_array,  // message members
  key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_init_function,  // function to initialize message memory (memory has to be allocated)
  key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_type_support_handle = {
  0,
  &key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_key_event_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, key_event_msgs, msg, KeyEvent)() {
  if (!key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_type_support_handle.typesupport_identifier) {
    key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &key_event_msgs__msg__KeyEvent__rosidl_typesupport_introspection_c__KeyEvent_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
