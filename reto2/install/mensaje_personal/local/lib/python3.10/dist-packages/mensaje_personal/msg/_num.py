# generated from rosidl_generator_py/resource/_idl.py.em
# with input from mensaje_personal:msg/Num.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Num(type):
    """Metaclass of message 'Num'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('mensaje_personal')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'mensaje_personal.msg.Num')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__num
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__num
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__num
            cls._TYPE_SUPPORT = module.type_support_msg__msg__num
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__num

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Num(metaclass=Metaclass_Num):
    """Message class 'Num'."""

    __slots__ = [
        '_type',
        '_amplitude',
        '_freq',
        '_offset',
        '_phase_shift',
        '_time',
    ]

    _fields_and_field_types = {
        'type': 'int64',
        'amplitude': 'float',
        'freq': 'float',
        'offset': 'float',
        'phase_shift': 'float',
        'time': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.type = kwargs.get('type', int())
        self.amplitude = kwargs.get('amplitude', float())
        self.freq = kwargs.get('freq', float())
        self.offset = kwargs.get('offset', float())
        self.phase_shift = kwargs.get('phase_shift', float())
        self.time = kwargs.get('time', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.type != other.type:
            return False
        if self.amplitude != other.amplitude:
            return False
        if self.freq != other.freq:
            return False
        if self.offset != other.offset:
            return False
        if self.phase_shift != other.phase_shift:
            return False
        if self.time != other.time:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property  # noqa: A003
    def type(self):  # noqa: A003
        """Message field 'type'."""
        return self._type

    @type.setter  # noqa: A003
    def type(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'type' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'type' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._type = value

    @builtins.property
    def amplitude(self):
        """Message field 'amplitude'."""
        return self._amplitude

    @amplitude.setter
    def amplitude(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'amplitude' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'amplitude' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._amplitude = value

    @builtins.property
    def freq(self):
        """Message field 'freq'."""
        return self._freq

    @freq.setter
    def freq(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'freq' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'freq' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._freq = value

    @builtins.property
    def offset(self):
        """Message field 'offset'."""
        return self._offset

    @offset.setter
    def offset(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'offset' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'offset' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._offset = value

    @builtins.property
    def phase_shift(self):
        """Message field 'phase_shift'."""
        return self._phase_shift

    @phase_shift.setter
    def phase_shift(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'phase_shift' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'phase_shift' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._phase_shift = value

    @builtins.property
    def time(self):
        """Message field 'time'."""
        return self._time

    @time.setter
    def time(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'time' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'time' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._time = value
