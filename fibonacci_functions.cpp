#include "fibonacci_functions.hpp"

unsigned long long recursive_fb(unsigned long n){
    if(n < 2) return n;
    return recursive_fb(n - 1) + recursive_fb(n - 2);
}

unsigned long long naive_fb(long unsigned n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    unsigned long long num1 = 0, num2 = 1, result = 0;

    for(int i = 2; i <= n; ++i){
        if(ULLONG_MAX - num2 < num1){
            std::cerr << "Overflow detected at n = " << i << '\n';
            return 0;
        }
        result = num1 + num2;
        num1 = num2;
        num2 = result;
    }
    return result;
}