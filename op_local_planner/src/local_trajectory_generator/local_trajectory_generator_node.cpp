/*
 * @Description: collision avoid and local trajectory generator implement
 * @Author: sunm
 * @Github: https://github.com/sunmiaozju
 * @Date: 2019-02-15 14:53:47
 * @LastEditors: sunm
 * @LastEditTime: 2019-02-20 15:46:08
 */
// #include <ros/ros.h>
#include "local_trajectory_generator/local_trajectory_generator.h"
#include "rollout_generator/rollout_generator.h"

#include <iostream>
#include <fstream>

typedef struct
{
    float x;
    float y;
} pose_x_y;

int main(int argc, char *argv[])
{
    // ros::init(argc, argv, "local_trajectory_generator_node");

    RolloutGeneratorNS::RolloutGenerator rollout_generator;
    // 主函数
    rollout_generator.run();
    rollout_generator.local_lanes;

    LocalTrajectoryGeneratorNS::LocalTrajectoryGenerator localtraj_generator;

    // 加入障碍物
    std::ofstream local_map_writer_obstacle;
    local_map_writer_obstacle.open("/home/zy/Desktop/op_local_planner/local_map_ROI_obstacle.csv", std::ios::out | std::ios::trunc);
    localtraj_generator.allContourPoints.clear(); // 所有障碍物的轮廓点 
    for (double i = 2; i <= 3; i += 0.1)
    {
        for (double j = -0.5; j <= 0.5; j += 0.1)
        {
            UtilityNS::WayPoint obj_p;
            obj_p.pos.x = i;
            obj_p.pos.y = j;
            localtraj_generator.allContourPoints.push_back(obj_p);
            local_map_writer_obstacle << obj_p.pos.x << "  ";
            local_map_writer_obstacle << obj_p.pos.y;
            local_map_writer_obstacle << "\n";
        }
    }
    local_map_writer_obstacle.close();
    // 加入障碍物 结束



    localtraj_generator.generated_rollouts;
    localtraj_generator.generated_rollouts.clear();
    // 保存所有路径点到.csv
    std::ofstream local_map_writer;
    local_map_writer.open("/home/zy/Desktop/op_local_planner/local_map_ROI.csv", std::ios::out | std::ios::trunc);
    if (rollout_generator.local_lanes.lanes.size() > 0)
    {
        localtraj_generator.generated_rollouts.clear();
        for (size_t i = 0; i < rollout_generator.local_lanes.lanes.size(); i++)
        {
            std::vector<UtilityNS::WayPoint> rollout_singleLane;
            for (size_t k = 0; k < rollout_generator.local_lanes.lanes[i].waypoints.size(); k++)
            {
                UtilityNS::WayPoint wp;
                wp.pos.x = rollout_generator.local_lanes.lanes[i].waypoints[k].pose.pose.position.x;
                wp.pos.y = rollout_generator.local_lanes.lanes[i].waypoints[k].pose.pose.position.y;
                wp.pos.z = rollout_generator.local_lanes.lanes[i].waypoints[k].pose.pose.position.z;
                wp.pos.yaw = 0;
                rollout_singleLane.push_back(wp);
                local_map_writer << wp.pos.x << "  ";
                local_map_writer << wp.pos.y;
                local_map_writer << "\n";
            }
            localtraj_generator.generated_rollouts.push_back(rollout_singleLane);
        }
    }
    local_map_writer.close();

    printf(" rollout_generator.local_lanes.lanes.size() %d  \n", rollout_generator.local_lanes.lanes.size());
    printf(" localtraj_generator.generated_rollouts.lanes.size() %d  \n", localtraj_generator.generated_rollouts.size());

    // 保存中间路径点
    std::ofstream local_map_writer_center;
    local_map_writer_center.open("/home/zy/Desktop/op_local_planner/local_map_ROI_center.csv", std::ios::out | std::ios::trunc);
    // 赋值 localtraj_generator.centralPathSection
    rollout_generator.central_path_section;
    localtraj_generator.centralPathSection.clear();
    for (int i = 0; i < rollout_generator.central_path_section.waypoints.size(); i++)
    {
        UtilityNS::WayPoint p;
        p.pos.x = rollout_generator.central_path_section.waypoints[i].pose.pose.position.x;
        p.pos.y = rollout_generator.central_path_section.waypoints[i].pose.pose.position.y;
        p.pos.z = rollout_generator.central_path_section.waypoints[i].pose.pose.position.z;
        p.pos.yaw = rollout_generator.central_path_section.waypoints[i].yaw;
        localtraj_generator.centralPathSection.push_back(p);
        local_map_writer_center << p.pos.x << "  ";
        local_map_writer_center << p.pos.y;
        local_map_writer_center << "\n";
    }
    local_map_writer_center.close();

    // 主函数
    localtraj_generator.run();

    // if (rollout_generator.local_lanes.lanes.size() > 0)
    // {
    //     localtraj_generator.generated_rollouts.clear();
    //     for (size_t i = 0; i < rollout_generator.local_lanes.lanes.size(); i++)
    //     {
    //         for (size_t k = 0; k < rollout_generator.local_lanes.lanes[i].waypoints.size(); k++)
    //         {
    //             UtilityNS::WayPoint wp;
    //             wp.pos.x = rollout_generator.local_lanes.lanes[i].waypoints[k].pose.pose.position.x;
    //             wp.pos.y = rollout_generator.local_lanes.lanes[i].waypoints[k].pose.pose.position.y;
    //             wp.pos.z = rollout_generator.local_lanes.lanes[i].waypoints[k].pose.pose.position.z;
    //             wp.pos.yaw = 0;
    //             local_map_writer << wp.pos.x << "  ";
    //             local_map_writer << wp.pos.y;
    //             local_map_writer << "\n";
    //         }
    //     }
    // }

    // 保存最优路径点
    std::ofstream local_map_writer_best;
    local_map_writer_best.open("/home/zy/Desktop/op_local_planner/local_map_ROI_best.csv", std::ios::out | std::ios::trunc);
    for (size_t k = 0; k < localtraj_generator.best_local_trajectory.waypoints.size(); k++)
    {
        UtilityNS::WayPoint wp;
        wp.pos.x = localtraj_generator.best_local_trajectory.waypoints[k].pose.pose.position.x;
        wp.pos.y = localtraj_generator.best_local_trajectory.waypoints[k].pose.pose.position.y;
        wp.pos.z = localtraj_generator.best_local_trajectory.waypoints[k].pose.pose.position.z;
        wp.pos.yaw = 0;
        local_map_writer_best << wp.pos.x << "  ";
        local_map_writer_best << wp.pos.y;
        local_map_writer_best << "\n";
    }
    local_map_writer_best.close();

    return 0;
}
