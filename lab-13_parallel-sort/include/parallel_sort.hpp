#pragma once

#include <cstdint>

template<typename It>
void parallel_sort(std::size_t thread_count, It begin, It end);

template<typename It, typename Comp>
void parallel_sort(std::size_t thread_count, It begin, It end, Comp comp);

template<typename It, typename Comp>
void my_merge_sort(It begin, It end, Comp comp);

template<typename It, typename Comp>
void my_inplace_merge(It begin, It middle, It end, Comp comp);

#include "parallel_sort.inl"
