// https://blog.csdn.net/weixin_43078345/article/details/103737910

// 速度规划——S-T图
// S-T Graph
// S-T Graph 是将有可能和path有overlap的障碍物投影到该path上面，生成st bounary
// 而速度规划则根据生成的st boundary进行纵向规划，其中s是指主车在该path上的行驶里程。
// S-T graph经常被用来做速度规划

#include <array>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <memory>
#include <future> // std::async, std::future
#include <chrono> // std::chrono::milliseconds

class Box2d
{
public:
  Box2d(const std::vector<double> &center, const double heading, const double length,
        const double width)
  {
    // std::cout << "Box2d  " << center[0] << "  " << center[1] << std::endl;
    center_ = (center);
    length_ = (length);
    width_ = (width);
    half_length_ = (length / 2.0);
    half_width_ = (width / 2.0);
    heading_ = (heading);
    cos_heading_ = (cos(heading));
    sin_heading_ = (sin(heading));
    InitCorners();
  }

  double center_x()
  {
    return center_[0];
  }

  double center_y()
  {
    return center_[1];
  }

  bool HasOverlap(Box2d box)
  {
  }
  double DistanceTo(Box2d &point)
  {

    double x_diff = center_[0] - point.center_[0];
    double y_diff = center_[1] - point.center_[1];

    double distance = hypot(y_diff, x_diff);

    // distance = 0.5;
    return distance;
  }

  void InitCorners()
  {
    const double dx1 = cos_heading_ * half_length_;
    const double dy1 = sin_heading_ * half_length_;
    const double dx2 = sin_heading_ * half_width_;
    const double dy2 = -cos_heading_ * half_width_;
    corners_.clear();

    std::vector<double> corner_point_1{center_[0] + dx1 + dx2, center_[1] + dy1 + dy2};
    std::vector<double> corner_point_2{center_[0] + dx1 - dx2, center_[1] + dy1 - dy2};
    std::vector<double> corner_point_3{center_[0] - dx1 - dx2, center_[1] - dy1 - dy2};
    std::vector<double> corner_point_4{center_[0] - dx1 + dx2, center_[1] - dy1 + dy2};

    corners_.push_back(corner_point_1);
    corners_.push_back(corner_point_2);
    corners_.push_back(corner_point_3);
    corners_.push_back(corner_point_4);

    for (auto &corner : corners_)
    {
      max_x_ = std::fmax(corner[0], max_x_);
      min_x_ = std::fmin(corner[0], min_x_);
      max_y_ = std::fmax(corner[1], max_y_);
      min_y_ = std::fmin(corner[1], min_y_);
    }
  }
  std::vector<double> center_;
  double length_ = 0.0;
  double width_ = 0.0;
  double half_length_ = 0.0;
  double half_width_ = 0.0;
  double heading_ = 0.0;
  double cos_heading_ = 1.0;
  double sin_heading_ = 0.0;

  double max_x_ = std::numeric_limits<double>::lowest();
  double min_x_ = std::numeric_limits<double>::max();
  double max_y_ = std::numeric_limits<double>::lowest();
  double min_y_ = std::numeric_limits<double>::max();

  std::vector<std::vector<double>> corners_;
};

// 数据部分
struct Waypoint
{
  Waypoint(const double _x, const double _y, const double _theta, const double _s)
      : x(_x), y(_y), theta(_theta), s(_s)
  {
  }
  double x;
  double y;
  double theta;
  double s;
};

struct DiscretizedPath
{
  explicit DiscretizedPath(const std::vector<Waypoint> &_waypoints) : points(_waypoints)
  {
  }
  DiscretizedPath() = default;
  std::vector<Waypoint> points;
};

struct TrajectoryPoint
{
  TrajectoryPoint(const Waypoint &_waypoint, const double _v, const double _relative_time)
      : waypoint(_waypoint), v(_v), relative_time(_relative_time)
  {
  }
  Waypoint waypoint;
  double v;
  double relative_time;
};

struct DiscretizedTrajectory
{
  explicit DiscretizedTrajectory(const std::vector<TrajectoryPoint> &_traj_points)
      : traj_points(_traj_points)
  {
  }
  DiscretizedTrajectory() = default;
  std::vector<TrajectoryPoint> traj_points;
};

// 障碍物
struct Obstacle
{
  Obstacle(const std::string &_id, const Box2d &_bounding_box, const bool _is_static,
           const DiscretizedTrajectory &_trajectory)
      : id(_id), bounding_box(_bounding_box), is_static(_is_static), trajectory(_trajectory)
  {
  }
  Obstacle(const std::string &_id, const Box2d &_bounding_box, const bool _is_static)
      : id(_id), bounding_box(_bounding_box), is_static(_is_static)
  {
  }
  std::string id;
  Box2d bounding_box;
  bool is_static;
  DiscretizedTrajectory trajectory;
};

// StBoundary
struct SpeedPoint
{
  SpeedPoint(const double _t, const double _s, double _v) : t(_t), s(_s), v(_v)
  {
  }

  void set_s(std::uint32_t s_)
  {
    s = s_;
  }

  void set_t(std::uint32_t t_)
  {
    t = t_;
  }

  void set_v(std::uint32_t v_)
  {
    v = v_;
  }

  double t;
  double s;
  double v;
};

// StBoundary
struct StPoint
{
  StPoint(const double _t, const double _s) : t(_t), s(_s)
  {
  }

  void set_s(std::uint32_t s_)
  {
    s = s_;
  }

  void set_t(std::uint32_t t_)
  {
    t = t_;
  }

  double t;
  double s;
};

struct SlPoint
{
  SlPoint(const double _s, const double _l) : s(_s), l(_l)
  {
  }
  double s;
  double l;
};

struct StGraphPoint
{
  StGraphPoint(StPoint &_st_point)
      : st_point(_st_point), pre_node(nullptr), cost(std::numeric_limits<double>::max())
  {
  }

  void Init(std::uint32_t index_t,
            std::uint32_t index_s, StPoint st_point)
  {
    index_t_ = index_t;
    index_s_ = index_s;
    st_point = st_point;
  }

  void SetPrePoint(StGraphPoint pre_node_)
  {
    pre_node = &pre_node_;
  }

  StPoint st_point;
  StGraphPoint *pre_node;

  void SetTotalCost(double cost_)
  {
    cost = cost_;
  }
  double cost;

  void SetObstacleCost(double ObstacleCost_)
  {
    ObstacleCost = ObstacleCost_;
  }
  double ObstacleCost;

  void SetSpatialPotentialCost(double SpatialPotentialCost_)
  {
    ObstacleCost = SpatialPotentialCost_;
  }
  double SpatialPotentialCost;

  std::uint32_t index_s_ = 0;
  std::uint32_t index_t_ = 0;

  void SetOptimalSpeed(double optimal_velocity_)
  {
    optimal_velocity = optimal_velocity_;
  }
  double optimal_velocity = 10;
};

class StBoundary
{
public:
  StBoundary();

  void Init(std::string obs_id, std::vector<StPoint> lower_points,
            std::vector<StPoint> upper_points);

  bool Evaluate(const double t, double *const lower_s, double *const upper_s) const;

  std::string id() const
  {
    return obs_id_;
  }

private:
  bool is_init_ = false;
  std::string obs_id_;
  std::vector<StPoint> lower_points_;
  std::vector<StPoint> upper_points_;
};

StBoundary::StBoundary()
{
  is_init_ = false;
}

void StBoundary::Init(std::string obs_id, std::vector<StPoint> lower_points,
                      std::vector<StPoint> upper_points)
{
  // CHECK_EQ(lower_points.size(), upper_points.size());
  // CHECK_GE(lower_points.size(), 2);

  obs_id_ = obs_id;
  lower_points_ = lower_points;
  upper_points_ = upper_points;
  is_init_ = true;
}

bool StBoundary::Evaluate(const double t, double *const lower_s, double *const upper_s) const
{
  // CHECK_NOTNULL(lower_s);
  // CHECK_NOTNULL(upper_s);
  // CHECK(is_init_);
  if (t < lower_points_.front().t)
  {
    return false;
  }
  if (t > lower_points_.back().t)
  {
    return false;
  }

  auto func = [](const StPoint &st_point, const double t) { return st_point.t < t; };
  const auto &lower_iter = std::lower_bound(lower_points_.begin(), lower_points_.end(), t, func);
  if (lower_iter != lower_points_.end())
  {
    *lower_s = lower_iter->s;
  }
  else
  {
    return false;
  }
  const auto &upper_iter = std::lower_bound(upper_points_.begin(), upper_points_.end(), t, func);
  if (upper_iter != upper_points_.end())
  {
    *upper_s = upper_iter->s;
  }
  else
  {
    return false;
  }
  return true;
}

// S-T Graph
class StGraph final
{
public:
  StGraph(const DiscretizedPath &path, const std::vector<Obstacle> &obstacles);

  bool GetAllObstacleStBoundary(std::vector<StBoundary> *const st_boundaries) const;

  bool GetObstacleStBoundary(const std::string &obs_id, StBoundary *const st_boundary) const;

  bool GetAllBlockedSRangesByT(const double t,
                               std::vector<std::pair<double, double>> *const blocked_ranges) const;

  bool GetBlockedSRangeByT(const double t, const StBoundary &st_boundary,
                           std::pair<double, double> *blocked_range) const;

private:
  void CalculateAllObstacleStBoundary(const std::vector<Obstacle> &obstacles);

  bool CalculateObstacleStBoundary(const Obstacle &obs, StBoundary *const st_boundary) const;

  bool CalculateStaticObstacleStBoundary(const std::string &obs_id, const Box2d &obs_box,
                                         StBoundary *const st_boundary) const;

  bool CalculateDynamicObstacleStBoundary(const Obstacle &obs, StBoundary *const st_boundary) const;

  std::vector<Waypoint> GetWaypointsWithinDistance(const double x, const double y,
                                                   const double radius) const;

  bool GetBlockedSRange(const Box2d &obs_box, double *const lower_s, double *const upper_s) const;

private:
  std::unordered_map<std::string, StBoundary> obs_st_boundary_;
  DiscretizedPath discretized_path_;

  const double veh_heading_ = M_PI / 4.0;
  const double veh_length_ = 2.0;
  const double veh_width_ = 1.0;
  const double time_range_ = 4.0;
};

StGraph::StGraph(const DiscretizedPath &path, const std::vector<Obstacle> &obstacles)
    : discretized_path_(path)
{
  // CHECK_GE(discretized_path_.points.size(), 2);

  obs_st_boundary_.clear();
  CalculateAllObstacleStBoundary(obstacles);
}

bool StGraph::GetAllObstacleStBoundary(std::vector<StBoundary> *const st_boundaries) const
{
  // CHECK_NOTNULL(st_boundaries);

  for (auto iter = obs_st_boundary_.begin(); iter != obs_st_boundary_.end(); ++iter)
  {
    st_boundaries->emplace_back(iter->second);
  }
  return true;
}

bool StGraph::GetObstacleStBoundary(const std::string &obs_id,
                                    StBoundary *const st_boundary) const
{
  // CHECK_NOTNULL(st_boundary);

  const auto &iter = obs_st_boundary_.find(obs_id);
  if (iter == obs_st_boundary_.end())
  {
    return false;
  }
  *st_boundary = iter->second;
  return true;
}

bool StGraph::GetAllBlockedSRangesByT(
    const double t, std::vector<std::pair<double, double>> *const blocked_ranges) const
{
  // CHECK_NOTNULL(blocked_ranges);
  std::vector<StBoundary> st_boundaries;
  GetAllObstacleStBoundary(&st_boundaries);

  for (const auto &st_boundary : st_boundaries)
  {
    std::pair<double, double> blocked_range;
    if (GetBlockedSRangeByT(t, st_boundary, &blocked_range))
    {
      blocked_ranges->emplace_back(blocked_range);
    }
  }
  return true;
}

bool StGraph::GetBlockedSRangeByT(const double t, const StBoundary &st_boundary,
                                  std::pair<double, double> *blocked_range) const
{
  // CHECK_NOTNULL(blocked_range);
  double lower_s = 0.0;
  double upper_s = 0.0;
  if (st_boundary.Evaluate(t, &lower_s, &upper_s))
  {
    *blocked_range = std::make_pair(lower_s, upper_s);
    return true;
  }
  return false;
}

void StGraph::CalculateAllObstacleStBoundary(const std::vector<Obstacle> &obstacles)
{
  for (const auto &obstacle : obstacles)
  {
    const auto &iter = obs_st_boundary_.find(obstacle.id);
    // CHECK(iter == obs_st_boundary_.end());
    StBoundary st_boundary;
    if (!CalculateObstacleStBoundary(obstacle, &st_boundary))
    {
      // AWARN << "Failed to get obstacle: " << obstacle.id << " st_boundary. ";
      continue;
    }
    obs_st_boundary_.insert(std::make_pair(obstacle.id, st_boundary));
  }
}

bool StGraph::CalculateObstacleStBoundary(const Obstacle &obstacle,
                                          StBoundary *const st_boundary) const
{
  // CHECK_NOTNULL(st_boundary);

  if (obstacle.is_static)
  {
    return CalculateStaticObstacleStBoundary(obstacle.id, obstacle.bounding_box, st_boundary);
  }
  else
  {
    return CalculateDynamicObstacleStBoundary(obstacle, st_boundary);
  }
}

bool StGraph::CalculateStaticObstacleStBoundary(const std::string &obs_id, const Box2d &obs_box,
                                                StBoundary *const st_boundary) const
{
  // CHECK_NOTNULL(st_boundary);

  double lower_s = 0.0;
  double upper_s = 0.0;
  if (!GetBlockedSRange(obs_box, &lower_s, &upper_s))
  {
    return false;
  }
  std::vector<StPoint> lower_points{StPoint(0.0, lower_s), StPoint(time_range_, lower_s)};
  std::vector<StPoint> upper_points{StPoint(0.0, upper_s), StPoint(time_range_, upper_s)};
  st_boundary->Init(obs_id, lower_points, upper_points);
  return true;
}

bool StGraph::GetBlockedSRange(const Box2d &obs_box, double *const lower_s,
                               double *const upper_s) const
{
  // CHECK_NOTNULL(lower_s);
  // CHECK_NOTNULL(upper_s);

  const double radius = 5.0;
  double radiAus = 2;
  const auto &points = GetWaypointsWithinDistance(obs_box.center_[0], obs_box.center_[1], radiAus);
  if (points.empty())
  {
    // ADEBUG << "Obstacle is not on the path. ";
    return false;
  }

  bool is_updated = false;

  for (auto iter = points.begin(); iter != points.end(); ++iter)
  {
    Box2d veh_box({iter->x, iter->y}, veh_heading_, veh_length_, veh_width_);
    if (veh_box.HasOverlap(obs_box))
    {
      iter = iter == points.begin() ? iter : iter - 1;
      *lower_s = iter->s;
      is_updated = true;
      break;
    }
  }

  if (!is_updated)

  {
    // ADEBUG << "There is no collision with obstacle. ";
    return false;
  }

  for (auto iter = points.rbegin(); iter != points.rend(); ++iter)
  {
    Box2d veh_box({iter->x, iter->y}, veh_heading_, veh_length_, veh_width_);
    if (veh_box.HasOverlap(obs_box))
    {
      iter = iter == points.rbegin() ? iter : iter - 1;
      *upper_s = iter->s;
      break;
    }
  }
  // CHECK_GE(*upper_s, *lower_s) << "upper_s: " << *upper_s << ", lower_s: " << *lower_s;
  return true;
}

bool StGraph::CalculateDynamicObstacleStBoundary(const Obstacle &obstacle,
                                                 StBoundary *const st_boundary) const
{
  // CHECK_NOTNULL(st_boundary);
  // CHECK_GE(obstacle.trajectory.traj_points.size(), 2);

  bool has_st_boundary = false;
  std::vector<StPoint> lower_points;
  std::vector<StPoint> upper_points;
  for (const auto &p : obstacle.trajectory.traj_points)
  {
    Box2d obs_box({p.waypoint.x, p.waypoint.y}, p.waypoint.theta, obstacle.bounding_box.length_,
                  obstacle.bounding_box.width_);
    double lower_s = 0.0;
    double upper_s = 0.0;
    if (GetBlockedSRange(obs_box, &lower_s, &upper_s))
    {
      lower_points.emplace_back(p.relative_time, lower_s);
      upper_points.emplace_back(p.relative_time, upper_s);
      has_st_boundary = true;
    }
  }
  st_boundary->Init(obstacle.id, lower_points, upper_points);
  return has_st_boundary;
}

std::vector<Waypoint> StGraph::GetWaypointsWithinDistance(const double x, const double y,
                                                          const double radius) const
{
  std::vector<Waypoint> nearest_points;
  for (const auto &p : discretized_path_.points)
  {
    if (std::hypot(p.x - x, p.y - y) < radius)
    {
      nearest_points.emplace_back(p);
    }
  }
  return nearest_points;
}

void DisplayStGraph(const std::vector<StBoundary> &st_boundaries)
{
}

// 数据

double FLAGS_planning_upper_speed_limit = 15;
static constexpr double kDoubleEpsilon = 1.0e-6;
double unit_t_ = 1.0;
double total_length_t_ = 10;
double total_length_s_ = 200;
double dense_dimension_s_ = 101;

double sparse_unit_s_ = 1.0;
double dense_unit_s_ = 0.1;

double max_acceleration_ = 2.0;
double max_deceleration_ = -4.0;

uint32_t dimension_t_;

uint32_t dimension_s_;
std::vector<std::vector<StGraphPoint>> cost_table_;
std::vector<double> speed_limit_by_index_;
std::vector<double> spatial_distance_by_index_;

bool InitCostTable()
{
  // Time dimension is homogeneous while Spatial dimension has two resolutions,
  // dense and sparse with dense resolution coming first in the spatial horizon

  dimension_t_ = static_cast<uint32_t>(std::ceil(
                     total_length_t_ / static_cast<double>(unit_t_))) +
                 1;

  double sparse_length_s =
      total_length_s_ -
      static_cast<double>(dense_dimension_s_ - 1) * dense_unit_s_;

  uint32_t sparse_dimension_s_ =
      sparse_length_s > std::numeric_limits<double>::epsilon()
          ? static_cast<uint32_t>(std::ceil(sparse_length_s / sparse_unit_s_))
          : 0;
  dense_dimension_s_ =
      sparse_length_s > std::numeric_limits<double>::epsilon()
          ? dense_dimension_s_
          : static_cast<uint32_t>(std::ceil(total_length_s_ / dense_unit_s_)) +
                1;
  dimension_s_ = dense_dimension_s_ + sparse_dimension_s_;

  // Sanity Check
  if (dimension_t_ < 1 || dimension_s_ < 1)
  {
    const std::string msg = "Dp st cost table size incorrect.";
    return false;
  }

  cost_table_.clear();
  StPoint st_point(0, 0);
  cost_table_ = std::vector<std::vector<StGraphPoint>>(
      dimension_t_, std::vector<StGraphPoint>(dimension_s_, StGraphPoint(st_point)));

  double curr_t = 0.0;
  for (uint32_t i = 0; i < cost_table_.size(); ++i, curr_t += unit_t_)
  {
    auto &cost_table_i = cost_table_[i];
    double curr_s = 0.0;
    for (uint32_t j = 0; j < dense_dimension_s_; ++j, curr_s += dense_unit_s_)
    {
      cost_table_i[j].Init(i, j, StPoint(curr_s, curr_t));
    }
    curr_s = static_cast<double>(dense_dimension_s_ - 1) * dense_unit_s_ +
             sparse_unit_s_;
    for (uint32_t j = dense_dimension_s_; j < cost_table_i.size();
         ++j, curr_s += sparse_unit_s_)
    {
      cost_table_i[j].Init(i, j, StPoint(curr_s, curr_t));
    }
  }

  const auto &cost_table_0 = cost_table_[0]; //第一列数据
  spatial_distance_by_index_.clear();
  spatial_distance_by_index_ = std::vector<double>(cost_table_0.size(), 0.0);
  for (uint32_t i = 0; i < cost_table_0.size(); ++i)
  {
    spatial_distance_by_index_[i] = cost_table_0[i].st_point.s;
  }
  return true;
}

bool InitSpeedLimitLookUp()
{
  speed_limit_by_index_.clear();

  speed_limit_by_index_.resize(dimension_s_);

  // const auto& speed_limit = st_graph_data_.speed_limit();

  // for (uint32_t i = 0; i < dimension_s_; ++i) {
  //   speed_limit_by_index_[i] =
  //       speed_limit.GetSpeedLimitByS(cost_table_[0][i].point().s());
  // }
  return true;
}

double GetObstacleCost(const StGraphPoint st_graph_point)
{

  return 1;
}

bool CalculateCostAt(size_t c, size_t r)
{
  //   const uint32_t c = c;
  // const uint32_t r = r;
  auto cost_cr = cost_table_[c][r];
  // if ((c - 1) >= 0)
  // {
  //   cost_cr.SetPrePoint(cost_table_[c - 1][r]);
  // }
  // else
  // {
  //   cost_cr.SetPrePoint(cost_table_[0][r]);
  // }

  if (1)
  {
    // dp_st_cost_.GetObstacleCost(cost_cr)
    double ObstacleCost_ = GetObstacleCost(cost_cr);
    cost_cr.SetObstacleCost(ObstacleCost_);
    if (cost_cr.ObstacleCost > std::numeric_limits<double>::max())
    {
      return true;
    }

    // dp_st_cost_.GetSpatialPotentialCost(cost_cr)
    double SpatialPotentialCost = 0;
    cost_cr.SetSpatialPotentialCost(SpatialPotentialCost);

    const auto &cost_init = cost_table_[0][0];
    double init_point_v = 0;
    if (c == 0)
    {
      cost_cr.SetTotalCost(0.0);

      cost_cr.SetOptimalSpeed(init_point_v);
      return true;
    }

    const double speed_limit = speed_limit_by_index_[r];
    double st_graph_data_cruise_speed = 10;
    const double cruise_speed = st_graph_data_cruise_speed;
    // The mininal s to model as constant acceleration formula
    // default: 0.25 * 7 = 1.75 m
    const double min_s_consider_speed = dense_unit_s_ * dimension_t_;

    if (c == 1)
    {
      const double acc =
          2 * (cost_cr.st_point.s / unit_t_ - init_point_v) / unit_t_;
      if (acc < max_deceleration_ || acc > max_acceleration_)
      {
        return true;
      }

      if (init_point_v + acc * unit_t_ < -kDoubleEpsilon &&
          cost_cr.st_point.s > min_s_consider_speed)
      {
        return true;
      }

      // if (CheckOverlapOnDpStGraph(st_graph_data_.st_boundaries(), cost_cr,
      //                             cost_init)) {
      //   return;
      // }

      cost_cr.SetTotalCost(
          cost_cr.ObstacleCost + cost_cr.SpatialPotentialCost +
          cost_init.cost /*+
        CalculateEdgeCostForSecondCol(r, speed_limit, cruise_speed)*/
      );

      cost_cr.SetPrePoint(cost_init);
      cost_cr.SetOptimalSpeed(init_point_v + acc * unit_t_);
      return true;
    }

    static constexpr double kSpeedRangeBuffer = 0.20;
    const double pre_lowest_s =
        cost_cr.st_point.s -
        FLAGS_planning_upper_speed_limit * (1 + kSpeedRangeBuffer) * unit_t_;
    const auto pre_lowest_itr =
        std::lower_bound(spatial_distance_by_index_.begin(),
                         spatial_distance_by_index_.end(), pre_lowest_s);
    uint32_t r_low = 0;
    if (pre_lowest_itr == spatial_distance_by_index_.end())
    {
      r_low = dimension_s_ - 1;
    }
    else
    {
      r_low = static_cast<uint32_t>(
          std::distance(spatial_distance_by_index_.begin(), pre_lowest_itr));
    }
    const uint32_t r_pre_size = r - r_low + 1;
    const auto &pre_col = cost_table_[c - 1];
    double curr_speed_limit = speed_limit;

    if (c == 2)
    {
      for (uint32_t i = 0; i < r_pre_size; ++i)
      {
        uint32_t r_pre = r - i;
        if (std::isinf(pre_col[r_pre].cost) ||
            pre_col[r_pre].pre_node == nullptr)
        {
          continue;
        }
        // TODO(Jiaxuan): Calculate accurate acceleration by recording speed
        // data in ST point.
        // Use curr_v = (point.s - pre_point.s) / unit_t as current v
        // Use pre_v = (pre_point.s - prepre_point.s) / unit_t as previous v
        // Current acc estimate: curr_a = (curr_v - pre_v) / unit_t
        // = (point.s + prepre_point.s - 2 * pre_point.s) / (unit_t * unit_t)
        const double curr_a =
            2 *
            ((cost_cr.st_point.s - pre_col[r_pre].st_point.s) / unit_t_ -
             pre_col[r_pre].optimal_velocity) /
            unit_t_;
        if (curr_a < max_deceleration_ || curr_a > max_acceleration_)
        {
          continue;
        }

        if (pre_col[r_pre].optimal_velocity + curr_a * unit_t_ <
                -kDoubleEpsilon &&
            cost_cr.st_point.s > min_s_consider_speed)
        {
          continue;
        }

        // Filter out continuous-time node connection which is in collision with
        // obstacle
        // if (CheckOverlapOnDpStGraph(st_graph_data_.st_boundaries(), cost_cr,
        //                             pre_col[r_pre])) {
        //   continue;
        // }

        curr_speed_limit =
            std::fmin(curr_speed_limit, speed_limit_by_index_[r_pre]);
        const double cost = cost_cr.ObstacleCost +
                            cost_cr.SpatialPotentialCost +
                            pre_col[r_pre].cost /* +
                          CalculateEdgeCostForThirdCol(
                              r, r_pre, curr_speed_limit, cruise_speed)*/
            ;

        if (cost < cost_cr.cost)
        {
          cost_cr.SetTotalCost(cost);
          cost_cr.SetPrePoint(pre_col[r_pre]);
          cost_cr.SetOptimalSpeed(pre_col[r_pre].optimal_velocity +
                                  curr_a * unit_t_);
        }
      }
      return true;
    }

    for (uint32_t i = 0; i < r_pre_size; ++i)
    {
      uint32_t r_pre = r - i;
      if (std::isinf(pre_col[r_pre].cost) ||
          pre_col[r_pre].pre_node == nullptr)
      {
        continue;
      }
      // Use curr_v = (point.s - pre_point.s) / unit_t as current v
      // Use pre_v = (pre_point.s - prepre_point.s) / unit_t as previous v
      // Current acc estimate: curr_a = (curr_v - pre_v) / unit_t
      // = (point.s + prepre_point.s - 2 * pre_point.s) / (unit_t * unit_t)
      const double curr_a =
          2 *
          ((cost_cr.st_point.s - pre_col[r_pre].st_point.s) / unit_t_ -
           pre_col[r_pre].optimal_velocity) /
          unit_t_;
      if (curr_a > max_acceleration_ || curr_a < max_deceleration_)
      {
        continue;
      }

      if (pre_col[r_pre].optimal_velocity + curr_a * unit_t_ < -kDoubleEpsilon &&
          cost_cr.st_point.s > min_s_consider_speed)
      {
        continue;
      }

      // if (CheckOverlapOnDpStGraph(st_graph_data_.st_boundaries(), cost_cr,
      //                             pre_col[r_pre])) {
      //   continue;
      // }

      uint32_t r_prepre = pre_col[r_pre].pre_node->index_s_;
      const StGraphPoint &prepre_graph_point = cost_table_[c - 2][r_prepre];
      if (std::isinf(prepre_graph_point.cost))
      {
        continue;
      }

      if (!prepre_graph_point.pre_node)
      {
        continue;
      }
      const StPoint &triple_pre_point = prepre_graph_point.pre_node->st_point;
      const StPoint &prepre_point = prepre_graph_point.st_point;
      const StPoint &pre_point = pre_col[r_pre].st_point;
      const StPoint &curr_point = cost_cr.st_point;
      curr_speed_limit =
          std::fmin(curr_speed_limit, speed_limit_by_index_[r_pre]);
      double cost = cost_cr.ObstacleCost + cost_cr.SpatialPotentialCost +
                    pre_col[r_pre].cost /* +
                  CalculateEdgeCost(triple_pre_point, prepre_point, pre_point,
                                    curr_point, curr_speed_limit, cruise_speed)*/
          ;

      if (cost < cost_cr.cost)
      {
        cost_cr.SetTotalCost(cost);
        cost_cr.SetPrePoint(pre_col[r_pre]);
        cost_cr.SetOptimalSpeed(pre_col[r_pre].optimal_velocity +
                                curr_a * unit_t_);
      }
    }
  }
  return 1;
}

void GetRowRange(StGraphPoint point,
                 size_t next_highest_row,
                 size_t next_lowest_row)
{
  double v0 = 0.0;
  // TODO(all): Record speed information in StGraphPoint and deprecate this.
  // A scaling parameter for DP range search due to the lack of accurate
  // information of the current velocity (set to 1 by default since we use
  // past 1 second's average v as approximation)
  double acc_coeff = 0.5;
  if (!point.pre_node)
  {
    v0 = 0;
  }
  else
  {
    // opitmal_speed;
    v0 = 10;
  }

  const auto max_s_size = dimension_s_ - 1;
  const double t_squared = unit_t_ * unit_t_;
  const double s_upper_bound = v0 * unit_t_ +
                               acc_coeff * max_acceleration_ * t_squared +
                               point.st_point.s;

  const auto next_highest_itr =
      std::lower_bound(spatial_distance_by_index_.begin(),
                       spatial_distance_by_index_.end(), s_upper_bound);
  if (next_highest_itr == spatial_distance_by_index_.end())
  {
    next_highest_row = max_s_size;
  }
  else
  {
    next_highest_row =
        std::distance(spatial_distance_by_index_.begin(), next_highest_itr);
  }

  const double s_lower_bound =
      std::fmax(0.0, v0 * unit_t_ + acc_coeff * max_deceleration_ * t_squared) +
      point.st_point.s;
  const auto next_lowest_itr =
      std::lower_bound(spatial_distance_by_index_.begin(),
                       spatial_distance_by_index_.end(), s_lower_bound);
  if (next_lowest_itr == spatial_distance_by_index_.end())
  {
    next_lowest_row = max_s_size;
  }
  else
  {
    next_lowest_row =
        std::distance(spatial_distance_by_index_.begin(), next_lowest_itr);
  }
}

bool CalculateTotalCost()
{

  size_t next_highest_row = 0;
  size_t next_lowest_row = 0;

  // CalculateTotalCost()的外层循环是
  for (size_t c = 0; c < cost_table_.size(); ++c)
  {
    size_t highest_row = 0;
    size_t lowest_row = cost_table_.back().size() - 1;

    int count = static_cast<int>(next_highest_row) -
                static_cast<int>(next_lowest_row) + 1;
    if (count > 0)
    {
      std::vector<std::future<void>> results;

      for (size_t r = highest_row; r <= lowest_row; ++r)
      {
        CalculateCostAt(c, r);
      }

      // CalculateTotalCost()的内层循环
      for (size_t r = next_lowest_row; r <= next_highest_row; ++r)
      {
        const auto &cost_cr = cost_table_[c][r];
        if (cost_cr.cost < std::numeric_limits<double>::infinity())
        {
          size_t h_r = 0;
          size_t l_r = 0;
          GetRowRange(cost_cr, h_r, l_r);
          highest_row = std::max(highest_row, h_r);
          lowest_row = std::min(lowest_row, l_r);
        }
      }
      next_highest_row = highest_row;
      next_lowest_row = lowest_row;
    }

    return true;
  }
}

bool RetrieveSpeedProfile()
{

  double min_cost = std::numeric_limits<double>::infinity();
   StGraphPoint *best_end_point = nullptr;

  int jj = 0;
  for ( StGraphPoint &cur_point : cost_table_.back())
  {
    if (!std::isinf(cur_point.cost &&
                    cur_point.cost < min_cost))
    {
      best_end_point = &cur_point;
      min_cost = cur_point.cost;
    }
    jj++;
  }
  std::cout << "jj   " << jj << std::endl;

  std::cout << "cost_table_.size()   " << cost_table_.size() << std::endl;
  std::cout << "cost_table_.[2].size()  " << cost_table_[2].size() << std::endl;
  // int ii=0;
  //   for ( auto &row : cost_table_)
  //   {
  //      StGraphPoint &cur_point = row.back();
  //     if (!std::isinf(cur_point.cost &&
  //                     cur_point.cost < min_cost))
  //     {
  //       best_end_point = &cur_point;
  //       min_cost = cur_point.cost;
  //     }
  //     ii++;
  //   }
  // std::cout<<"ii   "<<ii<<std::endl;

  if (best_end_point == nullptr)
  {
    return false;
  }

  // 以cur_point为当前的node一直往前搜索,直到 node==nullptr
  std::vector<SpeedPoint> speed_profile;
   StGraphPoint *cur_point = best_end_point;

cur_point->SetPrePoint(cost_table_[2][100]);


  int kk = 0;
  while (cur_point != nullptr)
  {
    SpeedPoint speed_point(0, 0, 0);
    speed_point.set_s(cur_point->st_point.s);
    speed_point.set_t(cur_point->st_point.t);
    speed_profile.push_back(speed_point);
    cur_point = cur_point->pre_node;
    kk++;
  }
  std::cout << "kk   " << kk << std::endl;
  std::reverse(speed_profile.begin(), speed_profile.end());

  static constexpr double kEpsilon = std::numeric_limits<double>::epsilon();
  if (speed_profile.front().t > kEpsilon ||
      speed_profile.front().s > kEpsilon)
  {
    return false;
  }

  for (size_t i = 0; i + 1 < speed_profile.size(); ++i)
  {
    const double v = (speed_profile[i + 1].s - speed_profile[i].s) /
                     (speed_profile[i + 1].t - speed_profile[i].t + 1e-3);
    speed_profile[i].set_v(v);
  }

  std::cout << "speed_profile.size()  " << speed_profile.size() << std::endl;
  for (int i = 0; i < speed_profile.size(); i++)
  {

    std::cout << "index, (s,t,v)  " << i << " (" << speed_profile[i].s << " " << speed_profile[i].t << " "
              << speed_profile[i].v << "  )" << std::endl;
  }

  // *speed_data = SpeedData(speed_profile);
  return true;
}

bool DP_speed_Search(std::vector<StBoundary> st_boundaries)
{
  static constexpr double kBounadryEpsilon = 1e-2;

  // 遍历的是STGraph中所有的boundary，每一个障碍物都会生成一个对应的boundary，这里就是将所有障碍的boundary都判断一遍
  for (const auto &boundary : st_boundaries)
  {
    // KeepClear obstacles not considered in Dp St decision

    //   // If init point in collision with obstacle, return speed fallback
    //   if (boundary->IsPointInBoundary({0.0, 0.0}) ||
    //       (std::fabs(boundary->min_t()) < kBounadryEpsilon &&
    //        std::fabs(boundary->min_s()) < kBounadryEpsilon))
    //   {
    //     dimension_t_ = static_cast<uint32_t>(std::ceil(
    //                        total_length_t_ / static_cast<double>(unit_t_))) +
    //                    1;
    //     std::vector<SpeedPoint> speed_profile;
    //     double t = 0.0;
    //     for (uint32_t i = 0; i < dimension_t_; ++i, t += unit_t_)
    //     {
    //       speed_profile.push_back(PointFactory::ToSpeedPoint(0, t));
    //     }
    //     *speed_data = SpeedData(speed_profile);
    //     return Status::OK();
    //   }
    // }
  }

  if (!InitCostTable())
  {
    // return false;
  }

  if (!InitSpeedLimitLookUp())
  {
    // return false;
  }

  if (!CalculateTotalCost())
  {
    // return false;
  }

  if (!RetrieveSpeedProfile())
  {
    // return false;
  }

  std::cout << "DP Speed Search " << std::endl;
  return true;
}

int main()
{

  std::vector<Waypoint> points;
  std::shared_ptr<DiscretizedPath> path_;
  for (double x = 0.0; x < 20; x += 0.1)
  {
    points.emplace_back(x, x, M_PI / 4.0, std::hypot(x, x));
  }
  path_ = std::make_shared<DiscretizedPath>(points);

  // std::vector<Obstacle> obstacles;
  // StGraph st_graph(*path_, obstacles);

  // std::vector<StBoundary> st_boundaries;
  // st_graph.GetAllObstacleStBoundary(&st_boundaries);
  // // EXPECT_TRUE(st_boundaries.empty());
  // std::cout << "should be true   " << st_boundaries.empty() << std::endl;

  // std::string id = "1";
  // StBoundary st_boundary;
  // // EXPECT_TRUE(!st_graph.GetObstacleStBoundary(id, &st_boundary));
  // std::cout << "should be true   " << !st_graph.GetObstacleStBoundary(id, &st_boundary) << std::endl;

  // double t = 0.0;
  // std::vector<std::pair<double, double>> blocked_ranges;
  // st_graph.GetAllBlockedSRangesByT(t, &blocked_ranges);
  // // EXPECT_TRUE(blocked_ranges.empty());
  // std::cout << "should be true   " << (blocked_ranges.empty()) << std::endl;

  // Box2d obs_box_1({5.0, 5.0}, M_PI / 4.0, 2.0, 1.0);
  // Box2d obs_box_2({5.0, 5.0}, M_PI / 2, 2.0, 1.0);
  // Obstacle obs_1("1", obs_box_1, true);
  // Obstacle obs_2("2", obs_box_2, true);
  // StGraph st_graph(*path_, std::vector<Obstacle>{obs_1, obs_2});

  // std::vector<StBoundary> st_boundaries;
  // st_graph.GetAllObstacleStBoundary(&st_boundaries);
  // // EXPECT_TRUE(!st_boundaries.empty());
  // std::cout << "should be true   " << (!st_boundaries.empty()) << std::endl;
  // std::string id = "2";
  // StBoundary st_boundary;
  // // EXPECT_TRUE(st_graph.GetObstacleStBoundary(id, &st_boundary));
  // std::cout << "should be true   " << (st_graph.GetObstacleStBoundary(id, &st_boundary)) << std::endl;
  // double lower_s = 0.0;
  // double upper_s = 0.0;
  // // st_boundary.Evaluate(3.0, &lower_s, &upper_s);
  // // EXPECT_EQ(lower_s, 5 * std::sqrt(2.0) - 2.0);
  // // EXPECT_EQ(upper_s, 5 * std::sqrt(2.0) + 2.0);

  // std::cout << "should be true   " << (lower_s == (5 * std::sqrt(2.0) - 2.0)) << std::endl;
  // std::cout << "should be true   " << (upper_s == (5 * std::sqrt(2.0) + 2.0)) << std::endl;

  // double t = 0.0;
  // std::vector<std::pair<double, double>> blocked_ranges;
  // st_graph.GetAllBlockedSRangesByT(t, &blocked_ranges);
  // // EXPECT_TRUE(!blocked_ranges.empty());
  // std::cout << "should be true   " << (!blocked_ranges.empty()) << std::endl;

  //////////////////////////////////////////////////////
  std::vector<StBoundary> st_boundaries_debug;
  StBoundary st_boundary_1;
  StBoundary st_boundary_2;
  StBoundary st_boundary_3;

  StPoint lower_point(0.0, 0.0);
  StPoint upper_point(1.0, 1.0);
  std::vector<StPoint> lower_points;
  std::vector<StPoint> upper_points;

  lower_points.push_back(lower_point);
  upper_points.push_back(upper_point);

  st_boundary_1.Init("1", lower_points, upper_points);
  st_boundary_1.Init("2", lower_points, upper_points);
  st_boundary_1.Init("3", lower_points, upper_points);

  st_boundaries_debug.push_back(st_boundary_1);
  st_boundaries_debug.push_back(st_boundary_2);
  st_boundaries_debug.push_back(st_boundary_3);

  // DP用于速度规划
  DP_speed_Search(st_boundaries_debug);
  std::cout << "End DP_speed " << std::endl;
  return 0;
}
