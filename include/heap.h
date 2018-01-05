/*
 * heap.h
 * Heap implementation in a template
 * Author: Huili Yu
 */

#ifndef INCLUDES_HEAP_H_
#define INCLUDES_HEAP_H_

#include <vector>

namespace dijkstra
{
template <typename var1, typename var2>
struct Dataum
{
  var1 idx;
  var2 key;
  Dataum(){};
  Dataum(var1 idx1, var2 key1) : idx(idx1), key(key1) {};
};

// Define heap class
template <class T1, class T2>
class Heap
{
 public:
  Heap(int n) : capacity_(n), num_of_items_(0), data_(n) {};
  ~Heap() {};
  void BubbleDown(int root, int bottom);
  void BubbleUp(int root, int bottom);
  bool Insert(Dataum<T1, T2> &dataum);
  Dataum<T1, T2> ExtractMin();
  bool Modify(Dataum<T1, T2> &dataum);
  int GetNumOfItems();
 private:
  int num_of_items_;
  int capacity_;
  std::vector<Dataum<T1, T2> > data_;
};

template <class T1, class T2>
void Heap<T1, T2>::BubbleUp(int root, int bottom)
{
  if (root < bottom)
  {
    int parent;
    parent = (bottom - 1) / 2;

    if (data_[parent].key > data_[bottom].key)// if smaller, stop
    {
      Dataum<T1, T2> temp;

      temp = data_[parent];
      data_[parent] = data_[bottom];
      data_[bottom] = temp;

      BubbleUp(root, parent);
    }
  }
}

template <class T1, class T2>
void Heap<T1, T2>::BubbleDown(int root, int bottom)
{
  int left_child;
  int right_child;
  left_child = 2 * root + 1;
  right_child = 2 * root + 2;

  // recursion
  if (left_child <= bottom)        // at least has one child
  {
    int minChild;
    if (left_child == bottom)   // if the root has no right child
    {
      minChild = left_child;
    }
    else                        // the root has both left and right child
    {
      if (data_[left_child].key <= data_[right_child].key)
        minChild = left_child;
      else
        minChild = right_child;
    }
    if (data_[root].key > data_[minChild].key)   // swap with the smaller child
    {
      Dataum<T1, T2> temp;
      temp = data_[root];
      data_[root] = data_[minChild];
      data_[minChild] = temp;

      // recursion
      BubbleDown(minChild, bottom);
    }
  }
}

template <class T1, class T2>
bool Heap<T1, T2>::Insert(Dataum<T1, T2> &dataum)
{
  if (num_of_items_ <= capacity_)
  {
    // insert key to last element of heap
    data_[num_of_items_] = dataum;
    BubbleUp(0, num_of_items_);
    ++num_of_items_;
    return true;
  }
	else {
	  return false;
	}
}

template <class T1, class T2>
Dataum<T1, T2> Heap<T1, T2>::ExtractMin()
{
  if (num_of_items_ < 1) {
    Dataum<T1, T2> out;
    out.idx = (T1)(-1);
    out.key = (T2)(-1);
  }
  Dataum<T1, T2> min_val = data_[0];

  //move last element to the root
  data_[0] = data_[num_of_items_ - 1];
  --num_of_items_;
  BubbleDown(0, num_of_items_ - 1);
  return min_val;
}

template <class T1, class T2>
int Heap<T1, T2>::GetNumOfItems()
{
  return num_of_items_;
}

template <class T1, class T2>
bool Heap<T1, T2>::Modify(Dataum<T1, T2> &dataum)
{
  for (int i = 0; i < num_of_items_; i++) {
    if (data_[i].idx == dataum.idx) {
      if (data_[i].key <= dataum.key) {
        // bubble down
        data_[i].key = dataum.key;
        BubbleDown(i, num_of_items_-1);
      }
      else {
        // bubble up
        data_[i].key = dataum.key;
        BubbleUp(0, i);
      }
      return true;
    }
  }
  return false;
}
}  // namespace dijkstra

#endif /* INCLUDES_HEAP_H_ */
