// Generated by gencpp from file smartcar_msgs/TrafficLightResultArray.msg
// DO NOT EDIT!


#ifndef SMARTCAR_MSGS_MESSAGE_TRAFFICLIGHTRESULTARRAY_H
#define SMARTCAR_MSGS_MESSAGE_TRAFFICLIGHTRESULTARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <smartcar_msgs/TrafficLightResult.h>

namespace smartcar_msgs
{
template <class ContainerAllocator>
struct TrafficLightResultArray_
{
  typedef TrafficLightResultArray_<ContainerAllocator> Type;

  TrafficLightResultArray_()
    : header()
    , results()  {
    }
  TrafficLightResultArray_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , results(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >::other >  _results_type;
  _results_type results;





  typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> const> ConstPtr;

}; // struct TrafficLightResultArray_

typedef ::smartcar_msgs::TrafficLightResultArray_<std::allocator<void> > TrafficLightResultArray;

typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResultArray > TrafficLightResultArrayPtr;
typedef boost::shared_ptr< ::smartcar_msgs::TrafficLightResultArray const> TrafficLightResultArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace smartcar_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'smartcar_msgs': ['/home/zy/Desktop/smartcar-dev_sunm/src/msgs/smartcar_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "2eb6bbdf62a95999f591812dc7ba8aa2";
  }

  static const char* value(const ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x2eb6bbdf62a95999ULL;
  static const uint64_t static_value2 = 0xf591812dc7ba8aa2ULL;
};

template<class ContainerAllocator>
struct DataType< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "smartcar_msgs/TrafficLightResultArray";
  }

  static const char* value(const ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n\
TrafficLightResult[] results\n\
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
\n\
================================================================================\n\
MSG: smartcar_msgs/TrafficLightResult\n\
# This message defines meta information for a traffic light status\n\
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
";
  }

  static const char* value(const ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.results);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct TrafficLightResultArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::smartcar_msgs::TrafficLightResultArray_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "results[]" << std::endl;
    for (size_t i = 0; i < v.results.size(); ++i)
    {
      s << indent << "  results[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::smartcar_msgs::TrafficLightResult_<ContainerAllocator> >::stream(s, indent + "    ", v.results[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // SMARTCAR_MSGS_MESSAGE_TRAFFICLIGHTRESULTARRAY_H
