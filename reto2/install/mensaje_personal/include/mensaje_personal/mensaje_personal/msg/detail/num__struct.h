// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mensaje_personal:msg/Num.idl
// generated code does not contain a copyright notice

#ifndef MENSAJE_PERSONAL__MSG__DETAIL__NUM__STRUCT_H_
#define MENSAJE_PERSONAL__MSG__DETAIL__NUM__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Num in the package mensaje_personal.
typedef struct mensaje_personal__msg__Num
{
  int64_t type;
  float amplitude;
  float freq;
  float offset;
  float phase_shift;
  float time;
} mensaje_personal__msg__Num;

// Struct for a sequence of mensaje_personal__msg__Num.
typedef struct mensaje_personal__msg__Num__Sequence
{
  mensaje_personal__msg__Num * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mensaje_personal__msg__Num__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MENSAJE_PERSONAL__MSG__DETAIL__NUM__STRUCT_H_
