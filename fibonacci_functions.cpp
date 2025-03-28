#include "fibonacci_functions.hpp"

using namespace std::chrono_literals;

// global variables
bool global_excede_time = false;  // actual definition


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
std::vector<unsigned> vector_addition(std::vector<unsigned>& num1, std::vector<unsigned>& num2){
    // num2 should always be bigger or equal to num1 because it is always the next number in the sequence
    assert(num1.size() <= num2.size()); 

    std::vector<unsigned> result;
    result.reserve(num2.size() + 1);
    int carry = 0;
    for(int i = 0; i < num2.size(); ++i){
        //prevent accessing num1 out of bounds
        if(i < num1.size()){
            if(num1.at(i) + num2.at(i) + carry < 10){
                result.push_back(num1.at(i) + num2.at(i) + carry);
                carry = 0; // carry in either case going to be 0, wether it was or wasnt already 0
            }
            if(num1.at(i) + num2.at(i) + carry >= 10){
                result.push_back( (num1.at(i) + num2.at(i) + carry) % 10 );
                carry = 1; // carry in either case going to be 1, wether it was or wasnt already 1
            }
        }
        else{
            if(num2.at(i) + carry < 10){
                result.push_back( num2.at(i) + carry );
                carry = 0;
            }
            if(num2.at(i) + carry >= 10){
                result.push_back( (num2.at(i) + carry) % 10 );
                carry = 1;
            }
        }
    }
    if(carry == 1){
        result.push_back(carry);
    }
    std::swap(num1, num2);
    num2 = result;
    return result;
}


std::vector<unsigned> vectorization_fb(long unsigned n){
    std::vector<unsigned> num1, num2, result;
    num1.push_back(0);
    num2.push_back(1);
    if(n == 0) return num1;
    if(n == 1) return num2;
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start_vec_appr, end_vec_appr;
    std::chrono::duration<double> duration_per_fibonacci_vec_appr = 0s;

    start_vec_appr = std::chrono::high_resolution_clock::now();
    for(int i = 2; i <= n; ++i){
        result = vector_addition(num1, num2);
    }
    end_vec_appr = std::chrono::high_resolution_clock::now();

    duration_per_fibonacci_vec_appr = end_vec_appr - start_vec_appr;
    if(duration_per_fibonacci_vec_appr >= 1s){
        global_excede_time = true;
        return num1;
    }
    return result;
}
