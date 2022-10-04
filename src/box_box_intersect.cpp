#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
  bool intersected = true;
  for (int i = 0; i < 3; i ++)
  {
    intersected = intersected && ((A.min_corner[i] <= B.max_corner[i]) && (A.max_corner[i] >= B.min_corner[i]));
  }
  if (intersected)
  {
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

