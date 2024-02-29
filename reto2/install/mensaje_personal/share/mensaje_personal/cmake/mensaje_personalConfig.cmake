# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_mensaje_personal_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED mensaje_personal_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(mensaje_personal_FOUND FALSE)
  elseif(NOT mensaje_personal_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(mensaje_personal_FOUND FALSE)
  endif()
  return()
endif()
set(_mensaje_personal_CONFIG_INCLUDED TRUE)

# output package information
if(NOT mensaje_personal_FIND_QUIETLY)
  message(STATUS "Found mensaje_personal: 0.0.0 (${mensaje_personal_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'mensaje_personal' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${mensaje_personal_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(mensaje_personal_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "rosidl_cmake-extras.cmake;ament_cmake_export_dependencies-extras.cmake;ament_cmake_export_include_directories-extras.cmake;ament_cmake_export_libraries-extras.cmake;ament_cmake_export_targets-extras.cmake;rosidl_cmake_export_typesupport_targets-extras.cmake;rosidl_cmake_export_typesupport_libraries-extras.cmake")
foreach(_extra ${_extras})
  include("${mensaje_personal_DIR}/${_extra}")
endforeach()
