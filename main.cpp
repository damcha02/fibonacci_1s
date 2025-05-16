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
#include "helper_functions.hpp"

using namespace std::chrono_literals;

int main(){
    
    time_t timestamp;
    time(&timestamp);
    std::cout << ctime(&timestamp); // print current time
    struct tm datetime = *localtime(&timestamp);
    
    if(datetime.tm_hour >= 22 || datetime.tm_hour <= 4){
        std::cout << "Welcome late traveller, don't stay too long, sleep is more important than this! :)\n" << std::endl;
    }
    
    std::cout << "What's the biggest fibonacci number I can compute in a second without overflow?\n";
    std::cout << "\nWhich approach would you like to run?\n\n";
    std::cout << "(0) all\t (1) recursive\t(2) naive\t(3) naive with vectors\t(6) benchmarking\n";
    std::cout << "input > ";
    int input;
    std::cin >> input;

    switch(input){
        case 1:
            std::cout << "\nrecursive approach\n";
            run_recursive_approach();
            break;
        case 2:
            std::cout << "\nnaive approach\n";
            run_naive_approach();
            break;
        case 3:
            std::cout <<"\nvectorization approach\n";
            run_naive_vector_approach();
            break;
        case 6: 
            std::cout << "\nbenchmarking\n";
            benchmarking();
            break;
        default:
        //-------------------------------------------------------
            std::cout << "\nrecursive approach\n";
            run_recursive_approach();
        //-------------------------------------------------------
            std::cout << "\nnaive approach\n";
            run_naive_approach();
        //-------------------------------------------------------
            std::cout<<"\nvectorization approach\n";
            run_naive_vector_approach();
        //-------------------------------------------------------
            break;

    }

    return 0;
}