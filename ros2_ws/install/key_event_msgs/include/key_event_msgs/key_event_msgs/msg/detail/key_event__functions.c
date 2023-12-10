// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from key_event_msgs:msg/KeyEvent.idl
// generated code does not contain a copyright notice
#include "key_event_msgs/msg/detail/key_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
key_event_msgs__msg__KeyEvent__init(key_event_msgs__msg__KeyEvent * msg)
{
  if (!msg) {
    return false;
  }
  // key
  return true;
}

void
key_event_msgs__msg__KeyEvent__fini(key_event_msgs__msg__KeyEvent * msg)
{
  if (!msg) {
    return;
  }
  // key
}

bool
key_event_msgs__msg__KeyEvent__are_equal(const key_event_msgs__msg__KeyEvent * lhs, const key_event_msgs__msg__KeyEvent * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // key
  if (lhs->key != rhs->key) {
    return false;
  }
  return true;
}

bool
key_event_msgs__msg__KeyEvent__copy(
  const key_event_msgs__msg__KeyEvent * input,
  key_event_msgs__msg__KeyEvent * output)
{
  if (!input || !output) {
    return false;
  }
  // key
  output->key = input->key;
  return true;
}

key_event_msgs__msg__KeyEvent *
key_event_msgs__msg__KeyEvent__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  key_event_msgs__msg__KeyEvent * msg = (key_event_msgs__msg__KeyEvent *)allocator.allocate(sizeof(key_event_msgs__msg__KeyEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(key_event_msgs__msg__KeyEvent));
  bool success = key_event_msgs__msg__KeyEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
key_event_msgs__msg__KeyEvent__destroy(key_event_msgs__msg__KeyEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    key_event_msgs__msg__KeyEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
key_event_msgs__msg__KeyEvent__Sequence__init(key_event_msgs__msg__KeyEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  key_event_msgs__msg__KeyEvent * data = NULL;

  if (size) {
    data = (key_event_msgs__msg__KeyEvent *)allocator.zero_allocate(size, sizeof(key_event_msgs__msg__KeyEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = key_event_msgs__msg__KeyEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        key_event_msgs__msg__KeyEvent__fini(&data[i - 1]);
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
key_event_msgs__msg__KeyEvent__Sequence__fini(key_event_msgs__msg__KeyEvent__Sequence * array)
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
      key_event_msgs__msg__KeyEvent__fini(&array->data[i]);
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

key_event_msgs__msg__KeyEvent__Sequence *
key_event_msgs__msg__KeyEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  key_event_msgs__msg__KeyEvent__Sequence * array = (key_event_msgs__msg__KeyEvent__Sequence *)allocator.allocate(sizeof(key_event_msgs__msg__KeyEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = key_event_msgs__msg__KeyEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
key_event_msgs__msg__KeyEvent__Sequence__destroy(key_event_msgs__msg__KeyEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    key_event_msgs__msg__KeyEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
key_event_msgs__msg__KeyEvent__Sequence__are_equal(const key_event_msgs__msg__KeyEvent__Sequence * lhs, const key_event_msgs__msg__KeyEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!key_event_msgs__msg__KeyEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
key_event_msgs__msg__KeyEvent__Sequence__copy(
  const key_event_msgs__msg__KeyEvent__Sequence * input,
  key_event_msgs__msg__KeyEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(key_event_msgs__msg__KeyEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    key_event_msgs__msg__KeyEvent * data =
      (key_event_msgs__msg__KeyEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!key_event_msgs__msg__KeyEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          key_event_msgs__msg__KeyEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!key_event_msgs__msg__KeyEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
