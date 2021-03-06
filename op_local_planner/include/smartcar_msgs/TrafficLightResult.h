// Generated by gencpp from file smartcar_msgs/TrafficLightResult.msg
// DO NOT EDIT!


#ifndef SMARTCAR_MSGS_MESSAGE_TRAFFICLIGHTRESULT_H
#define SMARTCAR_MSGS_MESSAGE_TRAFFICLIGHTRESULT_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace smartcar_msgs
{
template <class ContainerAllocator>
struct TrafficLightResult_
{
  typedef TrafficLightResult_<ContainerAllocator> Type;

  TrafficLightResult_()
    : header()
    , light_id(0)
    , recognition_result(0)
    , recognition_result_str()
    , lane_id(0)  {
    }
  TrafficLightResult_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , light_id(0)
    , recognition_result(0)
    , recognition_result_str(_alloc)
    , lane_id(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef int32_t _light_id_type;
  _light_id_type light_id;

   typedef int32_t _recognition_result_type;
  _recognition_result_type recognition_result;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _recognition_result_str_type;
  _recognition_result_str_type recognition_result_str;

   typedef int32_t _lane_id_type;
  _lane_id_type lane_id;





  typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> const> ConstPtr;

}; // struct TrafficLightResult_

typedef ::smartcar_msgs::TrafficLightResult_<std::allocator<void> > TrafficLightResult;

typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResult > TrafficLightResultPtr;
typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResult const> TrafficLightResultConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >::stream(s, "", v);
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
struct IsFixedSize< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "e09c50b47f3c14abf01fe3d89587b0eb";
  }

  static const char* value(const ::smartcar_msgs::TrafficLightResult_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xe09c50b47f3c14abULL;
  static const uint64_t static_value2 = 0xf01fe3d89587b0ebULL;
};

template<class ContainerAllocator>
struct DataType< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "smartcar_msgs/TrafficLightResult";
  }

  static const char* value(const ::smartcar_msgs::TrafficLightResult_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# This message defines meta information for a traffic light status\n\
Header header\n\
\n\
# Each bulb is assigned with an Id\n\
# The TLR node convention is to use the yellow bulb's ID\n\
int32 light_id\n\
\n\
# The result as provided by the tlr nodes\n\
# Red and Yellow states are both treated as STOP\n\
# RED       = 0\n\
# YELLOW    = 0\n\
# GREEN     = 1\n\
# UNKNOWN   = 2\n\
int32 recognition_result\n\
\n\
# This string is used by the Audio Player\n\
string recognition_result_str\n\
\n\
# LaneId to which this traffic light result belongs to\n\
# this Id is defined by the ADAS MAP\n\
int32 lane_id\n\
\n\
\n\
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
";
  }

  static const char* value(const ::smartcar_msgs::TrafficLightResult_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.light_id);
      stream.next(m.recognition_result);
      stream.next(m.recognition_result_str);
      stream.next(m.lane_id);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TrafficLightResult_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::smartcar_msgs::TrafficLightResult_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "light_id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.light_id);
    s << indent << "recognition_result: ";
    Printer<int32_t>::stream(s, indent + "  ", v.recognition_result);
    s << indent << "recognition_result_str: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.recognition_result_str);
    s << indent << "lane_id: ";
    Printer<int32_t>::stream(s, indent + "  ", v.lane_id);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SMARTCAR_MSGS_MESSAGE_TRAFFICLIGHTRESULT_H
