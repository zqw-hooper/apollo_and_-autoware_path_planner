; Auto-generated. Do not edit!


(cl:in-package smartcar_msgs-msg)


;//! \htmlinclude LaneArray.msg.html

(cl:defclass <LaneArray> (roslisp-msg-protocol:ros-message)
  ((lanes
    :reader lanes
    :initarg :lanes
    :type (cl:vector smartcar_msgs-msg:Lane)
   :initform (cl:make-array 0 :element-type 'smartcar_msgs-msg:Lane :initial-element (cl:make-instance 'smartcar_msgs-msg:Lane))))
)

(cl:defclass LaneArray (<LaneArray>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <LaneArray>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'LaneArray)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smartcar_msgs-msg:<LaneArray> is deprecated: use smartcar_msgs-msg:LaneArray instead.")))

(cl:ensure-generic-function 'lanes-val :lambda-list '(m))
(cl:defmethod lanes-val ((m <LaneArray>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smartcar_msgs-msg:lanes-val is deprecated.  Use smartcar_msgs-msg:lanes instead.")
  (lanes m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <LaneArray>) ostream)
  "Serializes a message object of type '<LaneArray>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'lanes))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'lanes))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <LaneArray>) istream)
  "Deserializes a message object of type '<LaneArray>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'lanes) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'lanes)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'smartcar_msgs-msg:Lane))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<LaneArray>)))
  "Returns string type for a message object of type '<LaneArray>"
  "smartcar_msgs/LaneArray")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'LaneArray)))
  "Returns string type for a message object of type 'LaneArray"
  "smartcar_msgs/LaneArray")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<LaneArray>)))
  "Returns md5sum for a message object of type '<LaneArray>"
  "ad237cdeffc418a8c16de978c749b43e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'LaneArray)))
  "Returns md5sum for a message object of type 'LaneArray"
  "ad237cdeffc418a8c16de978c749b43e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<LaneArray>)))
  "Returns full string definition for message of type '<LaneArray>"
  (cl:format cl:nil "Lane[] lanes~%================================================================================~%MSG: smartcar_msgs/Lane~%Header header~%int32 lane_id~%Waypoint[] waypoints~%~%float64 cost~%float64 center_cost~%float64 transition_cost~%float64 lateral_cost~%float64 long_cost~%~%float64 closest_obj_dis~%bool is_blocked~%int32 best_rollout_index~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/Waypoint~%float32 speed_limit~%float32 yaw~%int16 is_lane   # lane = 1 , cross = 0~%~%geometry_msgs/PoseStamped pose~%~%~%~%~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'LaneArray)))
  "Returns full string definition for message of type 'LaneArray"
  (cl:format cl:nil "Lane[] lanes~%================================================================================~%MSG: smartcar_msgs/Lane~%Header header~%int32 lane_id~%Waypoint[] waypoints~%~%float64 cost~%float64 center_cost~%float64 transition_cost~%float64 lateral_cost~%float64 long_cost~%~%float64 closest_obj_dis~%bool is_blocked~%int32 best_rollout_index~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: smartcar_msgs/Waypoint~%float32 speed_limit~%float32 yaw~%int16 is_lane   # lane = 1 , cross = 0~%~%geometry_msgs/PoseStamped pose~%~%~%~%~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of position and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <LaneArray>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'lanes) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <LaneArray>))
  "Converts a ROS message object to a list"
  (cl:list 'LaneArray
    (cl:cons ':lanes (lanes msg))
))
