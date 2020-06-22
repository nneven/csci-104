#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename Comparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator comp = Comparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below

  int m_;
  Comparator comp;
  std::vector<T> items;
  void trickleUp(int loc, Comparator& comp);
  void heapify(int loc, int effsize, Comparator& comp);


};

// Add implementation of member functions here

template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator comp)
{
  m_ = m;
  this->comp = comp;
}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap()
{

}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item)
{
  items.push_back(item);
  trickleUp(items.size() - 1, comp);
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return items[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  items[0] = items.back();
  items.pop_back();
  heapify(0, items.size(), comp);
}

template <typename T, typename Comparator>
bool Heap<T, Comparator>::empty() const
{
  return items.size() == 0;
}

template <typename T, typename Comparator >
void Heap<T, Comparator>::heapify(int loc, int effsize, Comparator& comp)
{
  int largest = loc;

  for (int i = 1; i <= m_; i++)
  {
    int child = m_ * loc + i;
    if (child <= effsize && comp(items[child], items[largest])) largest = child;
  }

  if (largest != loc)
  {
    std::swap(items[loc], items[largest]);
    heapify(largest, effsize, comp);
  }
}

template <typename T, typename Comparator >
void Heap<T, Comparator>::trickleUp(int loc, Comparator& comp)
{
  int parent = (loc - 1) / m_;
  while (parent >= 0 && comp(items[loc], items[parent]))
  {
    std::swap(items[loc], items[parent]);
    loc = parent;
    parent = (loc - 1) / m_;
  }
}

#endif