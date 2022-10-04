#include "ray_intersect_box.h"
#include <iostream>
#include <algorithm>
bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // based on the formula from slides
  
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  double x_min = box.min_corner[0];
  double x_max = box.max_corner[0];
  double y_min = box.min_corner[1];
  double y_max = box.max_corner[1];
  double z_min = box.min_corner[2];
  double z_max = box.max_corner[2];
  // handle the zero on denominator
  double a_xd = 1.0 / d[0];
  double a_yd = 1.0 / d[1];
  double a_zd = 1.0 / d[2];
  double xe = e[0];
  double ye = e[1];
  double ze = e[2];
  double t_x_min, t_x_max, t_y_min, t_y_max, t_z_min, t_z_max;
  if (a_xd >= 0)
  {
    t_x_min = (x_min - xe) * a_xd;
    t_x_max = (x_max - xe) * a_xd;
  }
  else
  {
    t_x_min = (x_max - xe) * a_xd;
    t_x_max = (x_min - xe) * a_xd;
  }
  if (a_yd >= 0)
  {
    t_y_min = (y_min - ye) * a_yd;
    t_y_max = (y_max - ye) * a_yd;
  }
  else
  {
    t_y_min = (y_max - ye) * a_yd;
    t_y_max = (y_min - ye) * a_yd;
  }
  if (a_zd >= 0)
  {
    t_z_min = (z_min - ze) * a_zd;
    t_z_max = (z_max - ze) * a_zd;
  }
  else
  {
    t_z_min = (z_max - ze) * a_zd;
    t_z_max = (z_min - ze) * a_zd;
  }
  double lower_bd = std::max(std::max(t_x_min, t_y_min), t_z_min);
  double upper_bd = std::min(std::min(t_x_max, t_y_max), t_z_max);
  if (lower_bd > upper_bd)
  {
    return false;
  }
  double min_bd = std::max(lower_bd, min_t);
  double max_bd = std::min(upper_bd, max_t);
  if (min_bd > max_bd)
  {
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}
