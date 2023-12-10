// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice

#ifndef KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__FUNCTIONS_H_
#define KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "key_event_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "key_event_msgs/msg/detail/key_event__struct.h"

/// Initialize msg/KeyEvent message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * key_event_msgs__msg__KeyEvent
 * )) before or use
 * key_event_msgs__msg__KeyEvent__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
bool
key_event_msgs__msg__KeyEvent__init(key_event_msgs__msg__KeyEvent * msg);

/// Finalize msg/KeyEvent message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
void
key_event_msgs__msg__KeyEvent__fini(key_event_msgs__msg__KeyEvent * msg);

/// Create msg/KeyEvent message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * key_event_msgs__msg__KeyEvent__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
key_event_msgs__msg__KeyEvent *
key_event_msgs__msg__KeyEvent__create();

/// Destroy msg/KeyEvent message.
/**
 * It calls
 * key_event_msgs__msg__KeyEvent__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
void
key_event_msgs__msg__KeyEvent__destroy(key_event_msgs__msg__KeyEvent * msg);

/// Check for msg/KeyEvent message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
bool
key_event_msgs__msg__KeyEvent__are_equal(const key_event_msgs__msg__KeyEvent * lhs, const key_event_msgs__msg__KeyEvent * rhs);

/// Copy a msg/KeyEvent message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
bool
key_event_msgs__msg__KeyEvent__copy(
  const key_event_msgs__msg__KeyEvent * input,
  key_event_msgs__msg__KeyEvent * output);

/// Initialize array of msg/KeyEvent messages.
/**
 * It allocates the memory for the number of elements and calls
 * key_event_msgs__msg__KeyEvent__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
bool
key_event_msgs__msg__KeyEvent__Sequence__init(key_event_msgs__msg__KeyEvent__Sequence * array, size_t size);

/// Finalize array of msg/KeyEvent messages.
/**
 * It calls
 * key_event_msgs__msg__KeyEvent__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
void
key_event_msgs__msg__KeyEvent__Sequence__fini(key_event_msgs__msg__KeyEvent__Sequence * array);

/// Create array of msg/KeyEvent messages.
/**
 * It allocates the memory for the array and calls
 * key_event_msgs__msg__KeyEvent__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
key_event_msgs__msg__KeyEvent__Sequence *
key_event_msgs__msg__KeyEvent__Sequence__create(size_t size);

/// Destroy array of msg/KeyEvent messages.
/**
 * It calls
 * key_event_msgs__msg__KeyEvent__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
void
key_event_msgs__msg__KeyEvent__Sequence__destroy(key_event_msgs__msg__KeyEvent__Sequence * array);

/// Check for msg/KeyEvent message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
bool
key_event_msgs__msg__KeyEvent__Sequence__are_equal(const key_event_msgs__msg__KeyEvent__Sequence * lhs, const key_event_msgs__msg__KeyEvent__Sequence * rhs);

/// Copy an array of msg/KeyEvent messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_key_event_msgs
bool
key_event_msgs__msg__KeyEvent__Sequence__copy(
  const key_event_msgs__msg__KeyEvent__Sequence * input,
  key_event_msgs__msg__KeyEvent__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // KEY_EVENT_MSGS__MSG__DETAIL__KEY_EVENT__FUNCTIONS_H_
