// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_test_msgs:msg/AddThreeInts.idl
// generated code does not contain a copyright notice
#include "custom_test_msgs/msg/detail/add_three_ints__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
custom_test_msgs__msg__AddThreeInts__init(custom_test_msgs__msg__AddThreeInts * msg)
{
  if (!msg) {
    return false;
  }
  // num
  return true;
}

void
custom_test_msgs__msg__AddThreeInts__fini(custom_test_msgs__msg__AddThreeInts * msg)
{
  if (!msg) {
    return;
  }
  // num
}

bool
custom_test_msgs__msg__AddThreeInts__are_equal(const custom_test_msgs__msg__AddThreeInts * lhs, const custom_test_msgs__msg__AddThreeInts * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // num
  if (lhs->num != rhs->num) {
    return false;
  }
  return true;
}

bool
custom_test_msgs__msg__AddThreeInts__copy(
  const custom_test_msgs__msg__AddThreeInts * input,
  custom_test_msgs__msg__AddThreeInts * output)
{
  if (!input || !output) {
    return false;
  }
  // num
  output->num = input->num;
  return true;
}

custom_test_msgs__msg__AddThreeInts *
custom_test_msgs__msg__AddThreeInts__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_test_msgs__msg__AddThreeInts * msg = (custom_test_msgs__msg__AddThreeInts *)allocator.allocate(sizeof(custom_test_msgs__msg__AddThreeInts), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_test_msgs__msg__AddThreeInts));
  bool success = custom_test_msgs__msg__AddThreeInts__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
custom_test_msgs__msg__AddThreeInts__destroy(custom_test_msgs__msg__AddThreeInts * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    custom_test_msgs__msg__AddThreeInts__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
custom_test_msgs__msg__AddThreeInts__Sequence__init(custom_test_msgs__msg__AddThreeInts__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_test_msgs__msg__AddThreeInts * data = NULL;

  if (size) {
    data = (custom_test_msgs__msg__AddThreeInts *)allocator.zero_allocate(size, sizeof(custom_test_msgs__msg__AddThreeInts), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_test_msgs__msg__AddThreeInts__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_test_msgs__msg__AddThreeInts__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_test_msgs__msg__AddThreeInts__Sequence__fini(custom_test_msgs__msg__AddThreeInts__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_test_msgs__msg__AddThreeInts__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_test_msgs__msg__AddThreeInts__Sequence *
custom_test_msgs__msg__AddThreeInts__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  custom_test_msgs__msg__AddThreeInts__Sequence * array = (custom_test_msgs__msg__AddThreeInts__Sequence *)allocator.allocate(sizeof(custom_test_msgs__msg__AddThreeInts__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = custom_test_msgs__msg__AddThreeInts__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
custom_test_msgs__msg__AddThreeInts__Sequence__destroy(custom_test_msgs__msg__AddThreeInts__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    custom_test_msgs__msg__AddThreeInts__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
custom_test_msgs__msg__AddThreeInts__Sequence__are_equal(const custom_test_msgs__msg__AddThreeInts__Sequence * lhs, const custom_test_msgs__msg__AddThreeInts__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!custom_test_msgs__msg__AddThreeInts__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
custom_test_msgs__msg__AddThreeInts__Sequence__copy(
  const custom_test_msgs__msg__AddThreeInts__Sequence * input,
  custom_test_msgs__msg__AddThreeInts__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(custom_test_msgs__msg__AddThreeInts);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    custom_test_msgs__msg__AddThreeInts * data =
      (custom_test_msgs__msg__AddThreeInts *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!custom_test_msgs__msg__AddThreeInts__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          custom_test_msgs__msg__AddThreeInts__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!custom_test_msgs__msg__AddThreeInts__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
