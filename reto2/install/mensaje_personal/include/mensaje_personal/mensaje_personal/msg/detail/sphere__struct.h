// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mensaje_personal:msg/Sphere.idl
// generated code does not contain a copyright notice

#ifndef MENSAJE_PERSONAL__MSG__DETAIL__SPHERE__STRUCT_H_
#define MENSAJE_PERSONAL__MSG__DETAIL__SPHERE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'center'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/Sphere in the package mensaje_personal.
typedef struct mensaje_personal__msg__Sphere
{
  geometry_msgs__msg__Point center;
  double radius;
} mensaje_personal__msg__Sphere;

// Struct for a sequence of mensaje_personal__msg__Sphere.
typedef struct mensaje_personal__msg__Sphere__Sequence
{
  mensaje_personal__msg__Sphere * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mensaje_personal__msg__Sphere__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MENSAJE_PERSONAL__MSG__DETAIL__SPHERE__STRUCT_H_
