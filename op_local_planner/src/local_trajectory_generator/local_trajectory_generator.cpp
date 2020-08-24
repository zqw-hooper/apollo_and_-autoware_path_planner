/*
 * @Description: collision avoid and local trajectory generator implement
 * @Author: sunm
 * @Github: https://github.com/sunmiaozju
 * @Date: 2019-02-15 14:54:09
 * @LastEditors: sunm
 * @LastEditTime: 2019-03-28 15:38:55
 */
#include <local_trajectory_generator/local_trajectory_generator.h>

namespace LocalTrajectoryGeneratorNS
{
    LocalTrajectoryGenerator::LocalTrajectoryGenerator() : velodyne_map_tf_ok(false), currentPose_flag(false), usingObjs(false), pre_best_index(-1)

    {
        initROS();
    }

    void LocalTrajectoryGenerator::initROS()
    {
        // sub_currentPose = nh.subscribe("/ndt/current_pose", 1, &LocalTrajectoryGenerator::getCurrentPose_cb, this);
        // sub_detectedObjects = nh.subscribe("fusion_objs", 1, &LocalTrajectoryGenerator::getDetectedObjects_cb, this);
        // sub_localRollouts = nh.subscribe("local_rollouts", 1, &LocalTrajectoryGenerator::getRolloutPaths_cb, this);
        // sub_centralPath = nh.subscribe("centralPathSection", 1, &LocalTrajectoryGenerator::getCentralPathSection_cb, this);

        // pub_collisionObjsRviz = nh.advertise<visualization_msgs::MarkerArray>("planner_objs_rviz", 1);
        // pub_LocalWeightedTrajectoryRviz = nh.advertise<visualization_msgs::MarkerArray>("local_trajectories_rviz", 1);
        // pub_LocalWeightedTrajectory = nh.advertise<smartcar_msgs::LaneArray>("local_trajectories", 1);
        // pub_TrajectoryCost = nh.advertise<smartcar_msgs::Lane>("local_trajectory_cost", 1);
        // pub_testLane = nh.advertise<visualization_msgs::Marker>("test_lane", 1);
        // pub_test_points = nh.advertise<visualization_msgs::MarkerArray>("test_points", 1);
        // pub_best_trajectories = nh.advertise<smartcar_msgs::Lane>("best_local_trajectories", 1);

        plan_params.horizonDistance = 200;
        plan_params.rollOutNumber = 6;
        plan_params.rollOutDensity = 0.1;
        plan_params.horizontalSafetyDistancel = 1;
        plan_params.verticalSafetyDistance = 1;
        plan_params.minFollowingDistance = 50;
        plan_params.lateralSkipDistance = 6.0;
        car_info.width = 0.5;
        car_info.length = 0.68;
        car_info.wheel_base = 0.48;

        // to_do_op
        // 获取机器人当前位置  //getCurrentPose_cb
        {
            // current_pose = UtilityNS::WayPoint(msg->pose.position.x, msg->pose.position.y, msg->pose.position.z, tf::getYaw(msg->pose.orientation));
            current_pose = UtilityNS::WayPoint(0, 0, 0, 0);
            currentPose_flag = true;
        }
    }
    LocalTrajectoryGenerator::~LocalTrajectoryGenerator() {}

    /**
 * @description: 获取障碍物数组
 */
    // void LocalTrajectoryGenerator::getDetectedObjects_cb(const smartcar_msgs::DetectedObjectArrayConstPtr& msg)
    // {
    // if (detect_objs.size() == 0) {
    //     UtilityNS::DetectedObject obj_zero;
    //     set_detectObj(obj_zero, msg, 0);
    //     detect_objs.push_back(obj_zero);
    // }
    //     detect_objs_tmp.clear();
    //     bool flag_similar_objs = false;
    //     for (int i = 0; i < msg->objects.size(); i++)
    //     {
    //         flag_similar_objs = false;
    //         for (int j = 0; j < detect_objs.size(); j++)
    //         {
    //             double center_dis;
    //             center_dis = std::sqrt(std::pow((msg->objects[i].pose.position.x - detect_objs[j].center.pos.x), 2) + std::pow((msg->objects[i].pose.position.y - detect_objs[j].center.pos.y), 2));
    //             double volume_diff;
    //             volume_diff = (detect_objs[j].l * detect_objs[j].w * detect_objs[j].h) - (msg->objects[i].dimensions.x * msg->objects[i].dimensions.y * msg->objects[i].dimensions.z);

    //             if (center_dis <= 0.5 && volume_diff < 20)
    //             {
    //                 set_detectObj(detect_objs[j], msg, i);
    //                 flag_similar_objs = true;
    //             }
    //         }
    //         if (!flag_similar_objs)
    //         {
    //             UtilityNS::DetectedObject obj;
    //             set_detectObj(obj, msg, i);
    //             detect_objs_tmp.push_back(obj);
    //         }
    //     }

    //     detect_objs.insert(detect_objs.end(), detect_objs_tmp.begin(), detect_objs_tmp.end());
    //     // printf("%d", int(detect_objs.size()));

    //     // 去除掉已经过期的障碍点
    //     detect_objs_tmp.clear();
    //     for (size_t i = 0; i < detect_objs.size(); i++)
    //     {
    //         if (ros::Time::now() - detect_objs[i].start_time < ros::Duration(0.5))
    //         {
    //             // detect_objs.erase(detect_objs.begin() + i);
    //             detect_objs_tmp.push_back(detect_objs[i]);
    //         }
    //     }
    //     detect_objs = detect_objs_tmp;
    //     detect_objs_tmp.clear();
    // }

    // /**
    //  * @description: 填充障碍物结构体的信息
    //  */
    // void LocalTrajectoryGenerator::set_detectObj(UtilityNS::DetectedObject& out_obj, const smartcar_msgs::DetectedObjectArrayConstPtr& msg, const double& i)
    // {
    //     out_obj.start_time = ros::Time::now();
    //     out_obj.id = msg->objects[i].id;
    //     out_obj.label = msg->objects[i].label;
    //     out_obj.center.pos.x = msg->objects[i].pose.position.x;
    //     out_obj.center.pos.y = msg->objects[i].pose.position.y;
    //     out_obj.center.pos.z = msg->objects[i].pose.position.z;
    //     // obj.center.pos.yaw = tf::getYaw(msg->objects[i].pose.orientation);
    //     velodyne_map_tf = FindTransform("map", "velodyne");
    //     out_obj.center.pos = TransformPoint(out_obj.center.pos, velodyne_map_tf);
    //     UtilityNS::GPSPoint p;
    //     out_obj.l = 0.1;
    //     out_obj.w = 0.1;
    //     out_obj.h = 0.1;
    //     out_obj.contour.clear();
    //     for (int k = 0; k < msg->objects[i].convex_hull.polygon.points.size(); k++) {
    //         p.x = msg->objects[i].convex_hull.polygon.points[k].x;
    //         p.y = msg->objects[i].convex_hull.polygon.points[k].y;
    //         p.z = msg->objects[i].convex_hull.polygon.points[k].z;
    //         p = TransformPoint(p, velodyne_map_tf);
    //         out_obj.l = (out_obj.l < 2 * (p.x - out_obj.center.pos.x) ? 2 * (p.x - out_obj.center.pos.x) : out_obj.l);
    //         out_obj.w = (out_obj.w < 2 * (p.y - out_obj.center.pos.y) ? 2 * (p.y - out_obj.center.pos.y) : out_obj.w);
    //         out_obj.h = (out_obj.h < 2 * (p.z - out_obj.center.pos.z) ? 2 * (p.z - out_obj.center.pos.z) : out_obj.h);
    //         out_obj.contour.push_back(p);
    //     }
    // }

    // /**
    //  * @description: 获取备选跟踪轨迹
    //  */
    // void LocalTrajectoryGenerator::getRolloutPaths_cb(const smartcar_msgs::LaneArrayConstPtr& msg)
    // {
    //     if (msg->lanes.size() > 0) {
    //         generated_rollouts.clear();
    //         for (size_t i = 0; i < msg->lanes.size(); i++) {
    //             std::vector<UtilityNS::WayPoint> rollout_singleLane;
    //             for (size_t k = 0; k < msg->lanes[i].waypoints.size(); k++) {
    //                 UtilityNS::WayPoint wp;
    //                 wp.pos.x = msg->lanes[i].waypoints[k].pose.pose.position.x;
    //                 wp.pos.y = msg->lanes[i].waypoints[k].pose.pose.position.y;
    //                 wp.pos.z = msg->lanes[i].waypoints[k].pose.pose.position.z;
    //                 wp.pos.yaw = tf::getYaw(msg->lanes[i].waypoints[k].pose.pose.orientation);
    //                 rollout_singleLane.push_back(wp);
    //             }
    //             generated_rollouts.push_back(rollout_singleLane);
    //         }
    //     }
    // }
    // /**
    //  * @description: 获取当前跟踪的全局轨迹的片段
    //  * @param {type}
    //  * @return:
    //  */
    // void LocalTrajectoryGenerator::getCentralPathSection_cb(const smartcar_msgs::LaneConstPtr& msg)
    // {
    //     centralPathSection.clear();
    //     for (int i = 0; i < msg->waypoints.size(); i++) {
    //         UtilityNS::WayPoint p;
    //         p.pos.x = msg->waypoints[i].pose.pose.position.x;
    //         p.pos.y = msg->waypoints[i].pose.pose.position.y;
    //         p.pos.z = msg->waypoints[i].pose.pose.position.z;
    //         p.pos.yaw = msg->waypoints[i].yaw;
    //         centralPathSection.push_back(p);
    //     }
    // }
    // /**
    //  * @description: 获取当前位置
    //  * @param {type}
    //  * @return:
    //  */
    // void LocalTrajectoryGenerator::getCurrentPose_cb(const geometry_msgs::PoseStampedConstPtr& msg)
    // {
    //     current_pose = UtilityNS::WayPoint(msg->pose.position.x, msg->pose.position.y, msg->pose.position.z, tf::getYaw(msg->pose.orientation));
    //     currentPose_flag = true;
    // }

    //   主循环函数
    void LocalTrajectoryGenerator::run()
    {
        printf("LocalTrajectoryGenerator,%d   \n", __LINE__);
        double pre_index = -1;
        double pre_pre_index = -1;
        // while (1)
        // {

        UtilityNS::TrajectoryCost best_trajectory;

        if (currentPose_flag /*&& centralPathSection.size() > 0 && velodyne_map_tf_ok*/)
        {
            printf("generated_rollouts.size()  %d \n", generated_rollouts.size());
            printf("centralPathSection.size()  %d \n", centralPathSection.size());

            best_trajectory = trajectory_evaluator_static(generated_rollouts,
                                                          centralPathSection,
                                                          current_pose,
                                                          plan_params,
                                                          car_info,
                                                          detect_objs);

            // best_index = floor(0.6 * best_trajectory.index + 0.25 * pre_index + 0.15 * pre_pre_index);

            best_index = best_trajectory.index;
            printf("best_index,%f   \n", best_index);

            smartcar_msgs::Lane best_local_lane;
            best_local_lane.closest_obj_dis = best_trajectory.closest_obj_distance;
            best_local_lane.is_blocked = best_trajectory.bBlocked;
            best_local_lane.cost = best_trajectory.cost;
            best_local_lane.best_rollout_index = best_trajectory.index;
            // pub_TrajectoryCost.publish(best_local_lane);

            smartcar_msgs::LaneArray local_trajectories_msg;
            // smartcar_msgs::Lane best_local_trajectory;

            // 最优的轨迹点
            best_local_trajectory.waypoints.clear();
            for (int m = 0; m < generated_rollouts.size(); m++)
            {
                smartcar_msgs::Lane lane_msg;
                lane_msg.transition_cost = trajectoryCosts[m].transition_cost;
                lane_msg.center_cost = trajectoryCosts[m].priority_cost;
                lane_msg.lateral_cost = trajectoryCosts[m].lateral_cost;
                lane_msg.long_cost = trajectoryCosts[m].longitudinal_cost;
                lane_msg.cost = trajectoryCosts[m].cost;
                if (m == int(best_index))
                {
                    // printf("best_index,%d   \n", best_index);
                    printf("m,%d   \n", m);
                    best_local_trajectory = lane_msg;
                    for (size_t ii = 0; ii < generated_rollouts[m].size(); ii++)
                    {
                        smartcar_msgs::Waypoint p;
                        p.pose.pose.position.x = generated_rollouts[m][ii].pos.x;
                        p.pose.pose.position.y = generated_rollouts[m][ii].pos.y;
                        p.pose.pose.position.z = generated_rollouts[m][ii].pos.z;
                        p.yaw = generated_rollouts[m][ii].v;
                        best_local_trajectory.waypoints.push_back(p);
                    }
                    // pub_best_trajectories.publish(best_local_trajectory);
                }

                local_trajectories_msg.lanes.push_back(lane_msg);
            }
            // pub_LocalWeightedTrajectory.publish(local_trajectories_msg);
            pre_pre_index = pre_index;
            pre_index = best_index;
            // visualInRviz();
        }
        // }
    }

    // 计算轨迹代价函数（静态）
    UtilityNS::TrajectoryCost LocalTrajectoryGenerator::trajectory_evaluator_static(const std::vector<std::vector<UtilityNS::WayPoint>> &rollouts,
                                                                                    const std::vector<UtilityNS::WayPoint> &centralPath,
                                                                                    const UtilityNS::WayPoint &currPose,
                                                                                    const UtilityNS::PlanningParams &params,
                                                                                    const UtilityNS::CAR_BASIC_INFO &car_info,
                                                                                    const std::vector<UtilityNS::DetectedObject> &obj_list)
    {
        UtilityNS::TrajectoryCost best_trajectory;
        best_trajectory.bBlocked = true;
        best_trajectory.closest_obj_distance = params.horizonDistance;
        best_trajectory.closest_obj_velocity = 0;
        best_trajectory.index = -1;

        // cal current trajectory where running
        UtilityNS::RelativeInfo car_relativeInfo;
        // 计算某一个轨迹到某一个点的相对位置
        UtilityNS::getRelativeInfo(centralPath, currPose, car_relativeInfo);

        int currIndex = params.rollOutNumber / 2 + floor(car_relativeInfo.perp_distance / params.rollOutDensity);
        if (currIndex > params.rollOutNumber)
            currIndex = params.rollOutNumber;
        else if (currIndex < 0)
            currIndex = 0;

        printf("currIndex   %d \n", currIndex);
        printf("rollouts.size()   %d \n", rollouts.size());

        // cal center cost
        trajectoryCosts.clear();
        if (rollouts.size() > 0)
        {
            UtilityNS::TrajectoryCost tc;
            for (int i = 0; i < rollouts.size(); i++)
            {
                tc.index = i;
                tc.relative_index = i - params.rollOutNumber / 2;
                tc.distance_from_center = params.rollOutDensity * tc.relative_index;
                tc.priority_cost = fabs(tc.distance_from_center);
                tc.closest_obj_distance = params.horizonDistance;
                tc.longitudinal_cost = 0;
                tc.lateral_cost = 0;
                trajectoryCosts.push_back(tc);
            }
        }

        // cal transition cost
        // for (int ki = 0; ki < trajectoryCosts.size(); ki++)
        // {
        //     trajectoryCosts[ki].transition_cost = fabs(params.rollOutDensity * (currIndex - ki));

        //     UtilityNS::WayPoint obj_p;
        //     // allContourPoints.clear(); // 所有障碍物的轮廓点
        //     for (int kk = 0; kk < obj_list.size(); kk++)
        //     {
        //         for (int m = 0; m < obj_list[kk].contour.size(); m++)
        //         {
        //             obj_p.pos = obj_list[kk].contour[m];
        //             // obj_p.pos = TransformPoint(obj_list[kk].contour[m], velodyne_map_tf);
        //             obj_p.v = obj_list[kk].center.v;
        //             obj_p.laneId = kk;
        //             allContourPoints.push_back(obj_p);
        //         }
        //     }
        //     printf("allContourPoints.size()  %d \n", allContourPoints.size());
        // }

        calLateralAndLongitudinalCostsStatic(trajectoryCosts, rollouts, centralPath, currPose, allContourPoints, params, car_info);
        normalizeCosts(trajectoryCosts);
        printf("trajectoryCosts.size()   %d \n", trajectoryCosts.size());

        for (size_t i = 0; i < trajectoryCosts.size(); i++)
        {
            printf("index  cost: %d, %f\n", i, trajectoryCosts[i].cost);
        }

        int bestIndex = -1;
        double smallestCost = 1000;
        double smallestDis = 1000;

        for (size_t i = 0; i < trajectoryCosts.size(); i++)
        {
            // printf("%s\n", "--------------------------------");
            // printf("index: %d\n", trajectoryCosts[i].index);
            // printf("cost: %f\n", trajectoryCosts[i].cost);
            // printf("bBlock: %d\n", trajectoryCosts[i].bBlocked);
            // printf("lateral_cost: %f\n", trajectoryCosts[i].lateral_cost);
            // printf("longitudinal_cost: %f\n", trajectoryCosts[i].longitudinal_cost);
            // printf("priority_cost: %f\n", trajectoryCosts[i].priority_cost);
            // printf("transition_cost: %f\n", trajectoryCosts[i].transition_cost);

            if (/*!trajectoryCosts[i].bBlocked &&*/ trajectoryCosts[i].cost < smallestCost)
            {
                smallestCost = trajectoryCosts[i].cost;
                bestIndex = i;
                printf("i  %d \n", i);
            }

            if (trajectoryCosts[i].closest_obj_distance < smallestDis)
            {
                smallestDis = trajectoryCosts[i].closest_obj_distance;
            }
        }

        if (bestIndex == -1)
        {
            best_trajectory.bBlocked = true;
            best_trajectory.index = pre_best_index;
            best_trajectory.closest_obj_distance = smallestDis;
        }
        else if (bestIndex >= 0)
        {
            best_trajectory = trajectoryCosts[bestIndex];
        }
        pre_best_index = bestIndex;

        return best_trajectory;
    }

    // 正则化代价损失
    void LocalTrajectoryGenerator::normalizeCosts(std::vector<UtilityNS::TrajectoryCost> &trajectory_cost)
    {
        double totalPriorities = 1;
        double totalLateralCosts = 1;
        double totalLongitudinalCosts = 1;
        double totalTransitionCosts = 1;

        double weightPriority = 0.2;
        double weightTransition = 0.2;
        double weightLateral = 1.8;
        double weightLong = 0.8;

        // for (int i = 0; i < trajectory_cost.size(); i++)
        // {
        //     totalPriorities += trajectory_cost[i].priority_cost;
        //     totalLateralCosts += trajectory_cost[i].lateral_cost;
        //     totalLongitudinalCosts += trajectory_cost[i].longitudinal_cost;
        //     totalTransitionCosts += trajectory_cost[i].transition_cost;
        // }

        for (int k = 0; k < trajectory_cost.size(); k++)
        {
            if (totalPriorities != 0 && !std::isnan(trajectory_cost[k].priority_cost))
                trajectory_cost[k].priority_cost = trajectory_cost[k].priority_cost / totalPriorities;
            else
                trajectory_cost[k].priority_cost = 0;

            if (totalLateralCosts != 0 && !std::isnan(trajectory_cost[k].lateral_cost))
                trajectory_cost[k].lateral_cost = trajectory_cost[k].lateral_cost / totalLateralCosts;
            else
                trajectory_cost[k].lateral_cost = 0;

            if (totalLongitudinalCosts != 0 && !std::isnan(trajectory_cost[k].longitudinal_cost))
                trajectory_cost[k].longitudinal_cost = trajectory_cost[k].longitudinal_cost / totalLongitudinalCosts;
            else
                trajectory_cost[k].longitudinal_cost = 0;

            if (totalTransitionCosts != 0 && !std::isnan(trajectory_cost[k].transition_cost))
                trajectory_cost[k].transition_cost = trajectory_cost[k].transition_cost / totalTransitionCosts;
            else
                trajectory_cost[k].transition_cost = 0;

            trajectory_cost[k].cost = (weightPriority * trajectory_cost[k].priority_cost + weightLateral * trajectory_cost[k].lateral_cost + weightLong * trajectory_cost[k].longitudinal_cost + weightTransition * trajectory_cost[k].transition_cost) / 4.0;

            // trajectory_cost[k].cost = ( trajectory_cost[k].priority_cost + trajectory_cost[k].lateral_cost +  trajectory_cost[k].longitudinal_cost + trajectory_cost[k].transition_cost) ;
            trajectory_cost[k].cost = trajectory_cost[k].lateral_cost;
        }
    }

    //  计算轨迹到障碍物的水平代价函数和垂直代价函数
    void LocalTrajectoryGenerator::calLateralAndLongitudinalCostsStatic(std::vector<UtilityNS::TrajectoryCost> &trajectoryCosts,
                                                                        const std::vector<std::vector<UtilityNS::WayPoint>> &rollOuts,
                                                                        const std::vector<UtilityNS::WayPoint> &centerPath,
                                                                        const UtilityNS::WayPoint &currPose,
                                                                        const std::vector<UtilityNS::WayPoint> &contourPoints,
                                                                        const UtilityNS::PlanningParams &params,
                                                                        const UtilityNS::CAR_BASIC_INFO &carInfo)
    {
        // 车辆安全区域的footprint
        double critical_lateral_distance = carInfo.width / 2.0 + params.horizontalSafetyDistancel;
        double critical_long_front_distance = carInfo.wheel_base / 2.0 + carInfo.length / 2.0 + params.verticalSafetyDistance;
        double critical_long_back_distance = carInfo.length / 2.0 - carInfo.wheel_base / 2.0 + params.verticalSafetyDistance;

        UtilityNS::GPSPoint bottom_left(-critical_lateral_distance, -critical_long_back_distance, currPose.pos.z, 0);
        UtilityNS::GPSPoint bottom_right(critical_lateral_distance, -critical_long_back_distance, currPose.pos.z, 0);
        UtilityNS::GPSPoint top_left(-critical_lateral_distance, critical_long_front_distance, currPose.pos.z, 0);
        UtilityNS::GPSPoint top_right(critical_lateral_distance, critical_long_front_distance, currPose.pos.z, 0);

        UtilityNS::Mat3 invRoatationMat(currPose.pos.yaw);
        UtilityNS::Mat3 invTranslationMat(currPose.pos.x, currPose.pos.y);

        bottom_left = invRoatationMat * bottom_left;
        bottom_left = invTranslationMat * bottom_left;

        bottom_right = invRoatationMat * bottom_right;
        bottom_right = invTranslationMat * bottom_right;

        top_left = invRoatationMat * top_left;
        top_left = invTranslationMat * top_left;

        top_right = invRoatationMat * top_right;
        top_right = invTranslationMat * top_right;
        // 车辆安全区域的footprint

        if (rollOuts.size() > 0)
        {
            UtilityNS::RelativeInfo car_rela_info;
            // 计算某一个轨迹到某一个点的相对位置
            UtilityNS::getRelativeInfo(centerPath, currPose, car_rela_info);
            // UtilityNS::visualLaneInRviz(centerPath, pub_testLane);
            for (int i = 0; i < rollOuts.size(); i++)
            {
                bool too_close = false;

                for (int k = 0; k < contourPoints.size(); k++)
                {
                    for (int ii = 0; ii < rollOuts[i].size(); ii++)
                    {
                        double x = rollOuts[i][ii].pos.x;
                        double y = rollOuts[i][ii].pos.y;

                        double diff_x = x - contourPoints[k].pos.x;
                        double diff_y = y - contourPoints[k].pos.y;

                        double distance = hypotf(diff_x, diff_y);
                        if (distance < 0.2)
                        {
                            too_close = true;
                            printf("too_close index  %d \n", i);
                        }
                    }
                }

                if (too_close)
                {
                    trajectoryCosts[i].lateral_cost = 300;
                }
                else
                {
                    trajectoryCosts[i].lateral_cost = 100;
                }
            }
        }
    }

    //   计算两个点之间的沿着轨迹线的距离
    double LocalTrajectoryGenerator::getTwoPointsDistanceAlongTrajectory(const std::vector<UtilityNS::WayPoint> &trajectory,
                                                                         const UtilityNS::RelativeInfo &p1,
                                                                         const UtilityNS::RelativeInfo &p2)
    {
        if (trajectory.size() == 0)
            return 0;
        if (p1.iFront == p2.iFront && p1.iBack == p2.iBack)
        {
            return p2.to_front_distance - p1.to_front_distance;
        }
        else if (p1.iFront <= p2.iBack)
        {
            double dis_along_tra = p1.to_front_distance + p2.from_back_distance;
            for (int i = p1.iFront; i < p2.iBack; i++)
            {
                dis_along_tra += hypot(trajectory[i + 1].pos.y - trajectory[i].pos.y, trajectory[i + 1].pos.x - trajectory[i].pos.x);
            }
            return dis_along_tra;
        }
        else if (p2.iFront <= p1.iBack)
        {
            double dis_along_tra = p1.to_front_distance + p2.from_back_distance;
            for (int i = p1.iFront; i < p2.iBack; i++)
            {
                dis_along_tra += hypot(trajectory[i + 1].pos.y - trajectory[i].pos.y, trajectory[i + 1].pos.x - trajectory[i].pos.x);
            }
            return -dis_along_tra;
        }
        else
        {
            return 0;
        }
    }

} // namespace LocalTrajectoryGeneratorNS