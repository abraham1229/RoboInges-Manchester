// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from mensaje_personal:msg/Sphere.idl
// generated code does not contain a copyright notice

#ifndef MENSAJE_PERSONAL__MSG__DETAIL__SPHERE__BUILDER_HPP_
#define MENSAJE_PERSONAL__MSG__DETAIL__SPHERE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "mensaje_personal/msg/detail/sphere__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace mensaje_personal
{

namespace msg
{

namespace builder
{

class Init_Sphere_radius
{
public:
  explicit Init_Sphere_radius(::mensaje_personal::msg::Sphere & msg)
  : msg_(msg)
  {}
  ::mensaje_personal::msg::Sphere radius(::mensaje_personal::msg::Sphere::_radius_type arg)
  {
    msg_.radius = std::move(arg);
    return std::move(msg_);
  }

private:
  ::mensaje_personal::msg::Sphere msg_;
};

class Init_Sphere_center
{
public:
  Init_Sphere_center()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Sphere_radius center(::mensaje_personal::msg::Sphere::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_Sphere_radius(msg_);
  }

private:
  ::mensaje_personal::msg::Sphere msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::mensaje_personal::msg::Sphere>()
{
  return mensaje_personal::msg::builder::Init_Sphere_center();
}

}  // namespace mensaje_personal

#endif  // MENSAJE_PERSONAL__MSG__DETAIL__SPHERE__BUILDER_HPP_
