;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::Waypoint)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'Waypoint (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::WAYPOINT")
  (make-package "SMARTCAR_MSGS::WAYPOINT"))

(in-package "ROS")
;;//! \htmlinclude Waypoint.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass smartcar_msgs::Waypoint
  :super ros::object
  :slots (_speed_limit _yaw _is_lane _pose ))

(defmethod smartcar_msgs::Waypoint
  (:init
   (&key
    ((:speed_limit __speed_limit) 0.0)
    ((:yaw __yaw) 0.0)
    ((:is_lane __is_lane) 0)
    ((:pose __pose) (instance geometry_msgs::PoseStamped :init))
    )
   (send-super :init)
   (setq _speed_limit (float __speed_limit))
   (setq _yaw (float __yaw))
   (setq _is_lane (round __is_lane))
   (setq _pose __pose)
   self)
  (:speed_limit
   (&optional __speed_limit)
   (if __speed_limit (setq _speed_limit __speed_limit)) _speed_limit)
  (:yaw
   (&optional __yaw)
   (if __yaw (setq _yaw __yaw)) _yaw)
  (:is_lane
   (&optional __is_lane)
   (if __is_lane (setq _is_lane __is_lane)) _is_lane)
  (:pose
   (&rest __pose)
   (if (keywordp (car __pose))
       (send* _pose __pose)
     (progn
       (if __pose (setq _pose (car __pose)))
       _pose)))
  (:serialization-length
   ()
   (+
    ;; float32 _speed_limit
    4
    ;; float32 _yaw
    4
    ;; int16 _is_lane
    2
    ;; geometry_msgs/PoseStamped _pose
    (send _pose :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _speed_limit
       (sys::poke _speed_limit (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yaw
       (sys::poke _yaw (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int16 _is_lane
       (write-word _is_lane s)
     ;; geometry_msgs/PoseStamped _pose
       (send _pose :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _speed_limit
     (setq _speed_limit (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yaw
     (setq _yaw (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int16 _is_lane
     (setq _is_lane (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; geometry_msgs/PoseStamped _pose
     (send _pose :deserialize buf ptr-) (incf ptr- (send _pose :serialization-length))
   ;;
   self)
  )

(setf (get smartcar_msgs::Waypoint :md5sum-) "b5a2063d34c7600d16d0bc54c56ca29f")
(setf (get smartcar_msgs::Waypoint :datatype-) "smartcar_msgs/Waypoint")
(setf (get smartcar_msgs::Waypoint :definition-)
      "float32 speed_limit
float32 yaw
int16 is_lane   # lane = 1 , cross = 0

geometry_msgs/PoseStamped pose





================================================================================
MSG: geometry_msgs/PoseStamped
# A Pose with reference coordinate frame and timestamp
Header header
Pose pose

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



(provide :smartcar_msgs/Waypoint "b5a2063d34c7600d16d0bc54c56ca29f")


