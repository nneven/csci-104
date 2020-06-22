#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename KComparator = std::equal_to<T>,
         typename PComparator = std::less<T>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const KComparator& kcomp = KComparator()  );

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

    /// decreaseKey - Finds key matching old object &
    /// updates its location in the heap based on the new value
    void decreaseKey(const T& old, const T& newVal);

 private:
    /// Add whatever helper functions and data members you need below
    void trickleUp(int loc);
    void heapify(int loc, int effsize);
    void print();


 private:
   /// Data members - These should be sufficient
    std::vector< T > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, KComparator> keyToLocation_;

};

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const KComparator& kcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, kcomp)

{

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::~Heap()
{
    
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::push( const T& item)
{
	int loc = store_.size();
	keyToLocation_.insert(std::make_pair(item, loc));
	store_.push_back(item);
  	trickleUp(store_.size() - 1);
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::decreaseKey(const T& old, const T& newVal)
{
	if (c_(old, newVal)) return;
	if (keyToLocation_.find(old) == keyToLocation_.end()) return;
	int location = keyToLocation_[old];
        // std::cout << location << " " << newVal << std::endl;
	keyToLocation_.erase(old);
	keyToLocation_.insert(std::make_pair(newVal, location));
	store_[location] = newVal;
	trickleUp(location);

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
T const & Heap<T,KComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return store_[0];
}

// Incomplete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }
    store_[0] = store_.back();
  	store_.pop_back();
  	heapify(0, store_.size());
}

/// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
bool Heap<T,KComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::heapify(int loc, int effsize)
{
	int largest = loc;

	for (int i = 1; i <= m_; i++)
	{
		int child = m_ * loc + i;
		if (child <= effsize && c_(store_[child], store_[largest])) largest = child;
	}

	if (largest != loc)
	{
		int index = keyToLocation_[store_[loc]];
		keyToLocation_[store_[loc]] = keyToLocation_[store_[largest]];
		keyToLocation_[store_[largest]] = index;
		std::swap(store_[loc], store_[largest]);
		heapify(largest, effsize);
	}
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleUp(int loc)
{
	int parent = (loc - 1) / m_;
	while (parent >= 0 && c_(store_[loc], store_[parent]))
	{
		int index = keyToLocation_[store_[loc]];
		keyToLocation_[store_[loc]] = keyToLocation_[store_[parent]];
		keyToLocation_[store_[parent]] = index;
		std::swap(store_[loc], store_[parent]);
		loc = parent;
		parent = (loc - 1) / m_;
	}
}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::print()
{
	for (int i = 0; i < store_.size(); i++)
	{
		// std::cout << store_[i] << "-" << i << std::endl;
	}
	// std::cout << std::endl;
}

#endif
