#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include "parallel_sort.hpp"

template <typename T>
using pair_vector = std::pair<std::vector<T>,std::vector<T> >;

class CustomType {
private:
	int value_;
public:
	CustomType() = default;
	CustomType(const CustomType&) = default;
	CustomType(int value) : value_(value) {};
	int Value() const {
		return value_;
	}
	friend bool operator==(const CustomType& l, const CustomType& r);

};
bool operator==(const CustomType& l, const CustomType& r){
	return l.value_ == r.value_;
}


template <typename T>
pair_vector<T> gen_vector(std::size_t size) {
	std::default_random_engine random_engine(0);
	std::uniform_int_distribution<> distribution(0, 10000);

	pair_vector<T> result;
	result.first.resize(size);
	result.second.resize(size);
	for (std::size_t i = 0; i < size; i++) {
		int j = distribution(random_engine);
		result.first[i] = j;
		result.second[i] = j;
	}
	return result;
}

template<typename F>
std::int64_t measure(F f) {
	auto started_at = std::chrono::steady_clock::now();
	f();
	auto ended_at = std::chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(ended_at - started_at).count();
}


void test_smoke_one_thead() {
	{
		pair_vector<int> target= gen_vector<int>(1);
		std::sort(target.first.begin(), target.first.end());
		parallel_sort(1, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "1. OK" << std::endl;
	}

	{
		pair_vector<int> target= gen_vector<int>(100);
		std::sort(target.first.begin(), target.first.end());
		parallel_sort(1, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "2. OK" << std::endl;
	}

	{
		pair_vector<int> target= gen_vector<int>(101);
		std::sort(target.first.begin(), target.first.end());
		parallel_sort(1, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "3. OK" << std::endl;
	}

	{
		pair_vector<char> target= gen_vector<char>(101);
		std::sort(target.first.begin(), target.first.end());
		parallel_sort(1, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "4. OK" << std::endl;
	}

}

void test_smoke_not_rand() {
	std::vector<int> pure = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	{
		pair_vector<int> target;
		target.first = target.second = pure;
		parallel_sort(1, target.first.begin(), target.first.end());
		parallel_sort(2, target.second.begin(), target.second.end());
		std::vector<int> answer = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		assert(target.first == target.second && target.first == answer);
		std::cout << "1. OK" << std::endl;
	}

	{
		pair_vector<int> target;
		target.first = target.second = pure;
		parallel_sort(3, target.first.begin(), target.first.end());
		parallel_sort(4, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "2. OK" << std::endl;
	}

	{
		pair_vector<int> target;
		target.first = target.second = pure;
		parallel_sort(1, target.first.begin(), target.first.end());
		parallel_sort(3, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "3. OK" << std::endl;
	}

	pure = {-1, -1, -1, -1};

	{
		pair_vector<int> target;
		target.first = target.second = pure;
		parallel_sort(1, target.first.begin(), target.first.end());
		parallel_sort(2, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "4. OK" << std::endl;
	}

	{
		pair_vector<int> target;
		target.first = target.second = pure;
		parallel_sort(3, target.first.begin(), target.first.end());
		parallel_sort(4, target.second.begin(), target.second.end());
		assert(target.first == target.second);
		std::cout << "5. OK" << std::endl;
	}

}


int main(int argc, char **argv) {
	assert(argc == 2);
	std::string type(argv[1]);
	if (type == "00-smoke")
		test_smoke_one_thead();
	else if (type == "01-smoke-not-rand")
		test_smoke_not_rand();
	else {
		std::cerr << "wrong usage" << std::endl;
	}
}

