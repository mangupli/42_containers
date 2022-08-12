# 42_containers

The project where we had to re-implement the data structures and their iterators of the standart library c++98:

- Vector
- Map
- Stack

### This project is aimed for:

1. To improve the skills of object-oriented programming on c++
2. To study thoroughly how the basic data structures work because you had to face the same problems of contrcuting them as the developers of the standard library
3. To get familiar with the red-black tree which is a bad-ass
4. To write your unit-tests

### How it works:

Clone the repo. The rule **make** creates an executable. The rule **make run** compiles everything and lunches the executable.

there is **main.cpp** in **./tests** directory, that call the specific tests functions which looks like this:
```
int main()
{
	stack_tests();
	vector_tests();
	map_tests();
	return 0;
}
```
**Tests:**

<img width="341" alt="Screen Shot 2022-08-12 at 19 47 45" src="https://user-images.githubusercontent.com/73948830/184405697-fa2292fe-b7fc-4a51-ad0f-b30f400e0809.png">

### My step-by-step guide 

1. Implement the stack with the underlying standard container(deque or vector) - then you'll change it to your own. Tests.
2. Implement the methods of vector that don't use iterators - push_back, size, capcity, etc.
3. Implement iterator system of the vector.
4. SFINAE and constructors of the vector. Tests.
5. Red-map tree. Rotations, insert, erase and iterators.
6. Map methods. Tests.

### Useful resources:

1. [INTERNATIONAL STANDARD C++98](https://www.lirmm.fr/~ducour/Doc-objets/ISO+IEC+14882-1998.pdf)


2. [Cormen, Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990) - the golden recourses for implementing red-black tree
(The book is in russian translation)](https://vk.com/doc179585542_437543470?hash=83777f0404cb6d6d7d&dl=5c71c40cb399227ec9)


3. [The best russian lector on c++ on youtube - the practicing programmer from Yandex (in russian)](https://www.youtube.com/watch?v=2PM4TgCZIQs&list=PL4_hYwCyhAvY2dY_tnTv3-TJThzcloCvM)

4. [Traversing Trees with Iterators](https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html)

