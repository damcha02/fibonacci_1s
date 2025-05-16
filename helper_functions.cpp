#include "helper_functions.hpp"

using namespace std::chrono_literals;

//timer to time the functions as a thread
static bool done = false;
void timer(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "timer has finished" << std::endl;
    done = true;
}

void clear_csv_files() {
    std::ofstream("../benchmarking/benchmark_recursive.csv", std::ios::trunc).close();
    std::ofstream("../benchmarking/benchmark_naive.csv", std::ios::trunc).close();
    std::ofstream("../benchmarking/benchmark_vector.csv", std::ios::trunc).close();
}

void print_to_file(unsigned approach ,unsigned long long n, double duration_per_fib){
    //create a director 
    
    std::filesystem::create_directories("../benchmarking");
    std::ofstream outFile;
    switch(approach){
        case 1: 
            outFile.open("../benchmarking/benchmark_recursive.csv", std::ios::app); 
            break;
        case 2:
            outFile.open("../benchmarking/benchmark_naive.csv", std::ios::app);
            break;
        case 3:
            outFile.open("../benchmarking/benchmark_vector.csv", std::ios::app);
            break;
        default:
            std::cerr << "file not found" << std::endl;
            return;
    }

    if(outFile.is_open()){
        outFile << n << "," << duration_per_fib << "\n";
    }
}

void print_vec(std::vector<unsigned> vec, unsigned long long n, std::chrono::duration<double> duration_per_fibonacci_vec_appr){
    
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
    //print to file
    if(outFile.is_open()){
        outFile << "The " << n << "-" << suffix << " fibonacci number:\n";
        std::for_each(vec.rbegin(), vec.rend(), [&outFile](unsigned &n){outFile << n;});
        outFile << "\n";
        outFile << *vec.rbegin() << "." << *(++vec.rbegin()) << "e" << vec.size() - 1 << "\n";
        outFile << "time: " << duration_per_fibonacci_vec_appr.count() << "s\n";
        outFile.close();
    }

    //print to terminal
    std::cout << "computed fib(" << n << ")\tsaved to output/fibonacci_number.txt\n" <<
            "time: " << duration_per_fibonacci_vec_appr.count() <<"s\n";
     
}

void average_out_and_add_time(double time1, int n){
    double time_to_add;

    for(int i = 94; i < 20000; i += 250){
        time_to_add = time1 * (i / n);
        if(time_to_add > 1.0) break;    
        print_to_file(2, i, time_to_add);
    }
}

void benchmarking(){
    clear_csv_files();

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration_per_fibonacci_number_recursive = 0s;
    for(unsigned n = 0; n < 42; ++n){
        start = std::chrono::high_resolution_clock::now();
        recursive_fb(n);
        end = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_number_recursive = end - start;
        print_to_file(1, n, duration_per_fibonacci_number_recursive.count());
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> start_naive, end_naive;
    std::chrono::duration<double> duration_per_fibonacci_number_naive = 0s;
    double time_array[94];
    for(unsigned n = 0; n <= 93; ++n){
        start_naive = std::chrono::high_resolution_clock::now();
        naive_fb(n);
        end_naive = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_number_naive = end_naive - start_naive;
        print_to_file(2, n, duration_per_fibonacci_number_naive.count());
        time_array[n] = duration_per_fibonacci_number_naive.count();
    }
    average_out_and_add_time(time_array[93], 93);

    std::chrono::time_point<std::chrono::high_resolution_clock> start_vec_appr, end_vec_appr;
    std::chrono::duration<double> duration_per_fibonacci_vec_appr = 0s;
    for(unsigned n = 0; n <= 15000; n += 120){
        start_vec_appr = std::chrono::high_resolution_clock::now();
        vectorization_fb(n);
        end_vec_appr = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_vec_appr = end_vec_appr - start_vec_appr;
        if(duration_per_fibonacci_vec_appr.count() < 1.0) print_to_file(3, n, duration_per_fibonacci_vec_appr.count());
    }
}
void run_recursive_approach(){

    unsigned long long num = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration_per_fibonacci_number_recursive = 0s;

    unsigned long long low = 0, high = 50, best = 0;
    while(low <= high){
        unsigned long long mid = low + (high - low) / 2;
        start = std::chrono::high_resolution_clock::now();
        num = recursive_fb(mid);
        end = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_number_recursive = end - start;
        if(duration_per_fibonacci_number_recursive < 1s){
            best = mid;
            low = mid + 1;
        } else high = mid - 1;
    }

    // for(int mid = 38; mid < 45; ++mid){
    //     start = std::chrono::high_resolution_clock::now();
    //     num = recursive_fb(mid);
    //     end = std::chrono::high_resolution_clock::now();
    //     duration_per_fibonacci_number_recursive = end - start;
    //     std::cout << "n = " << mid <<"\ttime: " << duration_per_fibonacci_number_recursive.count() << std::endl;   
    // }

    std::cout << "fib(" << best << ") = " << num << '\t' << "time: " << duration_per_fibonacci_number_recursive.count() << "s\n";
    std::cout << "check result correctness: ";
    if(num == naive_fb(best)) std::cout << "correct for (n = "<< best << ")!\n";
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
    std::cout << "check result correctess: ";
    --j;
    num_naive = naive_fb(j);
    if(num_naive != 0) std::cout << "correct for (n = "<< j << ")!\n";
    else std::cout << "incorrect!\n";
    
}


void run_naive_vector_approach(){
    
    std::chrono::time_point<std::chrono::high_resolution_clock> start_vec_appr, end_vec_appr;
    std::chrono::duration<double> duration_per_fibonacci_vec_appr = 0s;

    std::vector<unsigned> result;
    // binary search
    unsigned long low = 0, high = 20000, best = 0;
    while( low <= high ){
        unsigned long mid = low + (high - low) / 2;        
        start_vec_appr = std::chrono::high_resolution_clock::now();
        result = vectorization_fb(mid);
        end_vec_appr = std::chrono::high_resolution_clock::now();
        duration_per_fibonacci_vec_appr = end_vec_appr - start_vec_appr;
        if(duration_per_fibonacci_vec_appr < 1s){
            best = mid;
            low = mid + 1;
        } else high = mid - 1;
    }
    print_vec(vectorization_fb(best), best, duration_per_fibonacci_vec_appr);
}