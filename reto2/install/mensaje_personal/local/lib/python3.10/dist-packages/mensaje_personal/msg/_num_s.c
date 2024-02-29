// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from mensaje_personal:msg/Num.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "mensaje_personal/msg/detail/num__struct.h"
#include "mensaje_personal/msg/detail/num__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool mensaje_personal__msg__num__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[30];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("mensaje_personal.msg._num.Num", full_classname_dest, 29) == 0);
  }
  mensaje_personal__msg__Num * ros_message = _ros_message;
  {  // type
    PyObject * field = PyObject_GetAttrString(_pymsg, "type");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->type = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // amplitude
    PyObject * field = PyObject_GetAttrString(_pymsg, "amplitude");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->amplitude = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // freq
    PyObject * field = PyObject_GetAttrString(_pymsg, "freq");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->freq = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // offset
    PyObject * field = PyObject_GetAttrString(_pymsg, "offset");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->offset = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // phase_shift
    PyObject * field = PyObject_GetAttrString(_pymsg, "phase_shift");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->phase_shift = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // time
    PyObject * field = PyObject_GetAttrString(_pymsg, "time");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->time = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * mensaje_personal__msg__num__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Num */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("mensaje_personal.msg._num");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Num");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  mensaje_personal__msg__Num * ros_message = (mensaje_personal__msg__Num *)raw_ros_message;
  {  // type
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->type);
    {
      int rc = PyObject_SetAttrString(_pymessage, "type", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // amplitude
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->amplitude);
    {
      int rc = PyObject_SetAttrString(_pymessage, "amplitude", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // freq
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->freq);
    {
      int rc = PyObject_SetAttrString(_pymessage, "freq", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // offset
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->offset);
    {
      int rc = PyObject_SetAttrString(_pymessage, "offset", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // phase_shift
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->phase_shift);
    {
      int rc = PyObject_SetAttrString(_pymessage, "phase_shift", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // time
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
