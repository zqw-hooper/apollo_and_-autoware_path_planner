;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::LaneArray)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'LaneArray (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::LANEARRAY")
  (make-package "SMARTCAR_MSGS::LANEARRAY"))

(in-package "ROS")
;;//! \htmlinclude LaneArray.msg.html


(defclass smartcar_msgs::LaneArray
  :super ros::object
  :slots (_lanes ))

(defmethod smartcar_msgs::LaneArray
  (:init
   (&key
    ((:lanes __lanes) (let (r) (dotimes (i 0) (push (instance smartcar_msgs::Lane :init) r)) r))
    )
   (send-super :init)
   (setq _lanes __lanes)
   self)
  (:lanes
   (&rest __lanes)
   (if (keywordp (car __lanes))
       (send* _lanes __lanes)
     (progn
       (if __lanes (setq _lanes (car __lanes)))
       _lanes)))
  (:serialization-length
   ()
   (+
    ;; smartcar_msgs/Lane[] _lanes
    (apply #'+ (send-all _lanes :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; smartcar_msgs/Lane[] _lanes
     (write-long (length _lanes) s)
     (dolist (elem _lanes)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; smartcar_msgs/Lane[] _lanes
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _lanes (let (r) (dotimes (i n) (push (instance smartcar_msgs::Lane :init) r)) r))
     (dolist (elem- _lanes)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get smartcar_msgs::LaneArray :md5sum-) "ad237cdeffc418a8c16de978c749b43e")
(setf (get smartcar_msgs::LaneArray :datatype-) "smartcar_msgs/LaneArray")
(setf (get smartcar_msgs::LaneArray :definition-)
      "Lane[] lanes
================================================================================
MSG: smartcar_msgs/Lane
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

")



(provide :smartcar_msgs/LaneArray "ad237cdeffc418a8c16de978c749b43e")


