;; Auto-generated. Do not edit!


(when (boundp 'smartcar_msgs::Lane)
  (if (not (find-package "SMARTCAR_MSGS"))
    (make-package "SMARTCAR_MSGS"))
  (shadow 'Lane (find-package "SMARTCAR_MSGS")))
(unless (find-package "SMARTCAR_MSGS::LANE")
  (make-package "SMARTCAR_MSGS::LANE"))

(in-package "ROS")
;;//! \htmlinclude Lane.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass smartcar_msgs::Lane
  :super ros::object
  :slots (_header _lane_id _waypoints _cost _center_cost _transition_cost _lateral_cost _long_cost _closest_obj_dis _is_blocked _best_rollout_index ))

(defmethod smartcar_msgs::Lane
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:lane_id __lane_id) 0)
    ((:waypoints __waypoints) (let (r) (dotimes (i 0) (push (instance smartcar_msgs::Waypoint :init) r)) r))
    ((:cost __cost) 0.0)
    ((:center_cost __center_cost) 0.0)
    ((:transition_cost __transition_cost) 0.0)
    ((:lateral_cost __lateral_cost) 0.0)
    ((:long_cost __long_cost) 0.0)
    ((:closest_obj_dis __closest_obj_dis) 0.0)
    ((:is_blocked __is_blocked) nil)
    ((:best_rollout_index __best_rollout_index) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _lane_id (round __lane_id))
   (setq _waypoints __waypoints)
   (setq _cost (float __cost))
   (setq _center_cost (float __center_cost))
   (setq _transition_cost (float __transition_cost))
   (setq _lateral_cost (float __lateral_cost))
   (setq _long_cost (float __long_cost))
   (setq _closest_obj_dis (float __closest_obj_dis))
   (setq _is_blocked __is_blocked)
   (setq _best_rollout_index (round __best_rollout_index))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:lane_id
   (&optional __lane_id)
   (if __lane_id (setq _lane_id __lane_id)) _lane_id)
  (:waypoints
   (&rest __waypoints)
   (if (keywordp (car __waypoints))
       (send* _waypoints __waypoints)
     (progn
       (if __waypoints (setq _waypoints (car __waypoints)))
       _waypoints)))
  (:cost
   (&optional __cost)
   (if __cost (setq _cost __cost)) _cost)
  (:center_cost
   (&optional __center_cost)
   (if __center_cost (setq _center_cost __center_cost)) _center_cost)
  (:transition_cost
   (&optional __transition_cost)
   (if __transition_cost (setq _transition_cost __transition_cost)) _transition_cost)
  (:lateral_cost
   (&optional __lateral_cost)
   (if __lateral_cost (setq _lateral_cost __lateral_cost)) _lateral_cost)
  (:long_cost
   (&optional __long_cost)
   (if __long_cost (setq _long_cost __long_cost)) _long_cost)
  (:closest_obj_dis
   (&optional __closest_obj_dis)
   (if __closest_obj_dis (setq _closest_obj_dis __closest_obj_dis)) _closest_obj_dis)
  (:is_blocked
   (&optional __is_blocked)
   (if __is_blocked (setq _is_blocked __is_blocked)) _is_blocked)
  (:best_rollout_index
   (&optional __best_rollout_index)
   (if __best_rollout_index (setq _best_rollout_index __best_rollout_index)) _best_rollout_index)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _lane_id
    4
    ;; smartcar_msgs/Waypoint[] _waypoints
    (apply #'+ (send-all _waypoints :serialization-length)) 4
    ;; float64 _cost
    8
    ;; float64 _center_cost
    8
    ;; float64 _transition_cost
    8
    ;; float64 _lateral_cost
    8
    ;; float64 _long_cost
    8
    ;; float64 _closest_obj_dis
    8
    ;; bool _is_blocked
    1
    ;; int32 _best_rollout_index
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _lane_id
       (write-long _lane_id s)
     ;; smartcar_msgs/Waypoint[] _waypoints
     (write-long (length _waypoints) s)
     (dolist (elem _waypoints)
       (send elem :serialize s)
       )
     ;; float64 _cost
       (sys::poke _cost (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _center_cost
       (sys::poke _center_cost (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _transition_cost
       (sys::poke _transition_cost (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _lateral_cost
       (sys::poke _lateral_cost (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _long_cost
       (sys::poke _long_cost (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _closest_obj_dis
       (sys::poke _closest_obj_dis (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; bool _is_blocked
       (if _is_blocked (write-byte -1 s) (write-byte 0 s))
     ;; int32 _best_rollout_index
       (write-long _best_rollout_index s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _lane_id
     (setq _lane_id (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; smartcar_msgs/Waypoint[] _waypoints
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _waypoints (let (r) (dotimes (i n) (push (instance smartcar_msgs::Waypoint :init) r)) r))
     (dolist (elem- _waypoints)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; float64 _cost
     (setq _cost (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _center_cost
     (setq _center_cost (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _transition_cost
     (setq _transition_cost (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _lateral_cost
     (setq _lateral_cost (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _long_cost
     (setq _long_cost (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _closest_obj_dis
     (setq _closest_obj_dis (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; bool _is_blocked
     (setq _is_blocked (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; int32 _best_rollout_index
     (setq _best_rollout_index (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get smartcar_msgs::Lane :md5sum-) "97f9fe11d473c4d711b5fcf4253fcd1e")
(setf (get smartcar_msgs::Lane :datatype-) "smartcar_msgs/Lane")
(setf (get smartcar_msgs::Lane :definition-)
      "Header header
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



(provide :smartcar_msgs/Lane "97f9fe11d473c4d711b5fcf4253fcd1e")


