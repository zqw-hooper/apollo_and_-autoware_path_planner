// Generated by gencpp from file smartcar_msgs/LaneArray.msg
// DO NOT EDIT!


#ifndef SMARTCAR_MSGS_MESSAGE_LANEARRAY_H
#define SMARTCAR_MSGS_MESSAGE_LANEARRAY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <smartcar_msgs/Lane.h>

namespace smartcar_msgs
{
template <class ContainerAllocator>
struct LaneArray_
{
  typedef LaneArray_<ContainerAllocator> Type;

  LaneArray_()
    : lanes()  {
    }
  LaneArray_(const ContainerAllocator& _alloc)
    : lanes(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::smartcar_msgs::Lane_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::smartcar_msgs::Lane_<ContainerAllocator> >::other >  _lanes_type;
  _lanes_type lanes;





  typedef boost::shared_ptr< ::smartcar_msgs::LaneArray_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::smartcar_msgs::LaneArray_<ContainerAllocator> const> ConstPtr;

}; // struct LaneArray_

typedef ::smartcar_msgs::LaneArray_<std::allocator<void> > LaneArray;

typedef boost::shared_ptr< ::smartcar_msgs::LaneArray > LaneArrayPtr;
typedef boost::shared_ptr< ::smartcar_msgs::LaneArray const> LaneArrayConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::smartcar_msgs::LaneArray_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::smartcar_msgs::LaneArray_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace smartcar_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'smartcar_msgs': ['/home/zy/Desktop/op_local_planner/src/msgs/smartcar_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::smartcar_msgs::LaneArray_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::smartcar_msgs::LaneArray_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::smartcar_msgs::LaneArray_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "ad237cdeffc418a8c16de978c749b43e";
  }

  static const char* value(const ::smartcar_msgs::LaneArray_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xad237cdeffc418a8ULL;
  static const uint64_t static_value2 = 0xc16de978c749b43eULL;
};

template<class ContainerAllocator>
struct DataType< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "smartcar_msgs/LaneArray";
  }

  static const char* value(const ::smartcar_msgs::LaneArray_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Lane[] lanes\n\
================================================================================\n\
MSG: smartcar_msgs/Lane\n\
Header header\n\
int32 lane_id\n\
Waypoint[] waypoints\n\
\n\
float64 cost\n\
float64 center_cost\n\
float64 transition_cost\n\
float64 lateral_cost\n\
float64 long_cost\n\
\n\
float64 closest_obj_dis\n\
bool is_blocked\n\
int32 best_rollout_index\n\
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
\n\
================================================================================\n\
MSG: smartcar_msgs/Waypoint\n\
float32 speed_limit\n\
float32 yaw\n\
int16 is_lane   # lane = 1 , cross = 0\n\
\n\
geometry_msgs/PoseStamped pose\n\
\n\
\n\
\n\
\n\
\n\
================================================================================\n\
MSG: geometry_msgs/PoseStamped\n\
# A Pose with reference coordinate frame and timestamp\n\
Header header\n\
Pose pose\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";
  }

  static const char* value(const ::smartcar_msgs::LaneArray_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.lanes);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct LaneArray_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::smartcar_msgs::LaneArray_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::smartcar_msgs::LaneArray_<ContainerAllocator>& v)
  {
    s << indent << "lanes[]" << std::endl;
    for (size_t i = 0; i < v.lanes.size(); ++i)
    {
      s << indent << "  lanes[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::smartcar_msgs::Lane_<ContainerAllocator> >::stream(s, indent + "    ", v.lanes[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // SMARTCAR_MSGS_MESSAGE_LANEARRAY_H
