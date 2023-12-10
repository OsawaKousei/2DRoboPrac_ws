// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from custom_test_msgs:msg/AddThreeInts.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__FUNCTIONS_H_
#define CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "custom_test_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "custom_test_msgs/msg/detail/add_three_ints__struct.h"

/// Initialize msg/AddThreeInts message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * custom_test_msgs__msg__AddThreeInts
 * )) before or use
 * custom_test_msgs__msg__AddThreeInts__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
bool
custom_test_msgs__msg__AddThreeInts__init(custom_test_msgs__msg__AddThreeInts * msg);

/// Finalize msg/AddThreeInts message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
void
custom_test_msgs__msg__AddThreeInts__fini(custom_test_msgs__msg__AddThreeInts * msg);

/// Create msg/AddThreeInts message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * custom_test_msgs__msg__AddThreeInts__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
custom_test_msgs__msg__AddThreeInts *
custom_test_msgs__msg__AddThreeInts__create();

/// Destroy msg/AddThreeInts message.
/**
 * It calls
 * custom_test_msgs__msg__AddThreeInts__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
void
custom_test_msgs__msg__AddThreeInts__destroy(custom_test_msgs__msg__AddThreeInts * msg);

/// Check for msg/AddThreeInts message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
bool
custom_test_msgs__msg__AddThreeInts__are_equal(const custom_test_msgs__msg__AddThreeInts * lhs, const custom_test_msgs__msg__AddThreeInts * rhs);

/// Copy a msg/AddThreeInts message.
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
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
bool
custom_test_msgs__msg__AddThreeInts__copy(
  const custom_test_msgs__msg__AddThreeInts * input,
  custom_test_msgs__msg__AddThreeInts * output);

/// Initialize array of msg/AddThreeInts messages.
/**
 * It allocates the memory for the number of elements and calls
 * custom_test_msgs__msg__AddThreeInts__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
bool
custom_test_msgs__msg__AddThreeInts__Sequence__init(custom_test_msgs__msg__AddThreeInts__Sequence * array, size_t size);

/// Finalize array of msg/AddThreeInts messages.
/**
 * It calls
 * custom_test_msgs__msg__AddThreeInts__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
void
custom_test_msgs__msg__AddThreeInts__Sequence__fini(custom_test_msgs__msg__AddThreeInts__Sequence * array);

/// Create array of msg/AddThreeInts messages.
/**
 * It allocates the memory for the array and calls
 * custom_test_msgs__msg__AddThreeInts__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
custom_test_msgs__msg__AddThreeInts__Sequence *
custom_test_msgs__msg__AddThreeInts__Sequence__create(size_t size);

/// Destroy array of msg/AddThreeInts messages.
/**
 * It calls
 * custom_test_msgs__msg__AddThreeInts__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
void
custom_test_msgs__msg__AddThreeInts__Sequence__destroy(custom_test_msgs__msg__AddThreeInts__Sequence * array);

/// Check for msg/AddThreeInts message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
bool
custom_test_msgs__msg__AddThreeInts__Sequence__are_equal(const custom_test_msgs__msg__AddThreeInts__Sequence * lhs, const custom_test_msgs__msg__AddThreeInts__Sequence * rhs);

/// Copy an array of msg/AddThreeInts messages.
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
ROSIDL_GENERATOR_C_PUBLIC_custom_test_msgs
bool
custom_test_msgs__msg__AddThreeInts__Sequence__copy(
  const custom_test_msgs__msg__AddThreeInts__Sequence * input,
  custom_test_msgs__msg__AddThreeInts__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_TEST_MSGS__MSG__DETAIL__ADD_THREE_INTS__FUNCTIONS_H_
