// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from mensaje_personal:msg/Num.idl
// generated code does not contain a copyright notice

#ifndef MENSAJE_PERSONAL__MSG__DETAIL__NUM__STRUCT_HPP_
#define MENSAJE_PERSONAL__MSG__DETAIL__NUM__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__mensaje_personal__msg__Num __attribute__((deprecated))
#else
# define DEPRECATED__mensaje_personal__msg__Num __declspec(deprecated)
#endif

namespace mensaje_personal
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Num_
{
  using Type = Num_<ContainerAllocator>;

  explicit Num_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0ll;
      this->amplitude = 0.0f;
      this->freq = 0.0f;
      this->offset = 0.0f;
      this->phase_shift = 0.0f;
      this->time = 0.0f;
    }
  }

  explicit Num_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0ll;
      this->amplitude = 0.0f;
      this->freq = 0.0f;
      this->offset = 0.0f;
      this->phase_shift = 0.0f;
      this->time = 0.0f;
    }
  }

  // field types and members
  using _type_type =
    int64_t;
  _type_type type;
  using _amplitude_type =
    float;
  _amplitude_type amplitude;
  using _freq_type =
    float;
  _freq_type freq;
  using _offset_type =
    float;
  _offset_type offset;
  using _phase_shift_type =
    float;
  _phase_shift_type phase_shift;
  using _time_type =
    float;
  _time_type time;

  // setters for named parameter idiom
  Type & set__type(
    const int64_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__amplitude(
    const float & _arg)
  {
    this->amplitude = _arg;
    return *this;
  }
  Type & set__freq(
    const float & _arg)
  {
    this->freq = _arg;
    return *this;
  }
  Type & set__offset(
    const float & _arg)
  {
    this->offset = _arg;
    return *this;
  }
  Type & set__phase_shift(
    const float & _arg)
  {
    this->phase_shift = _arg;
    return *this;
  }
  Type & set__time(
    const float & _arg)
  {
    this->time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    mensaje_personal::msg::Num_<ContainerAllocator> *;
  using ConstRawPtr =
    const mensaje_personal::msg::Num_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<mensaje_personal::msg::Num_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<mensaje_personal::msg::Num_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      mensaje_personal::msg::Num_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<mensaje_personal::msg::Num_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      mensaje_personal::msg::Num_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<mensaje_personal::msg::Num_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<mensaje_personal::msg::Num_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<mensaje_personal::msg::Num_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__mensaje_personal__msg__Num
    std::shared_ptr<mensaje_personal::msg::Num_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__mensaje_personal__msg__Num
    std::shared_ptr<mensaje_personal::msg::Num_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Num_ & other) const
  {
    if (this->type != other.type) {
      return false;
    }
    if (this->amplitude != other.amplitude) {
      return false;
    }
    if (this->freq != other.freq) {
      return false;
    }
    if (this->offset != other.offset) {
      return false;
    }
    if (this->phase_shift != other.phase_shift) {
      return false;
    }
    if (this->time != other.time) {
      return false;
    }
    return true;
  }
  bool operator!=(const Num_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Num_

// alias to use template instance with default allocator
using Num =
  mensaje_personal::msg::Num_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace mensaje_personal

#endif  // MENSAJE_PERSONAL__MSG__DETAIL__NUM__STRUCT_HPP_
