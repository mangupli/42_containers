#ifndef UTILS_H
#define UTILS_H

#include "iterator_traits.hpp"


//	struct nullptr_t
//	{
//		template<class T>
//		operator T*() const { return 0; }
//
//		template<class C, class T>
//		operator T C::*() const { return 0; }
//
//	};
//
//	nullptr_t nullptr;

namespace ft {

	template<class InputIterator>
			typename iterator_traits<InputIterator>::difference_type
							distance(InputIterator first, InputIterator last)
			{
				typename iterator_traits<InputIterator>::difference_type dist = 0;
				while (first != last)
				{
					++first;
					++dist;
				}
				return dist;
			}

}





#endif