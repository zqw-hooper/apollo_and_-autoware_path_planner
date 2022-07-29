
// https://blog.csdn.net/weixin_43078345/article/details/87886933#t4

#include <array>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <memory>
#include <cmath>

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

  bool HasOverlap(Box2d &box)
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

  double center_x()
  {
    return center_[0];
  }

  double center_y()
  {
    return center_[1];
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

class QuinticPolynomialCurve1d
{

public:
  QuinticPolynomialCurve1d(
      const double x0, const double dx0, const double ddx0, const double x1,
      const double dx1, const double ddx1, const double param)
  {
    ComputeCoefficients(x0, dx0, ddx0, x1, dx1, ddx1, param);
    start_condition_[0] = x0;
    start_condition_[1] = dx0;
    start_condition_[2] = ddx0;
    end_condition_[0] = x1;
    end_condition_[1] = dx1;
    end_condition_[2] = ddx1;
    param_ = param;
  }

  double Evaluate(const uint32_t order, const double p)
  {
    switch (order)
    {
    case 0:
    {
      return ((((coef_[5] * p + coef_[4]) * p + coef_[3]) * p + coef_[2]) * p +
              coef_[1]) *
                 p +
             coef_[0];
    }
    case 1:
    {
      return (((5.0 * coef_[5] * p + 4.0 * coef_[4]) * p + 3.0 * coef_[3]) * p +
              2.0 * coef_[2]) *
                 p +
             coef_[1];
    }
    case 2:
    {
      return (((20.0 * coef_[5] * p + 12.0 * coef_[4]) * p) + 6.0 * coef_[3]) *
                 p +
             2.0 * coef_[2];
    }
    case 3:
    {
      return (60.0 * coef_[5] * p + 24.0 * coef_[4]) * p + 6.0 * coef_[3];
    }
    case 4:
    {
      return 120.0 * coef_[5] * p + 24.0 * coef_[4];
    }
    case 5:
    {
      return 120.0 * coef_[5];
    }
    default:
      return 0.0;
    }
  }

  void ComputeCoefficients(
      const double x0, const double dx0, const double ddx0, const double x1,
      const double dx1, const double ddx1, const double p)
  {

    coef_[0] = x0;
    coef_[1] = dx0;
    coef_[2] = ddx0 / 2.0;

    const double p2 = p * p;
    const double p3 = p * p2;

    // the direct analytical method is at least 6 times faster than using matrix
    // inversion.
    const double c0 = (x1 - 0.5 * p2 * ddx0 - dx0 * p - x0) / p3;
    const double c1 = (dx1 - ddx0 * p - dx0) / p2;
    const double c2 = (ddx1 - ddx0) / p;

    coef_[3] = 0.5 * (20.0 * c0 - 8.0 * c1 + c2);
    coef_[4] = (-15.0 * c0 + 7.0 * c1 - c2) / p;
    coef_[5] = (6.0 * c0 - 3.0 * c1 + 0.5 * c2) / p2;
  }

  std::array<double, 6> coef_{{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
  std::array<double, 3> start_condition_{{0.0, 0.0, 0.0}};
  std::array<double, 3> end_condition_{{0.0, 0.0, 0.0}};
  double param_ = 0.0;
};

// node.h file
struct SlPoint
{
  SlPoint(const double _s, const double _l) : s(_s), l(_l)
  {
  }
  double s;
  double l;
};

struct Node
{
  Node(const SlPoint &_sl_point)
      : sl_point(_sl_point), pre_node(nullptr), cost(std::numeric_limits<double>::max())
  {
  }
  SlPoint sl_point;
  Node *pre_node;
  double cost;
};

// class DpPath file
class DpPath final
{
public:
  explicit DpPath(const std::vector<std::vector<SlPoint>> &sample_points,
                  const std::vector<Box2d> &obstacles);

  bool Search(std::vector<SlPoint> *path);

private:
  void Init(const std::vector<std::vector<SlPoint>> &sample_points);

  void CalculateCostTable();

  void CalculateCostAt(const int32_t l, const int32_t s);

  double CalculateAllObstacleCost(SlPoint &pre_point, SlPoint &cur_point);

  double CalculateObstacleCost(Box2d &obs, Box2d &veh);

  double CalculateReferenceLineCost(const SlPoint &pre_point, const SlPoint &cur_point) const;

private:
  std::vector<std::vector<Node>> cost_table_;
  std::vector<Box2d> obstacles_;
  const double vehicle_length_ = 2.0;
  const double vehicle_width_ = 1.0;
};

//
DpPath::DpPath(const std::vector<std::vector<SlPoint>> &sample_points,
               const std::vector<Box2d> &obstacles)
    : obstacles_(obstacles)
{
  // CHECK_GT(sample_points.size(), 1);
  // CHECK_EQ(sample_points.front().size(), 1);
  Init(sample_points);
}

// 动态规划的主函数
bool DpPath::Search(std::vector<SlPoint> *path)
{
  if (path == nullptr)
  {
    std::cout << "Need to initialize path" << std::endl;
    return false;
  }

  CalculateCostTable();

  for (int i = 0; i < cost_table_.size(); i++)
  {
    std::cout << "level  " << i << "  cost_table_.size() "
              << "   " << cost_table_[i].size() << std::endl;
  }

  auto &last_level = cost_table_.back();
  Node *min_cost_node = nullptr;
  double min_cost = std::numeric_limits<double>::max();

  // auto &p = cost_table_.front();
  for (auto &p : last_level)
  {
    if (p.cost < min_cost)
    {
      min_cost = p.cost;
      min_cost_node = &p; // 最后一个level中cost最小的node
    }
  }

  if (min_cost_node == nullptr || min_cost == std::numeric_limits<double>::max())
  {
    std::cout << "runing DP_path_planner "
              << "   " << __LINE__ << std::endl;
    if (min_cost_node == nullptr)
    {
      std::cout << "min_cost_node == nullptr" << std::endl;
    }
    return false;
  }

  std::cout << "" << std::endl;
  std::cout << "" << std::endl;
  // 最后一个level中cost最小的node,它的pre_node也是上一个level中cost最小的
  while (min_cost_node != nullptr)
  {
    std::cout << "final path ( " << min_cost_node->sl_point.s << " " << min_cost_node->sl_point.l << " )" << std::endl;
    path->emplace_back(min_cost_node->sl_point);
    min_cost_node = min_cost_node->pre_node;
  }
  std::reverse(path->begin(), path->end());

  // { // debug only
  //   std::cout << "the left path  " << std::endl;
  //   auto the_left = cost_table_.back()[0];
  //   for (int i = 0; i < cost_table_.size(); i++)
  //   {
  //     std::cout << "left path s  " << the_left.sl_point.s << "  l   " << the_left.sl_point.l << std::endl;
  //     if (the_left.pre_node != nullptr)
  //     {
  //       the_left = *(the_left.pre_node);
  //     }
  //   }
  // }
  return true;
}

// 初始化
void DpPath::Init(const std::vector<std::vector<SlPoint>> &sample_points)
{
  for (const auto &level : sample_points)
  {
    std::vector<Node> level_points;
    for (const auto &p : level)
    {
      level_points.emplace_back(p);
    }
    cost_table_.emplace_back(level_points);
  }
}

// 计算cost
void DpPath::CalculateCostTable()
{
  // std::cout<<"cost_table_.size()   "<<cost_table_.size()<<std::endl;
  // std::cout<<"cost_table_[0].size()   "<<cost_table_[1].size()<<std::endl;

  cost_table_[0][0].cost = 0.0;
  // 撒点
  // 对level撒点
  for (uint32_t s = 1; s < cost_table_.size(); ++s)
  { // 在每个level中,撒点
    for (uint32_t l = 0; l < cost_table_[s].size(); ++l)
    {
      CalculateCostAt(s, l);
      double cost_tmp = cost_table_[s][l].cost;
      std::cout << "  (" << cost_tmp << ")  ";
    }
    std::cout << "" << std::endl;
  }
}

// 每一个(s,l)轨迹点的cost
void DpPath::CalculateCostAt(const int32_t s, const int32_t l)
{
  // 上一个level的所有点  // // 按照s的方向撒点为level方向
  // auto &pre_level = cost_table_[s - 1];

  auto pre_level = cost_table_[s - 1].end();
  auto pre_point = cost_table_[s - 1].begin();

  double min_cost = std::numeric_limits<double>::max();

  // for (pre_point; pre_point<= pre_level;pre_point++)

  for (int i = 0; i < cost_table_[s - 1].size(); i++)
  {
    double cost = CalculateAllObstacleCost(cost_table_[s - 1][i].sl_point, cost_table_[s][l].sl_point) +
                  CalculateReferenceLineCost(cost_table_[s - 1][i].sl_point, cost_table_[s][l].sl_point);
    // double cost = CalculateAllObstacleCost(pre_point->sl_point, cost_table_[s][l].sl_point) +
    //               CalculateReferenceLineCost(pre_point->sl_point, cost_table_[s][l].sl_point);
    cost += cost_table_[s - 1][i].cost;
    if (cost < min_cost)
    {
      min_cost = cost;
      // 当前node的pre_node一定是上个level中cost最小的node
      cost_table_[s][l].pre_node = &cost_table_[s - 1][i];
      cost_table_[s][l].cost = min_cost;
    }
  }
}

double DpPath::CalculateAllObstacleCost(SlPoint &pre_point, SlPoint &cur_point)
{
  const double curve_length = cur_point.s - pre_point.s;
  QuinticPolynomialCurve1d curve(pre_point.l, 0.0, 0.0, cur_point.l, 0.0, 0.0, curve_length);
  double cost = 0.0;
  constexpr double kStep = 0.1;
  for (double s = 0.0; s < curve_length; s += kStep)
  {
    double vehicle_l = curve.Evaluate(0, s);
    double vehicle_s = pre_point.s + s;
    double vehicle_heading = std::atan(curve.Evaluate(1, s));
    Box2d veh({vehicle_s, vehicle_l}, vehicle_heading, vehicle_length_, vehicle_width_);
    for (auto &obs : obstacles_)
    {
      cost += CalculateObstacleCost(obs, veh);
    }
  }
  return cost;
}

double DpPath::CalculateObstacleCost(Box2d &obs, Box2d &veh)
{
  // 详细需要参考Apollo中Box2d的实现

  // 车辆的box和障碍物的box有重叠
  // if (obs.HasOverlap(veh))
  // {
  //   return std::numeric_limits<double>::max();
  // }

  double dis = obs.DistanceTo(veh);
  if (dis > 2 * vehicle_width_)
  {
    return 0.0;
  }
  return 1.0 / (dis + std::numeric_limits<double>::epsilon());
}

double DpPath::CalculateReferenceLineCost(const SlPoint &pre_point,
                                          const SlPoint &cur_point) const
{
  const double curve_length = cur_point.s - pre_point.s;
  QuinticPolynomialCurve1d curve(pre_point.l, 0.0, 0.0, cur_point.l, 0.0, 0.0, curve_length);
  double cost = 0.0;
  constexpr double kStep = 0.1;
  for (double s = 0.0; s < curve_length; s += kStep)
  {
    double l = curve.Evaluate(0, s);
    cost += std::fabs(l * l); // l方向的偏移距离作为 cost
  }
  return cost;
}

int main()
{

  std::cout << "runing DP_path_planner " << std::endl;

  std::shared_ptr<DpPath> dp_path_ = nullptr;
  std::vector<std::vector<SlPoint>> sample_points_;

  // 障碍物
  std::vector<Box2d> obstacles_;
  Box2d obs1({3, 0}, 0.0, 0.8, 1.5);
  Box2d obs2({11, 0}, 0.0, 0.8, 1.5);
  obstacles_.emplace_back(obs1);
  obstacles_.emplace_back(obs2);
  SlPoint vehicle_position(0.0, 0.0);

  sample_points_.emplace_back(std::vector<SlPoint>{vehicle_position});
  for (double s = 3; s < 20; s += 8)
  {
    std::vector<SlPoint> level_points;
    for (double l = -1; l < +2; l += 1)
    {
      level_points.emplace_back(s, l);
    }
    sample_points_.emplace_back(level_points);
  }

  // 撒的点
  for (int i = 0; i < sample_points_.size(); i++)
  {
    for (int j = 0; j < sample_points_[i].size(); j++)
    {
      std::cout << "  ( " << sample_points_[i][j].s << " " << sample_points_[i][j].l << " )  ";
    }

    std::cout << "" << std::endl;
  }

  dp_path_ = std::make_shared<DpPath>(sample_points_, obstacles_);
  std::cout << "runing DP_path_planner " << std::endl;
  std::vector<SlPoint> path;

  bool ret = dp_path_->Search(&path);
  std::cout << " DP can find a path?  " << ret << std::endl;

  std::cout << "End DP_path_planner " << std::endl;
  return 0;
}
