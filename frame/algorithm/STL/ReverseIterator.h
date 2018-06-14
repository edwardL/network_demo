#ifndef _REVERSE_ITERATOR_H
#define _REVERSE_ITERATOR_H

#include "Iterator.h"

namespace TinySTL {
	template<class Iterator>
	class reverse_iterator_t{
	public:
		typedef Iterator		iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type defference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;

		typedef const pointer const_pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef const reference const_reference;

	private:
		Iterator base_;
		Iterator cur_;

	public:
		// 构造复制析构相关
		reverse_iterator_t():base_(0),cur_(0){}
		explicit reverse_iterator_t(const iterator_type& it):base(it) {
			auto temp = it;
			cur_ = --temp;
		}
		template<clas Iter>
		reverse_iterator_t(const reverse_iterator_t<Iter>& rev_it) {
			base_ = (iterator_type)rev_it.base();
			auto temp = base_;
			cur_ = --temp;
		}

	};
}


#endif