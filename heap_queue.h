#pragma once

#include "vector_for_heap.h"
#include <algorithm>

namespace my_min_heap {
	template <typename T>
	void swap(T& lhs, T& rhs)
	{
		T tmp = lhs;
		lhs = rhs;
		rhs = tmp;
	}

	template <class T>
	class heap_queue
	{
	public:
		/*================================================
			HEAP NODE
		================================================*/
		struct heap_node {
			int key;
			T data;

			bool operator>(const heap_node& _node) const {
				return key > _node.key;
			}

			bool operator<(const heap_node& _node) const {
				return key < _node.key;
			}
		};

		/*================================================
		
		================================================*/
		heap_queue();
		~heap_queue() {};

		/*================================================
			GETTERS
		================================================*/
		bool isEmpty() const;
		int getSize() const;

		/*================================================
		
		================================================*/
		int parent(unsigned int idx) const;
		int child(unsigned int idx) const;
		int find(unsigned int idx, T item_to_find) const;

		/*================================================
			
		================================================*/
		void insert(int new_key, T new_item);
		void remove(T item_to_remove);
		T extractMin();
	private:
		my_vector::vector<heap_node> queue_;
		unsigned int size_;

		/*
		Called by insert()
		If the parent's value is greater than current
		the current item bubbles up till it reach root
		*/
		void bubbleUp(int idx);

		/*
		Called by delete()
		If the current is greater than children
		the current item bubbles down till no more children
		*/
		void bubbleDown(int idx);

		/*
		Used by bubbleDown()
		Get the index of the main value
		between 3 given indices to the heap array
		*/
		int getMinIdx(int aIdx, int bIdx, int cIdx);
	};

	template <typename T>
	heap_queue<T>::heap_queue() {
		size_ = 0;
	}

	template <typename T>
	bool heap_queue<T>::isEmpty() const {
		return (size_ == 0);
	}

	template <typename T>
	int heap_queue<T>::getSize() const {
		return size_;
	}

	template <typename T>
	int heap_queue<T>::parent(unsigned int idx) const {
		if (idx < 1) return -1; //empty or root has no parent
		return ((int)idx / 2); //floor(idx / 2)
	}

	template <typename T>
	int heap_queue<T>::child(unsigned int idx) const {
		if (/*size_ <= -1 ||*/ 2 * idx >= size_) return -1; //empty or root has no child ?
		return (2 * idx);
	}

	template <typename T>
	int heap_queue<T>::find(unsigned int idx, T item_to_find) const { //O(log n)
		if (idx > size_) return -1; //base case: idx out of bounds
		if (item_to_find < queue_[idx].data) return -1; //base case: item_to_find not in min-heap
		if (queue_[idx].data == item_to_find) return idx; //found the item_to_find, return the index

		int childIdx = child(idx), i = -1;

		if (childIdx != -1) { //find in left and right children
			i = std::max(find(childIdx, item_to_find), find(childIdx + 1, item_to_find));
			//i = find(childIdx, item_to_find) > find(childIdx + 1, item_to_find) ? find(childIdx, item_to_find) : find(childIdx + 1, item_to_find);
		}

		return i;
	}

	template <typename T>
	void heap_queue<T>::insert(int new_key, T new_item) {
		queue_.push(heap_node{ new_key,new_item });
		size_++;
		bubbleUp(size_ - 1);
	}

	template <typename T>
	void heap_queue<T>::bubbleUp(int idx) {
		int parentIdx = parent(idx);
		if (parentIdx == -1) return; //base case: root of the heap

		if (queue_[parentIdx] > queue_[idx]) {
			swap(queue_[parentIdx], queue_[idx]);
			bubbleUp(parentIdx);
		}
	}

	template <typename T>
	void heap_queue<T>::bubbleDown(int idx) {
		int childIdx = child(idx);
		if (childIdx == -1) return;//base case: no children left
		int minIdx = getMinIdx(idx, childIdx, childIdx + 1);

		if (minIdx != idx) {
			swap(queue_[minIdx], queue_[idx]);
			bubbleDown(minIdx);
		}
	}

	template <typename T>
	void heap_queue<T>::remove(T item_to_delete) { //O(2 * log n)
		int idx = find(0, item_to_delete);
		if (idx == -1) return;

		swap(queue_[idx], queue_[size_ - 1]); //swap current with last item
		size_--;
		queue_.resize(size_); //idx 0 is a dud item
		bubbleDown(idx);
		bubbleUp(idx);
	}

	template <typename T>
	T heap_queue<T>::extractMin() {
		if (isEmpty()) throw("Heap underflow.");

		T min = queue_[0].data;
		remove(min);

		return min;
	}

	template <typename T>
	int heap_queue<T>::getMinIdx(int aIdx, int bIdx, int cIdx) {
		bool is_left_smaller = (queue_[aIdx] < queue_[bIdx]);

		if (cIdx >= (int)size_) { //the last right child doesn't exist
			return is_left_smaller ? aIdx : bIdx;
		}
		else if (is_left_smaller) {
			return (queue_[aIdx] < queue_[cIdx]) ? aIdx : cIdx;
		}
		else {
			return (queue_[bIdx] < queue_[cIdx]) ? bIdx : cIdx;
		}
	}
}
