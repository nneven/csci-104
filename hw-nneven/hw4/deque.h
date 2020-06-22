#ifndef DEQUE_H
#define DEQUE_H
#include <stdexcept>

/**
 * Implements a templated, array-based, 
 * double-ended queue.
 *
 * The Deque should allow for amortized O(1) 
 * insertion and removal from either end. 
 * It should dynamically resize, when it becomes
 * full, but never needs to shrink.  
 *
 * It should use a circular buffer approach
 * by tracking the "front" and "back" location.
 *
 */


template <typename T>
class Deque
{
 public:
  /* START - DO NOT CHANGE ANY OF THESE LINES */
  /**
   *  Default constructor 
   *   Create an array of size 1 by default
   */
  Deque();

  /**
   *  Default constructor 
   *   Create an array of the given capacity.
   */
  Deque(size_t capacity);

  /**
   *  Destructor
   */
  ~Deque();

  /**
   *  Returns the number of elements in the Deque. 
   *   - Must run in O(1)
   */
  size_t size() const;

  /**
   *  returns true if the deque is empty
   *   - Must run in O(1)
   */
  bool empty() const;

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T& operator[](size_t i);

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T const & operator[](size_t i) const;

  /**
   *  Inserts a new item at the back of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_back(const T& item);

  /**
   *  Inserts a new item at the front of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_front(const T& item);

  /**
   *  Removes the back item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_back();

  /**
   *  Removes the front item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_front();
  /* END - DO NOT CHANGE ANY OF THESE LINES */

 private:
  /* Add data members and private helper 
   * functions below 
   */

  T* array;
  int front;
  int back;
  size_t size_;
  size_t max;
  
};

/* Implement each Deque<T> member function below 
 * taking care to meet the runtime requirements
 */

template <typename T>
Deque<T>::Deque()
{
  size_ = 0;
  max = 1;
  array = new T[max];
  front = 0;
  back = front + size_;
}

template <typename T>
Deque<T>::Deque(size_t capacity)
{
  size_ = 0;
  max = capacity;
  array = new T[max];
  front = 0;
  back = front + size_;
}

template <typename T>
Deque<T>::~Deque()
{
  delete[] array;
}

template <typename T>
size_t Deque<T>::size() const
{
  return size_;
}

template <typename T>
bool Deque<T>::empty() const
{
  return size_ == 0;
}

template <typename T>
T& Deque<T>::operator[](size_t i)
{
  if (i < 0 || i > size_) throw std::range_error("Invalid index location");
  return array[(front + i) % max];
}

template <typename T>
T const & Deque<T>::operator[](size_t i) const
{
  if (empty()) throw std::range_error("Deque Empty");
  if (i < 0 || i > size_) throw std::range_error("Invalid index location");
  return array[(front + i) % max];
}

template <typename T>
void Deque<T>::push_back(const T& item)
{
  if (size_ == max) {
    max = max * 2;
    T* temp = new T[max];
    for (int i = 0; i < (int)max / 2; i++) {
      temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    front = 0;
    back = front + size_;
  }
  size_++;
  array[back] = item;
  back = (back + 1) % max;
}

template <typename T>
void Deque<T>::push_front(const T& item)
{
  if (size_ == max) {
    max = max * 2;
    T* temp = new T[max];
    for (int i = 0; i < (int)max / 2; i++) {
      temp[i] = array[i];
    }
    delete[] array;
    array = temp;
    front = 0;
    back = front + size_;
  }
  if (front == 0) {
    front = max - 1;
  } else {
    front--;
  }

  size_++;
  array[front] = item;
}

template <typename T>
void Deque<T>::pop_back()
{
  if (empty()) return;
  else {
    size_--;
    if (back == 0) {
      back = max - 1;
    } else {
      back--;
    }
  }
}

template <typename T>
void Deque<T>::pop_front()
{
  if (empty()) return;
  else {
    size_--;
    front = (front + 1) % max;
  }
}

#endif