// Generated by gencpp from file smartcar_msgs/ControlCommandStamped.msg
// DO NOT EDIT!


#ifndef SMARTCAR_MSGS_MESSAGE_CONTROLCOMMANDSTAMPED_H
#define SMARTCAR_MSGS_MESSAGE_CONTROLCOMMANDSTAMPED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <smartcar_msgs/ControlCommand.h>

namespace smartcar_msgs
{
template <class ContainerAllocator>
struct ControlCommandStamped_
{
  typedef ControlCommandStamped_<ContainerAllocator> Type;

  ControlCommandStamped_()
    : header()
    , cmd()  {
    }
  ControlCommandStamped_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , cmd(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef  ::smartcar_msgs::ControlCommand_<ContainerAllocator>  _cmd_type;
  _cmd_type cmd;





  typedef boost::shared_ptr< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> const> ConstPtr;

}; // struct ControlCommandStamped_

typedef ::smartcar_msgs::ControlCommandStamped_<std::allocator<void> > ControlCommandStamped;

typedef boost::shared_ptr< ::smartcar_msgs::ControlCommandStamped > ControlCommandStampedPtr;
typedef boost::shared_ptr< ::smartcar_msgs::ControlCommandStamped const> ControlCommandStampedConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace smartcar_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'smartcar_msgs': ['/home/zy/Desktop/op_local_planner/src/msgs/smartcar_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "cf8b01a8273bedcf082c4a0007472482";
  }

  static const char* value(const ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xcf8b01a8273bedcfULL;
  static const uint64_t static_value2 = 0x082c4a0007472482ULL;
};

template<class ContainerAllocator>
struct DataType< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "smartcar_msgs/ControlCommandStamped";
  }

  static const char* value(const ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
ControlCommand cmd\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: smartcar_msgs/ControlCommand\n\
float64 linear_velocity\n\
float64 linear_acceleration #m/s^2\n\
float64 steering_angle\n\
";
  }

  static const char* value(const ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.cmd);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct ControlCommandStamped_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::smartcar_msgs::ControlCommandStamped_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "cmd: ";
    s << std::endl;
    Printer< ::smartcar_msgs::ControlCommand_<ContainerAllocator> >::stream(s, indent + "  ", v.cmd);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SMARTCAR_MSGS_MESSAGE_CONTROLCOMMANDSTAMPED_H
