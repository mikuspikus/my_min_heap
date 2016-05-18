#pragma once

#include <math.h>

namespace my_vector {
	double log2_(double _value)
	{
		return log(_value) / log(2.0);
	}

	template <class T>
	class vector
	{
	private:
		T* ptr_;
		int size_;
		int capacity_;
		int base_;
	public:
		/*===================================
		CONSTRUCTORS'N'DESTRUCTOS
		===================================*/
		vector();
		vector(const vector&);
		vector(int, int);
		vector(T, int, int);
		~vector();

		/*===================================
		GETTERS
		===================================*/
		int get_size();
		int get_base();

		/*===================================
		PUBLIC METHODS
		===================================*/
		void resize(int);
		void push(T);
		T pop();

		/*===================================
		OPERATORS
		===================================*/
		T& operator[](int) const;
		vector<T> operator+(const vector&);
		vector<T>& operator+=(const vector&);
		vector<T> operator-(const vector&);
		vector<T>& operator-=(const vector&);
		vector<T>& operator=(const vector&);
	};

	template <typename T>
	vector<T>::vector()
	{
		size_ = 0;
		capacity_ = 0;
		base_ = 0;
		ptr_ = new T[capacity_];
	}

	template <typename T>
	vector<T>::vector(const vector& _v)
	{
		size_ = _v.size_;
		capacity_ = _v.capacity_;
		base_ = _v.base_;
		ptr_ = new T[capacity_];

		for (auto i = 0; i < size_; i++)
			ptr_[i] = _v.ptr_[i];
	}

	template <typename T>
	vector<T>::vector(int _size, int _base)
	{
		size_ = _size;
		base_ = _base;
		capacity_ = 1 << int(ceil(log2_(_size)));
		ptr_ = new T[capacity_];
	}

	template <typename T>
	vector<T>::vector(T _filler, int _size, int _base)
	{
		size_ = _size;
		base_ = _base;
		capacity_ = 1 << int(ceil(log2_(_size)));
		ptr_ = new T[capacity_];

		for (auto i = 0; i > size_; i++)
			ptr_[i] = _filler;
	}

	template <typename T>
	vector<T>::~vector()
	{
		delete[] ptr_;
	}

	template <typename T>
	int vector<T>::get_base()
	{
		return base_;
	}

	template <typename T>
	int vector<T>::get_size()
	{
		return size_;
	}

	template <typename T>
	void vector<T>::resize(int new_size)
	{
		if (new_size < 0)
			throw("New size is less than 0, can't resize.");

		if (1 << int(ceil(log2_(new_size))) != capacity_) {
			capacity_ = 1 << int(ceil(log2_(new_size)));
			T* buffer = new T[capacity_];

			if (new_size > capacity_)
				for (int i = 0; i < size_; ++i)
					buffer[i] = ptr_[i];
			else
				for (int i = 0; i < new_size; ++i)
					buffer[i] = ptr_[i];

			delete[] ptr_;
			ptr_ = buffer;
		}

		size_ = new_size;
	}

	template <typename T>
	void vector<T>::push(T _item)
	{
		resize(size_ + 1);
		ptr_[size_ - 1] = _item;
	}

	template <typename T>
	T vector<T>::pop()
	{
		if (size_ == 0)
			throw("Nothig to pop.");

		T item = ptr_[size_ - 1];
		resize(size_ - 1);

		return item;
	}

	template <typename T>
	T& vector<T>::operator[](int index) const
	{
		if (index < base_ || index - base_ >= size_)
			throw("Index doesn't exist.");
		else {
			return ptr_[index];
		}
	}

	template <typename T>
	vector<T> vector<T>::operator+(const vector& _v)
	{
		if (size_ != _v.size_)
			resize(_v.size_);

		vector<T> result = *this;
		result += _v;
		return result;
	}

	template <typename T>
	vector<T>& vector<T>::operator+=(const vector& _v)
	{
		if (size_ != _v.size_)
			resize(_v.size_);
		for (auto i = 0; i < size_; i++)
			ptr_[i] += _v.ptr_[i];
		return *this;
	}

	template <typename T>
	vector<T> vector<T>::operator-(const vector& _v)
	{
		if (size_ != _v.size_)
			resize(_v.size_);

		vector<T> result = *this;
		result -= _v;
		return result;
	}

	template <typename T>
	vector<T>& vector<T>::operator-=(const vector& _v)
	{
		if (size_ != _v.size_)
			resize(_v.size_);
		for (auto i = 0; i < size_; i++)
			ptr_[i] -= _v.ptr_[i];
		return *this;
	}

	template <typename T>
	vector<T>& vector<T>::operator=(const vector& _v)
	{
		size_ = _v.size_;
		capacity_ = _v.capacity_;
		base_ = _v.base_;

		delete[] ptr_;
		ptr_ = new T[capacity_];

		for (auto i = 0; i < size_; i++)
			ptr_[i] = _v.ptr_[i];

		return *this;
	}
}
