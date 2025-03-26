#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include <climits>
#include <vector>
#include <assert.h>
#include <algorithm>

extern bool global_excede_time;

unsigned long long recursive_fb(unsigned long n);


unsigned long long naive_fb(long unsigned n);

std::vector<unsigned> vector_addition(std::vector<unsigned>& num1, std::vector<unsigned>& num2);

std::vector<unsigned> vectorization_fb(long unsigned n);

void print(std::vector<unsigned> vec);

// void test_recursive();

// void test_naive();