#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <limits>
AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  // From text book
  int obj_size = objects.size();
  if (obj_size == 0)
  {
    this->left = nullptr;
    this->right = nullptr;
  } 
  else if (obj_size == 1)
  {
    this->left = objects[0];
    this->right = nullptr;
    insert_box_into_box(objects[0]->box, this->box);
  }
  else if (obj_size == 2)
  {
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);
  }
  else
  {
    for (int i = 0; i < obj_size; i ++)
    {
      insert_box_into_box(objects[i]->box, this->box);
    }

    double longest_axis = - std::numeric_limits<double>::infinity();
    double centroid = 0;
    int longest_axis_idx = 0;
    for (int i = 0; i < 3; i ++)
    {
      double axis_len = this->box.max_corner[i] - this->box.min_corner[i];
      if (axis_len > longest_axis)
      {
        longest_axis = axis_len;
        longest_axis_idx = i;
      }
    }
    centroid = this->box.center()[longest_axis_idx];

    std::vector<std::shared_ptr<Object>> subtree_left;
    std::vector<std::shared_ptr<Object>> subtree_right;
    for (int i = 0; i < obj_size; i ++)
    {
      if (objects[i]->box.center()[longest_axis_idx] < centroid)
      {
        subtree_left.emplace_back(objects[i]);
      }
      else
      {
        subtree_right.emplace_back(objects[i]);
      }
    }

    // balance the tree
    int subtree_left_size = subtree_left.size();
    int subtree_right_size = subtree_right.size();
    if (subtree_left_size == 0)
    {
      int start = subtree_right.size() / 2;
      for (int i = start; i < subtree_right.size(); i ++)
      {
        subtree_left.emplace_back(subtree_right[i]);
      }
      subtree_right.erase(subtree_right.begin() + start, subtree_right.end());
    }
    else if (subtree_right_size == 0)
    {
      int start = subtree_left.size() / 2;
      for (int i = start; i < subtree_left.size(); i ++)
      {
        subtree_right.emplace_back(subtree_left[i]);
      }
      subtree_left.erase(subtree_left.begin() + start, subtree_left.end());
    }

    if (subtree_left.size() == 1)
    {
      this->left = subtree_left[0];
    }
    else if (subtree_left.size() > 1)
    {
      this->left = std::make_shared<AABBTree>(subtree_left, a_depth + 1);
    }
    if (subtree_right.size() == 1)
    {
      this->right = subtree_right[0];
    }
    else if (subtree_right.size() > 1)
    {
      this->right = std::make_shared<AABBTree>(subtree_right, a_depth + 1);
    }
  }
}
