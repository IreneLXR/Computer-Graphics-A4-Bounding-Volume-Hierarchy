#include "point_box_squared_distance.h"
#include <algorithm>
#include <math.h>
double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  
  double res = 0;
  for (int i = 0; i < 3; i ++)
  {
    double tmp = std::max(std::max(box.min_corner[i] - query[i], 0.0), query[i] - box.max_corner[i]);
    res = res + pow(tmp, 2);
  }


  return res;
  ////////////////////////////////////////////////////////////////////////////
}