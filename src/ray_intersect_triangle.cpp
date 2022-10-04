#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>
bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // modify from A2 code
  //t = 0;
  
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d d = ray.direction;
  //double t_tmp;
  Eigen::Vector3d c1 = (B - A).transpose();
  Eigen::Vector3d c2 = (C - A).transpose();
  Eigen::Vector3d res = e - A.transpose();
  Eigen::Matrix3d mtx;
  mtx.col(0) = c2;
  mtx.col(1) = c1;
  mtx.col(2) = - d;
  // Solve for B of AB = C
  Eigen::Vector3d solution = mtx.householderQr().solve(res);
  if (solution[2] < min_t || solution[2] > max_t)
  {
    return false;
  }
  // if statement from lec notes
  if (solution[0] >= 0 && solution[1] >= 0 && (solution[0] + solution[1] <= 1))
  {
    t = solution[2];
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

