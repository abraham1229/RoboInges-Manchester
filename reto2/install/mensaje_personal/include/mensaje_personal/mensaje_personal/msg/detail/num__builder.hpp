// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mensaje_personal:msg/Num.idl
// generated code does not contain a copyright notice

#ifndef MENSAJE_PERSONAL__MSG__DETAIL__NUM__BUILDER_HPP_
#define MENSAJE_PERSONAL__MSG__DETAIL__NUM__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mensaje_personal/msg/detail/num__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mensaje_personal
{

namespace msg
{

namespace builder
{

class Init_Num_time
{
public:
  explicit Init_Num_time(::mensaje_personal::msg::Num & msg)
  : msg_(msg)
  {}
  ::mensaje_personal::msg::Num time(::mensaje_personal::msg::Num::_time_type arg)
  {
    msg_.time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mensaje_personal::msg::Num msg_;
};

class Init_Num_phase_shift
{
public:
  explicit Init_Num_phase_shift(::mensaje_personal::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_time phase_shift(::mensaje_personal::msg::Num::_phase_shift_type arg)
  {
    msg_.phase_shift = std::move(arg);
    return Init_Num_time(msg_);
  }

private:
  ::mensaje_personal::msg::Num msg_;
};

class Init_Num_offset
{
public:
  explicit Init_Num_offset(::mensaje_personal::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_phase_shift offset(::mensaje_personal::msg::Num::_offset_type arg)
  {
    msg_.offset = std::move(arg);
    return Init_Num_phase_shift(msg_);
  }

private:
  ::mensaje_personal::msg::Num msg_;
};

class Init_Num_freq
{
public:
  explicit Init_Num_freq(::mensaje_personal::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_offset freq(::mensaje_personal::msg::Num::_freq_type arg)
  {
    msg_.freq = std::move(arg);
    return Init_Num_offset(msg_);
  }

private:
  ::mensaje_personal::msg::Num msg_;
};

class Init_Num_amplitude
{
public:
  explicit Init_Num_amplitude(::mensaje_personal::msg::Num & msg)
  : msg_(msg)
  {}
  Init_Num_freq amplitude(::mensaje_personal::msg::Num::_amplitude_type arg)
  {
    msg_.amplitude = std::move(arg);
    return Init_Num_freq(msg_);
  }

private:
  ::mensaje_personal::msg::Num msg_;
};

class Init_Num_type
{
public:
  Init_Num_type()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Num_amplitude type(::mensaje_personal::msg::Num::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_Num_amplitude(msg_);
  }

private:
  ::mensaje_personal::msg::Num msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mensaje_personal::msg::Num>()
{
  return mensaje_personal::msg::builder::Init_Num_type();
}

}  // namespace mensaje_personal

#endif  // MENSAJE_PERSONAL__MSG__DETAIL__NUM__BUILDER_HPP_
