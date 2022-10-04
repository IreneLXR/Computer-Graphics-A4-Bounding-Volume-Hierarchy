#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  I = -1;
  sqrD = 0;
  double criterion = std::numeric_limits<double>::infinity();
  for (int i = 0; i < points.rows(); i ++)
  {
    Eigen::RowVector3d pt = points.row(i);
    double distance = (query - pt).squaredNorm();
    if (distance < criterion)
    {
      I = i;
      criterion = distance;
    }
  }
  if (I != -1)
  {
    sqrD = criterion;
  }
  ////////////////////////////////////////////////////////////////////////////
}
