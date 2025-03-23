/**
 * @brief fibonacci sequence in one second, how far can we get?
 * 
 * f(0) = 0
 * f(1) = 1
 * f(2) = 1
 * f(n) = f(n - 2) + f(n - 1) 
 * 
 * @return n and n-th fibonacci number
 */


#include "fibonacci_functions.hpp"
using namespace std::chrono_literals;


static bool done = false;
void timer(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "timer has finished" << std::endl;
    done = true;
}


int main(){

    std::chrono::time_point<std::chrono::high_resolution_clock> start1, end1;
    start1 = std::chrono::high_resolution_clock::now();
    std::cout << "What's the biggest fibonacci number I can compute in a second without overflow?\n";
    end1 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds = end1 - start1;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end1);
    std::cout << std::ctime(&end_time);

//////////////////////////////////////////////////////////
    std::cout << "\nrecursive approach\n";
    // std::thread t1 (timer);
    int i = 0;
    unsigned long long num = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration_per_fibonacci_number_recursive = 0s;
    while(duration_per_fibonacci_number_recursive < 1s){
        ++i;
        start = std::chrono::high_resolution_clock::now();
        num = recursive_fb(i);
        end = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_number_recursive = end - start;
        if(duration_per_fibonacci_number_recursive > 1s){
            --i;
            start = std::chrono::high_resolution_clock::now();
            num = recursive_fb(i);
            end = std::chrono::high_resolution_clock::now();
            duration_per_fibonacci_number_recursive = end - start;
            break;
        }
    }
    std::cout << "fib(" << i << ") = " << num << '\t' << "time: " << duration_per_fibonacci_number_recursive.count() << "s\n";
    std::cout << "check result correctness: ";
    if(num == naive_fb(i)) std::cout << "correct(n = "<< i << ")!\n";
    else std::cout << "incorrect!\n";

////////////////////////////////////////////
    std::cout << "\nnaive approach\n";

    unsigned long long num_naive = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_naive, end_naive;
    std::chrono::duration<double> duration_per_fibonacci_number_naive = 0s;

    int j = 1;
    while(true){
        
        start_naive = std::chrono::high_resolution_clock::now();
        auto temp = naive_fb(j);
        end_naive = std::chrono::high_resolution_clock::now();

        if(temp == 0){
            std::cout << "fib(" << j - 1 << ") = " << num_naive << '\t' << "time: " 
            << duration_per_fibonacci_number_naive.count() <<"s"<< std::endl;
            break;
        }

        num_naive = temp;
        duration_per_fibonacci_number_naive = end_naive - start_naive;
        ++j;
    }
    // std::cout << "fib(" << j << ") = " << num_naive << '\t' << "time: " << duration_per_fibonacci_number_naive.count() << std::endl;
    std::cout << "check result correctess: ";
    --j;
    num_naive = naive_fb(j);
    if(num_naive != 0) std::cout << "correct for (n = "<< j << ")!\n";
    else std::cout << "incorrect!\n";

    // std::cout << "fib(" << j << ") = " << num_naive << std::endl;
    
    return 0;
}


