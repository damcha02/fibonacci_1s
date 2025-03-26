# Optimizing fibonacci 


## About
My goal is to get the biggest fibonacci number in 1 second.

Language: C++

My approaches so far:
- *recursive*: ends at around n = 41, because of the time constraint
- *naive*: ends at n = 93, because of machine number constraints (i.e. silent overflow at n=94)
- *vector naive*: ends between 10'000 and 15'000 because of time constraint, but its somewhat random when it terminates. My guess is that it has something to do with how the caches work.


## How to use
Create a build directory, inside it run cmake and make:
```bash 
mkdir build
cd build
cmake ..
make
```
To run the program:
```bash
cd build
./main
```
To run google tests :
```bash
cd build/Tests
ctest
./test_functions
```
## Reflections
**23.03.2025** \
The recursive implementation is really slow, with a time complexity of O($2^n$).
The naive implementation is super fast compared to the recursive, with a time complexity of O($n$).
Currently we are limited by the amount of bits that represent our numbers, we can only represent a 64-bit number, which we already surpass at n = 94. 

**26.03.2025** \
We are not limited anymore by the amount digits we can represent, however we are now limited by time. Vector approach is in O($n^2$) and memory-heavy.

#### IDEA: 
Use OpenBlas library to do vector addition instead of my own function. OpenBlas will greatly help with managing cache and memory usage.