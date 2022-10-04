#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>
bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  hit_t = 0;
  hit_f = 0;
  
  double t_tmp = std::numeric_limits<double>::infinity();
  bool has_intersected = false;
  for (int i = 0; i < F.rows(); i ++)
  {
    Eigen::RowVector3d A = V.row(F(i, 0));
    Eigen::RowVector3d B = V.row(F(i, 1));
    Eigen::RowVector3d C = V.row(F(i, 2));
    double t_tmp_prime;
    if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, t_tmp_prime))
    {
      if (t_tmp_prime < t_tmp)
      {
        t_tmp = t_tmp_prime;
        has_intersected = true;
        hit_f = i;
      }
    }
  }
  if (has_intersected)
  {
    hit_t = t_tmp;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
