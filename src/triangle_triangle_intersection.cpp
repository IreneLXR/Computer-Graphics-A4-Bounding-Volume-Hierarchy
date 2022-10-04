#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // from stackoverflow: Find whether two triangles intersect or not
  // In mathematical way:
  // check: https://math.stackexchange.com/questions/1231340/find-where-2-triangles-intersect-in-3d
  //  in programming: for two triangles intersect or not, 
  // we can actually view each edge of triangle as a ray and see if this ray intersect another triangle or not
  Eigen::RowVector3d e, d;
  // first check for triangle A
  d = B1 - B0;
  e = B0;
  // Intersect a ray with a triangle
  double t;
  double min_t = 0.0;
  double max_t = 1.0;
  if (ray_intersect_triangle(Ray(e, d), A0, A1, A2, min_t, max_t, t))
  {
    return true;
  }
  d = B2 - B1;
  e = B1;
  if (ray_intersect_triangle(Ray(e, d), A0, A1, A2, min_t, max_t, t))
  {
    return true;
  }
  d = B0 - B2;
  e = B2;
  if (ray_intersect_triangle(Ray(e, d), A0, A1, A2, min_t, max_t, t))
  {
    return true;
  }

  // then check for triangle B
  d = A1 - A0;
  e = A0;
  if (ray_intersect_triangle(Ray(e, d), B0, B1, B2, min_t, max_t, t))
  {
    return true;
  }
  d = A2 - A1;
  e = A1;
  if (ray_intersect_triangle(Ray(e, d), B0, B1, B2, min_t, max_t, t))
  {
    return true;
  }
  d = A0 - A2;
  e = A2;
  if (ray_intersect_triangle(Ray(e, d), B0, B1, B2, min_t, max_t, t))
  {
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
