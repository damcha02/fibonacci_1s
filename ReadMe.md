# Optimizing fibonacci 


## About
My goal is to get the biggest fibonacci number in 1 second.

Language: C++

My approaches so far:
- *recursive*: ends at n = 41, because of the time constraint
- *naive*: ends at n = 93, because of machine number constraints (i.e. silent overflow at n=94)


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
./main
```

## Reflections
The recursive implementation is really slow, with a time complexity of O(2^n).
The naive implementation is super fast compared to the recursive, with a time complexity of O(n).
Currently we are limited by the amount of bits that represent our numbers, we can only represent a 64-bit number, which we already surpass at n = 94. 

#### IDEA: 
Create a vector that will expand all the time and then to print the number we loop over the vector and print each single digit. Might make memory complexity worse but we will be able to represent larger numbers.