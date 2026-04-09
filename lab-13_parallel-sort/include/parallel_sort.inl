#pragma once

#include <vector>
#include <iterator>
#include <thread>
#include <functional>
#include <algorithm>
template<typename It, typename Comp>
void my_merge_sort(It begin, It end, Comp comp) {
    std::size_t size = end - begin;
    if (size <= 1) return;

    It middle = begin + size / 2;
    my_merge_sort(begin, middle, comp);
    my_merge_sort(middle, end, comp);

    using Value = typename std::iterator_traits<It>::value_type;
    std::vector<Value> merged;
    merged.reserve(size);

    It left = begin;
    It right = middle;

    while (left != middle && right != end) {
        if (comp(*right, *left)) {
            merged.push_back(std::move(*right));
            ++right;
        } else {
            merged.push_back(std::move(*left));
            ++left;
        }
    }

    std::move(left, middle, std::back_inserter(merged));
    std::move(right, end, std::back_inserter(merged));
    std::move(merged.begin(), merged.end(), begin);
}

template<typename It, typename Comp>
void my_inplace_merge(It begin, It middle, It end, Comp comp) {
    std::inplace_merge(begin, middle, end, comp);
}

template<typename It, typename Comp>
void parallel_sort(std::size_t thread_count, It begin, It end, Comp comp) {
    std::size_t size_data = end - begin; 
    if (size_data <= 1) return;

    if (thread_count > size_data)
        thread_count = size_data;

    std::size_t chunk_size = size_data / thread_count;
    std::size_t remainder = size_data % thread_count;

    std::vector<It> chunk_starts;
    chunk_starts.reserve(thread_count + 1);
    chunk_starts.push_back(begin);

    std::size_t i = 0;
    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (std::size_t j = 0; j < thread_count; ++j) {
        std::size_t current_chunk_size = chunk_size + (j == thread_count - 1 ? remainder : 0);

        It chunk_begin = begin + i;
        It chunk_end = chunk_begin + current_chunk_size;
        chunk_starts.push_back(chunk_end);

        threads.emplace_back([chunk_begin, chunk_end, comp]() {
            my_merge_sort(chunk_begin, chunk_end, comp);
        });

        i += current_chunk_size;
    }

    for (auto& t : threads) t.join();

    while (chunk_starts.size() > 2) {
        std::vector<It> new_starts;
        new_starts.reserve((chunk_starts.size() / 2) + 1);
        new_starts.push_back(chunk_starts[0]);

        for (std::size_t i = 1; i + 1 < chunk_starts.size(); i += 2) {
            It left = chunk_starts[i - 1];
            It middle = chunk_starts[i];
            It right = chunk_starts[i + 1];
            my_inplace_merge(left, middle, right, comp);
            new_starts.push_back(right);
        }

        if ((chunk_starts.size() - 1) % 2 == 1) {
            new_starts.push_back(chunk_starts.back());
        }

        chunk_starts = std::move(new_starts);
    }

    if (chunk_starts.size() == 2) {
        my_inplace_merge(chunk_starts[0], chunk_starts[1], end, comp);
    }
}

template<typename It>
void parallel_sort(std::size_t thread_count, It begin, It end) {
    parallel_sort(thread_count, begin, end, std::less<typename std::iterator_traits<It>::value_type>());
}
