#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 
#include <iostream>

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  
  std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object>>> qlist;
  if (box_box_intersect(rootA->box, rootB->box))
  {
    qlist.emplace_back(rootA, rootB);
  }
  while (!qlist.empty())
  {
    std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> tmp_pair = qlist.front();
    qlist.pop_front();
    std::shared_ptr<AABBTree> tmp1 = std::dynamic_pointer_cast<AABBTree>(tmp_pair.first);
    std::shared_ptr<AABBTree> tmp2 = std::dynamic_pointer_cast<AABBTree>(tmp_pair.second);
    // AABB subtree
    if (tmp1 == nullptr && tmp2 == nullptr)
    {
      leaf_pairs.emplace_back(tmp_pair.first, tmp_pair.second);
    }
    else if (tmp1 == nullptr)
    {
      if (tmp2->left && box_box_intersect(tmp_pair.first->box, tmp2->left->box))
      {
        qlist.emplace_back(tmp_pair.first, tmp2->left);
      }
      if (tmp2->right && box_box_intersect(tmp_pair.first->box, tmp2->right->box))
      {
        qlist.emplace_back(tmp_pair.first, tmp2->right);
      }
    }
    else if (tmp2 == nullptr)
    {
      if (tmp1->left && box_box_intersect(tmp1->left->box, tmp_pair.second->box))
      {
        qlist.emplace_back(tmp1->left, tmp_pair.second);
      }
      if (tmp1->right && box_box_intersect(tmp1->right->box, tmp_pair.second->box))
      {
        qlist.emplace_back(tmp1->right, tmp_pair.second);
      }
    }
    else
    {
      if (tmp1->left && tmp2->left && box_box_intersect(tmp1->left->box, tmp2->left->box))
      {
        qlist.emplace_back(tmp1->left, tmp2->left);
      }
      if (tmp1->left && tmp2->right && box_box_intersect(tmp1->left->box, tmp2->right->box))
      {
        qlist.emplace_back(tmp1->left, tmp2->right);
      }
      if (tmp1->right && tmp2->right && box_box_intersect(tmp1->right->box, tmp2->right->box))
      {
        qlist.emplace_back(tmp1->right, tmp2->right);
      }
      if (tmp1->right && tmp2->left && box_box_intersect(tmp1->right->box, tmp2->left->box))
      {
        qlist.emplace_back(tmp1->right, tmp2->left);
      }
    }
  }
}