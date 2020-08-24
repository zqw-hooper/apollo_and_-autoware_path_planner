// Auto-generated. Do not edit!

// (in-package smartcar_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let Waypoint = require('./Waypoint.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Lane {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.lane_id = null;
      this.waypoints = null;
      this.cost = null;
      this.center_cost = null;
      this.transition_cost = null;
      this.lateral_cost = null;
      this.long_cost = null;
      this.closest_obj_dis = null;
      this.is_blocked = null;
      this.best_rollout_index = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('lane_id')) {
        this.lane_id = initObj.lane_id
      }
      else {
        this.lane_id = 0;
      }
      if (initObj.hasOwnProperty('waypoints')) {
        this.waypoints = initObj.waypoints
      }
      else {
        this.waypoints = [];
      }
      if (initObj.hasOwnProperty('cost')) {
        this.cost = initObj.cost
      }
      else {
        this.cost = 0.0;
      }
      if (initObj.hasOwnProperty('center_cost')) {
        this.center_cost = initObj.center_cost
      }
      else {
        this.center_cost = 0.0;
      }
      if (initObj.hasOwnProperty('transition_cost')) {
        this.transition_cost = initObj.transition_cost
      }
      else {
        this.transition_cost = 0.0;
      }
      if (initObj.hasOwnProperty('lateral_cost')) {
        this.lateral_cost = initObj.lateral_cost
      }
      else {
        this.lateral_cost = 0.0;
      }
      if (initObj.hasOwnProperty('long_cost')) {
        this.long_cost = initObj.long_cost
      }
      else {
        this.long_cost = 0.0;
      }
      if (initObj.hasOwnProperty('closest_obj_dis')) {
        this.closest_obj_dis = initObj.closest_obj_dis
      }
      else {
        this.closest_obj_dis = 0.0;
      }
      if (initObj.hasOwnProperty('is_blocked')) {
        this.is_blocked = initObj.is_blocked
      }
      else {
        this.is_blocked = false;
      }
      if (initObj.hasOwnProperty('best_rollout_index')) {
        this.best_rollout_index = initObj.best_rollout_index
      }
      else {
        this.best_rollout_index = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Lane
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [lane_id]
    bufferOffset = _serializer.int32(obj.lane_id, buffer, bufferOffset);
    // Serialize message field [waypoints]
    // Serialize the length for message field [waypoints]
    bufferOffset = _serializer.uint32(obj.waypoints.length, buffer, bufferOffset);
    obj.waypoints.forEach((val) => {
      bufferOffset = Waypoint.serialize(val, buffer, bufferOffset);
    });
    // Serialize message field [cost]
    bufferOffset = _serializer.float64(obj.cost, buffer, bufferOffset);
    // Serialize message field [center_cost]
    bufferOffset = _serializer.float64(obj.center_cost, buffer, bufferOffset);
    // Serialize message field [transition_cost]
    bufferOffset = _serializer.float64(obj.transition_cost, buffer, bufferOffset);
    // Serialize message field [lateral_cost]
    bufferOffset = _serializer.float64(obj.lateral_cost, buffer, bufferOffset);
    // Serialize message field [long_cost]
    bufferOffset = _serializer.float64(obj.long_cost, buffer, bufferOffset);
    // Serialize message field [closest_obj_dis]
    bufferOffset = _serializer.float64(obj.closest_obj_dis, buffer, bufferOffset);
    // Serialize message field [is_blocked]
    bufferOffset = _serializer.bool(obj.is_blocked, buffer, bufferOffset);
    // Serialize message field [best_rollout_index]
    bufferOffset = _serializer.int32(obj.best_rollout_index, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Lane
    let len;
    let data = new Lane(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [lane_id]
    data.lane_id = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [waypoints]
    // Deserialize array length for message field [waypoints]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.waypoints = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.waypoints[i] = Waypoint.deserialize(buffer, bufferOffset)
    }
    // Deserialize message field [cost]
    data.cost = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [center_cost]
    data.center_cost = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [transition_cost]
    data.transition_cost = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [lateral_cost]
    data.lateral_cost = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [long_cost]
    data.long_cost = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [closest_obj_dis]
    data.closest_obj_dis = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [is_blocked]
    data.is_blocked = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [best_rollout_index]
    data.best_rollout_index = _deserializer.int32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.waypoints.forEach((val) => {
      length += Waypoint.getMessageSize(val);
    });
    return length + 61;
  }

  static datatype() {
    // Returns string type for a message object
    return 'smartcar_msgs/Lane';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '97f9fe11d473c4d711b5fcf4253fcd1e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int32 lane_id
    Waypoint[] waypoints
    
    float64 cost
    float64 center_cost
    float64 transition_cost
    float64 lateral_cost
    float64 long_cost
    
    float64 closest_obj_dis
    bool is_blocked
    int32 best_rollout_index
    
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: smartcar_msgs/Waypoint
    float32 speed_limit
    float32 yaw
    int16 is_lane   # lane = 1 , cross = 0
    
    geometry_msgs/PoseStamped pose
    
    
    
    
    
    ================================================================================
    MSG: geometry_msgs/PoseStamped
    # A Pose with reference coordinate frame and timestamp
    Header header
    Pose pose
    
    ================================================================================
    MSG: geometry_msgs/Pose
    # A representation of pose in free space, composed of position and orientation. 
    Point position
    Quaternion orientation
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    ================================================================================
    MSG: geometry_msgs/Quaternion
    # This represents an orientation in free space in quaternion form.
    
    float64 x
    float64 y
    float64 z
    float64 w
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Lane(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.lane_id !== undefined) {
      resolved.lane_id = msg.lane_id;
    }
    else {
      resolved.lane_id = 0
    }

    if (msg.waypoints !== undefined) {
      resolved.waypoints = new Array(msg.waypoints.length);
      for (let i = 0; i < resolved.waypoints.length; ++i) {
        resolved.waypoints[i] = Waypoint.Resolve(msg.waypoints[i]);
      }
    }
    else {
      resolved.waypoints = []
    }

    if (msg.cost !== undefined) {
      resolved.cost = msg.cost;
    }
    else {
      resolved.cost = 0.0
    }

    if (msg.center_cost !== undefined) {
      resolved.center_cost = msg.center_cost;
    }
    else {
      resolved.center_cost = 0.0
    }

    if (msg.transition_cost !== undefined) {
      resolved.transition_cost = msg.transition_cost;
    }
    else {
      resolved.transition_cost = 0.0
    }

    if (msg.lateral_cost !== undefined) {
      resolved.lateral_cost = msg.lateral_cost;
    }
    else {
      resolved.lateral_cost = 0.0
    }

    if (msg.long_cost !== undefined) {
      resolved.long_cost = msg.long_cost;
    }
    else {
      resolved.long_cost = 0.0
    }

    if (msg.closest_obj_dis !== undefined) {
      resolved.closest_obj_dis = msg.closest_obj_dis;
    }
    else {
      resolved.closest_obj_dis = 0.0
    }

    if (msg.is_blocked !== undefined) {
      resolved.is_blocked = msg.is_blocked;
    }
    else {
      resolved.is_blocked = false
    }

    if (msg.best_rollout_index !== undefined) {
      resolved.best_rollout_index = msg.best_rollout_index;
    }
    else {
      resolved.best_rollout_index = 0
    }

    return resolved;
    }
};

module.exports = Lane;
