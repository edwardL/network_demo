#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <cstring>

#include "Iterator.h"

namespace TinySTL {
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first , ForwardIterator last , const T& value)
	{
		for(; first != last; ++last)
			*first = value;
	}
	inline void fill(char *first , char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value),last - first);
	}
	inline void fill(wchar_t *first , wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value),(last - first) * sizeof(wchar_t));
	}

	template<class OutputIterator, class Size , class T>
	OutputIterator fill_n(OutputIterator first , Size n, const T& value)
	{
		for(; n > 0; --n; ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char* fill_n(char* first , Size n , const char& value)
	{
		memset(first,static_cast<unsigned char>(value),n);
		return first + n;
	}
	template<class Size>
	wchar_t* fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first,static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	//*------------------------ min
	template<class T>
	const T& min(const T& a, const T& b)
	{
		return !(b < a) ? a : b;
	}
	template<class T, class Compare>
	const T& min(const T& a, const T& b, Compare comp) {
		return !comp(b,a) ? a : b;
	}

	//*********** [max] ********************
	//********* [Algorithm Complexity: O(1)] ****************
	template <class T> 
	const T& max(const T& a, const T& b){
		return (a < b) ? b : a;
	}
	template <class T, class Compare>
	const T& max(const T& a, const T& b, Compare comp){
		return (comp(a, b)) ? b : a;
	}

	//************************* [make_heap] ********************
	template<class RandomAccessIterator, class Compare>
	// heap …œÀ›À„∑®
	static void up(RandomAccessIterator first , RandomAccessIterator last,
		RandomAccessIterator head , Compare comp) {
			/// head points to heap's head

	}
}


#endif