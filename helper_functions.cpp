#include "helper_functions.hpp"

using namespace std::chrono_literals;

//timer to time the functions as a thread
static bool done = false;
void timer(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "timer has finished" << std::endl;
    done = true;
}


void print_vec(std::vector<unsigned> vec, unsigned long long n){
    
    //create a directory for the output file if doesnt exist already
    std::filesystem::create_directories("../output");
    
    //create an output stream file and open it
    std::ofstream outFile("../output/fibonacci_number.txt");

    std::string suffix;
    switch(n % 10){
        case 1: 
            suffix = "st";
            break;
        case 2: 
            suffix = "nd";
            break;
        case 3:
            suffix = "rd";
            break;
        default:
            suffix = "th";
            break;
    }

    if(outFile.is_open()){
        outFile << "The " << n << "-" << suffix << " fibonacci number:\n";
        std::for_each(vec.rbegin(), vec.rend(), [&outFile](unsigned &n){outFile << n;});
        outFile << "\n";
        outFile.close();
    }   
}


void run_recursive_approach(){
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
}


void run_naive_approach(){
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
    
}


void run_naive_vector_approach(){
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start_vec_appr, end_vec_appr;
    std::chrono::duration<double> duration_per_fibonacci_vec_appr = 0s;

    std::vector<unsigned> result;
    for(int i = 15000; ; ++i){
        start_vec_appr = std::chrono::high_resolution_clock::now();
        result = vectorization_fb(i);
        end_vec_appr = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_vec_appr = end_vec_appr - start_vec_appr;
        std::cout << "time: " << duration_per_fibonacci_vec_appr.count() << "s\n";
        if(global_excede_time){
            std::cout << "fib(" << i << ") = ";
            print_vec(vectorization_fb(i), i);
            std::cout<<std::endl;
            break;
        }
        
    }
}