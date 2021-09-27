#ifndef ITERATOR_H
#define ITERATOR_H

namespace ft
{
	template< class Category, class T, class Distance = std::ptrdiff_t,
					class Pointer = T*, class Reference = T& >
	class iterator {
	public:
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	struct random_access_iterator_tag	{};
	struct input_iterator_tag			{};
	struct output_iterator_tag			{};
}

#endif