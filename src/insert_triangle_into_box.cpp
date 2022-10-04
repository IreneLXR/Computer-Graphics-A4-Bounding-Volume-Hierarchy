#include "insert_triangle_into_box.h"

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  for (int i = 0; i < 3; i ++)
  {
    double min_tri = std::min(std::min(a[i], b[i]), c[i]);
    double max_tri = std::max(std::max(a[i], b[i]), c[i]);
    B.min_corner[i] = std::min(min_tri, B.min_corner[i]);
    B.max_corner[i] = std::max(max_tri, B.max_corner[i]);
  }
}



