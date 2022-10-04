#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <MeshTriangle.h>
#include <CloudPoint.h>
#include <limits>
bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  sqrd = 0;
  // Object is base for AABBTree 
  std::priority_queue<std::pair<double, std::shared_ptr<Object>>, 
                      std::vector<std::pair<double, std::shared_ptr<Object>>>,
                      std::greater<std::pair<double, std::shared_ptr<Object>>>> pq;
  double dis_1 = point_box_squared_distance(query, root->box);
  std::pair<double, std::shared_ptr<Object>> pair_1(dis_1, root);
  pq.push(pair_1);         
  double criterion_min = std::numeric_limits<double>::infinity();
  while(!pq.empty())
  {
    std::pair<double, std::shared_ptr<Object>> tmp_pair = pq.top();
    pq.pop();
    double tmp_dis = tmp_pair.first;
    std::shared_ptr<Object> tmp_obj = tmp_pair.second;
    if (tmp_dis < criterion_min)
    {
      // check for leaves
      // Pointers to left and right subtree branches. These could be another
      // AABBTree (internal node) or a leaf (primitive Object like MeshTriangle, or
      // CloudPoint)
      // check if not AABBTree then it is leaf
      std::shared_ptr<AABBTree> t = std::dynamic_pointer_cast<AABBTree>(tmp_obj);
      if (t == nullptr)
      {
        double tmp_leaf;
        std::shared_ptr<Object> leaf_obj;
        if (tmp_obj && tmp_obj->point_squared_distance(query, min_sqrd, max_sqrd, tmp_leaf, leaf_obj))
        {
          if (tmp_leaf < criterion_min)
          {
            criterion_min = tmp_leaf;
            descendant = tmp_obj;
          }
        }
      }
      else // not leaves
      {
        if (t->left)
        {
          double tmp_left = point_box_squared_distance(query, t->left->box);
          std::pair<double, std::shared_ptr<Object>> pair_left(tmp_left, t->left);
          pq.push(pair_left);
        }
        if (t->right)
        {
          double tmp_right = point_box_squared_distance(query, t->right->box);
          std::pair<double, std::shared_ptr<Object>> pair_right(tmp_right, t->right);
          pq.push(pair_right);
        }

      }
    }

  }
  sqrd = criterion_min;
  if (criterion_min != std::numeric_limits<double>::infinity())
  {
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
