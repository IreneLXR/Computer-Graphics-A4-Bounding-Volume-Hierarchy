#include "AABBTree.h"
// See AABBTree.h for API
#include "MeshTriangle.h"
#include "CloudPoint.h"
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool has_intersected = ray_intersect_box(ray, this->box, min_t, max_t);
  if (has_intersected)
  {
    bool i1 = false;
    bool i2 = false;
    double t1 = std::numeric_limits<double>::infinity();
    double t2 = std::numeric_limits<double>::infinity();
    std::shared_ptr<Object> descendant_left, descendant_right;
    
    if (this->left != nullptr && this->left->ray_intersect(ray, min_t, max_t, t1, descendant_left))
    {
      i1 = true;
    }
    
    if (this->right != nullptr && this->right->ray_intersect(ray, min_t, max_t, t2, descendant_right))
    {
      i2 = true;
    }
    
    // Pointers to left and right subtree branches. These could be another
    // AABBTree (internal node) or a leaf (primitive Object like MeshTriangle, or
    // CloudPoint)
    
    if (i1 == true && !descendant_left)
    {
      descendant_left = this->left;
    }
    if (i2 == true && !descendant_right)
    {
      descendant_right = this->right;
    }
    
    if (i1 && i2)
    {
      if (t1 < t2)
      {
        t = t1;
        descendant = descendant_left;
      }
      else
      {
        t = t2;
        descendant = descendant_right;
      }
      return true;
    }
    else if (i1)
    {
      t = t1;
      descendant = descendant_left;
      return true;
    }
    else if (i2)
    {
      t = t2;
      descendant = descendant_right;
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}


