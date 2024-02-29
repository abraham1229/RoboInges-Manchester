// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from mensaje_personal:msg/Num.idl
// generated code does not contain a copyright notice

#ifndef MENSAJE_PERSONAL__MSG__DETAIL__NUM__TRAITS_HPP_
#define MENSAJE_PERSONAL__MSG__DETAIL__NUM__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "mensaje_personal/msg/detail/num__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace mensaje_personal
{

namespace msg
{

inline void to_flow_style_yaml(
  const Num & msg,
  std::ostream & out)
{
  out << "{";
  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: amplitude
  {
    out << "amplitude: ";
    rosidl_generator_traits::value_to_yaml(msg.amplitude, out);
    out << ", ";
  }

  // member: freq
  {
    out << "freq: ";
    rosidl_generator_traits::value_to_yaml(msg.freq, out);
    out << ", ";
  }

  // member: offset
  {
    out << "offset: ";
    rosidl_generator_traits::value_to_yaml(msg.offset, out);
    out << ", ";
  }

  // member: phase_shift
  {
    out << "phase_shift: ";
    rosidl_generator_traits::value_to_yaml(msg.phase_shift, out);
    out << ", ";
  }

  // member: time
  {
    out << "time: ";
    rosidl_generator_traits::value_to_yaml(msg.time, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Num & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: amplitude
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "amplitude: ";
    rosidl_generator_traits::value_to_yaml(msg.amplitude, out);
    out << "\n";
  }

  // member: freq
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "freq: ";
    rosidl_generator_traits::value_to_yaml(msg.freq, out);
    out << "\n";
  }

  // member: offset
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "offset: ";
    rosidl_generator_traits::value_to_yaml(msg.offset, out);
    out << "\n";
  }

  // member: phase_shift
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "phase_shift: ";
    rosidl_generator_traits::value_to_yaml(msg.phase_shift, out);
    out << "\n";
  }

  // member: time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time: ";
    rosidl_generator_traits::value_to_yaml(msg.time, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Num & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace mensaje_personal

namespace rosidl_generator_traits
{

[[deprecated("use mensaje_personal::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const mensaje_personal::msg::Num & msg,
  std::ostream & out, size_t indentation = 0)
{
  mensaje_personal::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use mensaje_personal::msg::to_yaml() instead")]]
inline std::string to_yaml(const mensaje_personal::msg::Num & msg)
{
  return mensaje_personal::msg::to_yaml(msg);
}

template<>
inline const char * data_type<mensaje_personal::msg::Num>()
{
  return "mensaje_personal::msg::Num";
}

template<>
inline const char * name<mensaje_personal::msg::Num>()
{
  return "mensaje_personal/msg/Num";
}

template<>
struct has_fixed_size<mensaje_personal::msg::Num>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<mensaje_personal::msg::Num>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<mensaje_personal::msg::Num>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MENSAJE_PERSONAL__MSG__DETAIL__NUM__TRAITS_HPP_
