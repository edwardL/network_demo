#ifndef _VECTOR_IMPL_H
#define _VECTOR_IMPL_H

namespace TinySTL{
	//***********************���죬���ƣ��������***********************
	template<class T, class Alloc>
	vector<T,Alloc>::~vector() {
		destroyAndDeallocateAll();
	}
	template<class T, class Alloc>
	vector<T,Alloc>::vector(const size_type n){
		allocateAndFillN(n , value_type());
	}
	template<class T, class Alloc>
	vector<T,Alloc>::vector(const size_type n, const value_type& value) {
		allocateAndFillN(n,value);
	}
	template<class T, class Alloc>
	template<class InputIterator>
	vector<T,Alloc>::vector(InputIterator first , InputIterator) {
		// ����ָ������ּ������ĺ���
		vector_aux(first,last, typename std::is_integral<InputIterator>::type());
	}

	template<class T, class Alloc>
	vector<T,Alloc>::vector(const vector& v) {
		allocateAndCopy(v.start_, v.finish_);
	}
	template<class T, class Alloc>
	template<T,Alloc>::vector(vector&& v){
		start_ = v.start_;
		finish_ = v.finish_;
		endOfStorage_ = v.endOfStorage_;
		v.start_ = v.finish_ = v.endOfStorage_ = 0;
	}
	template<class T, class Alloc>
	vector<T,Alloc>& vector<T,Alloc>::operator = (const vector& v){
		if(this != &v) {
			allocateAndCopy(v.start_, v.finish_);
		}
		return *this;
	}
	template<T , class Alloc>
	vector<T,Alloc>& vector<T,Alloc>::operator =(vector&& v) {
		if(this != &v) {
			destroyAndDeallocateAll();
			start_s = v.start_;
			finish_ = v.finish_;
			endOfStorage_ = v.endOfStorage_;
			v.start_ = v.finish_ = v.endOfStorage_ = 0;
		}
		return *this;
	}

	//*************���������������******************************
	template<class T, class Alloc>
	void vector<T,Alloc>::resize(size_type n, value_type val /* = value_type() */){
		if(n < size()){
			dataAllocator::destroy(start_ + n , finish_);
			finish_ = start_ + n;
		}
		else if(n > size() && n <= capacity()) {
			size_type lengthOfInsert = n - size();
			finish_ = TinySTL::uninitialized_fill_n(finish_,lengthOfInsert,val);
		}
		else if(n > capacity()) {
			size_type lengthOfInsert = n - size();
			T *newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
			T *newFinish = TinySTL::uninitialized_copy(begin(),end(),newStart);
			newFinish = TinySTL::uninitialized_fill_n(newFinish,lengthOfInsert,val);
			destroyAndDeallocateAll();
			start_ = newStart;
			finish_ = newFinish;
			endOfStorage_ = start_ + n;
		}
	}

	template<class T,class Alloc>
	void vector<T,Alloc>::reserve(size_type n) {
		if(n <= capacity())
			return;
		T *newStart = dataAllocator::allocate(n);
		T *newFinish = TinySTL::uninitialized_copy(begin(),end(),newStart);
		destroyAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + n;
	}

	//***************�޸���������ز���**************************
	template<class T,class Alloc>
	void vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator position) {
		return erase(position,position + 1);
	}
	template<class T,class Alloc>
	typename vector<T,Alloc>::iterator vector<T,Alloc>::erase(iterator first, iterator last){
		// β������������
		difference_type lenOfTail = end() - last;
		// ɾȥ������Ŀ
		difference_type lenOfRemoved = last - first;
		finish_ = finish_ - lenOfRemoved;
		for(; lenOfTail != 0; --lenOfTail){
			auto temp = (last - lenOfRemoved);
			*temp = *(last++);
		}
		return (first);
	}

	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T,Alloc>::reallocateAndCopy(iterator position, InputIterator first, InputIterator last){
		difference_type newCapacity = getNewCapacity(last - first);
		T *newStart = dataAllocator::allocate(newCapacity);
		T *newEndOfStorage = newStart + newCapacity;
		T *newFinish = TinySTL::uninitialized_copy(begin(),position,newStart);
		newFinish = TinySTL::uninitialized_copy(first,last,newFinish);
		newFinish = TinySTL::uninitialized_copy(position,end(),newFinish);
		
		destroyAndDeallocateAll();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = newEndOfStorage;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type& n, const value_type& val){
		difference_type newCapacity = getNewCapacity(n);
		T *newStart = dataAllocator::allocate(newCapacity);
		T *newEndOfStorage = newStart + newCapacity;
		T *newFinish = TinySTL::uninitialized_copy(begin(),position,newStart);
		newFinish = TinySTL::uninitialized_fill_n(newFinish,n,val);
		newFinish = TinySTL::uninitialized_fill_n(newFinish,n,val);
		newFinish = TinySTL::uninitialized_copy(position,end(),newFinish);

		destroyAndDeallocateAll();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = newEndOfStorage;
	}

	/// insert �Ȳ�д

	//***********�߼��Ƚϲ������*******************
	template<class T,class Alloc>
	bool vector<T,Alloc>::operator ==(const vector& v)const {
		if(size() != v.size()){
			return false;
		}
		else {
			auto ptr1 = start_;
			auto ptr2 = v.start_;
			for(; ptr1 != finish_ && ptr2 != v.finish_ ; ++ptr1, ++ptr2) {
				if(*ptr1 != *ptr2)
					return false;
			}
			return true;
		}
	}
	template<class T,class Alloc>
	bool vector<T,Alloc>::operator !=(const vector& v) const {
		return !(*this == v);
	}
	template<class T,class Alloc>
	bool operator == (const vector<T,Alloc>& v1, const vector<T,Alloc>&v2){
		return v1.operator =(v2);
	}
	template<class T,class Alloc>
	bool operator != (const vector<T,Alloc>& v1, const vector<T,Alloc>&v2){
		return !(v1 == v2);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::shrink_to_fit(){
		//dataAllocator::deallocate(finish_, endOfStorage_ - finish_);
		//endOfStorage_ = finish_;
		T* t = (T*)dataAllocator::allocate(size());
		finish_ = TinySTL::uninitialized_copy(start_, finish_, t);
		dataAllocator::deallocate(start_, capacity());
		start_ = t;
		endOfStorage_ = finish_;
	}

	template<class T, class Alloc>
	void vector<T,Alloc>::clear() {
		dataAllocator::destroy(start_,finish_);
		finish_ = start_;
	}
	template<class T, class Alloc>
	void vector<T,Alloc>::swap(vector& v){
		if(this != &v){
			TinySTL::swap(start_,v.start_);
			TinySTL::swap(finish_,v.finish_);
			TinySTL::swap(endOfStorage_,v.endOfStorage_)
		}
	}

	//*************�ڴ��������******************************
	template<class T, class Alloc>
	void vector<T,Alloc>::destroyAndDeallocateAll(){
		if(capacity() != 0) {
			dataAllocator::destroy(start_,finish_);
			dataAllocator::deallocate(start_,capacity());
		}
	}
	template<class T, class Alloc>
	void vector<T,Alloc>::allocateAndFillN(const size_type n, const value_type& value) {
		start_ = dataAllocator::allocate(n);
		TinySTL::uninitialized_fill_n(start_,n,value);
		finish_ = endOfStorage_ = start_ + n;
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T,Alloc>::allocateAndCopy(InputIterator first, InputIterator last) {
		start_ = dataAllocator::allocate(last -- first);
		finish_ = TinySTL::uninitialized_copy(first,last,start_);
		endOfStorage_ = finish_;
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T,Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type){
		allocateAndCopy(first,last);
	}
	template<class T,class Alloc>
	template<class InputIterator>
	void vector<T,Alloc>::vector_aux(Integer n, const value_type& value, std::true_type){
		allocateAndFillN(n,value);
	}
	
	template<class T, class Alloc>
	typename vector<T,Alloc>::size_type vector<T,Alloc>::getNewCapacity(size_type len)const {
		size_type oldCapacity = endOfStorage_ - start_;
		size_type res = TinySTL::max(oldCapacity,len);
		size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
		return newCapacity;
	}
}


#endif