cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_containers main.cpp
        vector.hpp
        iterator_traits.hpp
        iterator.hpp
        random_access_iterator.hpp
        utils.hpp
        InputIterator.hpp



        )
