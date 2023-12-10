// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from drive_pkg:msg/DiffDrive.idl
// generated code does not contain a copyright notice

#ifndef DRIVE_PKG__MSG__DETAIL__DIFF_DRIVE__STRUCT_H_
#define DRIVE_PKG__MSG__DETAIL__DIFF_DRIVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/DiffDrive in the package drive_pkg.
typedef struct drive_pkg__msg__DiffDrive
{
  rosidl_runtime_c__String name;
  double m1;
  double m2;
} drive_pkg__msg__DiffDrive;

// Struct for a sequence of drive_pkg__msg__DiffDrive.
typedef struct drive_pkg__msg__DiffDrive__Sequence
{
  drive_pkg__msg__DiffDrive * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} drive_pkg__msg__DiffDrive__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DRIVE_PKG__MSG__DETAIL__DIFF_DRIVE__STRUCT_H_
