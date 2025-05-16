#pragma once


#include "fibonacci_functions.hpp"
#include <fstream>
#include <filesystem>
#include <cmath>

void print_vec(std::vector<unsigned> vec, unsigned long long n, std::chrono::duration<double> duration_per_fibonacci_vec_appr);
void print_to_file(unsigned approach ,unsigned long long n, std::chrono::duration<double> duration_per_fib);

void run_recursive_approach();
void run_naive_approach();
void run_naive_vector_approach();

void benchmarking();
