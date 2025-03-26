#include <gtest/gtest.h>

#include "../fibonacci_functions.hpp"



TEST(VectorAdditionTest, TwoFourDigitVectors){
    std::vector<unsigned> number1 = {1, 2, 3, 4};
    std::vector<unsigned> number2 = {2, 8, 4, 6};
    std::vector<unsigned> copy_n2 = number2;

    // the solution vector should carry one digit along
    std::vector<unsigned> solution = {3, 0, 8, 0, 1};

    std::vector<unsigned> computed_result = vector_addition(number1, number2);

    EXPECT_EQ(solution, computed_result);
    EXPECT_EQ(solution, number2); // number 2 should be updated immediately to solution
    EXPECT_EQ(number1, copy_n2); //number 1 should be updated to previous number 2 (i.e. copy_n2)
}


TEST(VectorAdditionTest, TwoDifferentSizeNumbersN2biggerThanN1){
    std::vector<unsigned> number1 = {1, 2, 3, 4};
    std::vector<unsigned> number2 = {2, 8, 4, 6, 7};
    std::vector<unsigned> copy_n2 = number2;

    // the solution vector should carry one digit along
    std::vector<unsigned> solution = {3, 0, 8, 0, 8};

    std::vector<unsigned> computed_result = vector_addition(number1, number2);

    EXPECT_EQ(solution, computed_result);
    EXPECT_EQ(solution, number2); // number 2 should be updated immediately to solution
    EXPECT_EQ(number1, copy_n2); //number 1 should be updated to previous number 2 (i.e. copy_n2)
}

TEST(VectorAdditionTest, TwoDifferentSizeNumbersN1biggerThanN2){
    std::vector<unsigned> number1 = {1, 2, 3, 4, 7};
    std::vector<unsigned> number2 = {2, 8, 4, 6};
    std::vector<unsigned> copy_n2 = number2;

    // the solution vector should carry one digit along
    std::vector<unsigned> solution = {3, 0, 8, 0, 8};

    // std::vector<unsigned> computed_result = vector_addition(number1, number2);

    EXPECT_DEATH({
        vector_addition(number1, number2);
    }, ".*");
    
}
TEST(FibonacciFunctions, BasicFibonacciTest){
    std::map<unsigned, unsigned> fib_map = {{0, 0}, {1, 1}, {2, 1}, {3, 2}, {4, 3}, {5, 5}, {6, 8}, {7, 13}, {8, 21}, {9, 34}};

    for(unsigned i = 0; i < fib_map.size(); ++i){
        EXPECT_EQ(fib_map[i], recursive_fb(i));
        EXPECT_EQ(fib_map[i], naive_fb(i));
    }
}

TEST(FibonacciFunctions, BasicFibonacciVectorTest){
    std::map<unsigned, std::vector<unsigned>> fib_map_v = {{0, {0}}, {1, {1}}, {2, {1}}, {3, {2}}, {4, {3}}, {5, {5}}, {6, {8}}, {7, {3,1}}, {8, {1,2}}, {9, {4,3}}};
    for(unsigned i = 0; i < fib_map_v.size(); ++i){
        EXPECT_EQ(fib_map_v[i], vectorization_fb(i));
    }
    
}

TEST(FibonacciFunctions, RecursiveAndNaiveUntilFib30){
    for(int i = 0; i <= 30; ++i){
        EXPECT_EQ(recursive_fb(i), naive_fb(i));
    }
}

// TEST(FibonacciFunctions, NaiveAndVectorizationUntilFib90){
//     std::vector<unsigned> naive_result_v;
//     unsigned long long naive_result;
//     for(int i = 0; i <= 90; ++i){
//         while(naive_result / 10 > 0){
//             naive_result_v.push_back(naive_result % 10);
//             naive_result = naive_result / 10;
//         }
//         EXPECT_EQ(naive_result_v, vectorization_fb(i));
//     }
// }


// main func to run all tests
int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}