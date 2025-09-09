#include <gtest/gtest.h>
#include <cmath>
#include <vector>
using namespace std;

// a. Function f1
int f1(int x) {
    if (x > 10)
        return 2 * x;
    else
        return -x;
}

// b. Function f1 wrong
int f1_wrong(int x) {
    if (x > 10)
        return 2 * x;
    else if (x > 0)
        return -x;
    else
        return 2 * x;
}

// c. Function f2
int f2(int x) {
    if (x < 10)
        return 2 * x;
    else if (x < 2)
        return -x;
    else
        return 2 * x;
}

// d. Function f3
int f3(int x) {
    return 2 * x;
}

// e. Function findMax 
int findMax(int num1, int num2, int num3) {
    int max = 0;
    if ((num1 > num2) && (num1 > num3)) max = num1;
    if ((num2 > num1) && (num2 > num3)) max = num2;
    if ((num3 > num1) && (num3 > num2)) max = num3;
    return max;
}

// Quartic solver

int solveQuartic(double a, double b, double c, vector<double>& x) {
    x.clear();
    if (a == 0 && b == 0 && c == 0)
        return -1; // Infinite solutions

    if (a == 0 && b == 0)
        return 0;  // No solution

    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;
        x.push_back(sqrt(y));
        x.push_back(-sqrt(y));
        return 2;
    }

    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;

    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);

    if (y1 >= 0) {
        x.push_back(sqrt(y1));
        x.push_back(-sqrt(y1));
    }
    if (y2 >= 0 && y2 != y1) {
        x.push_back(sqrt(y2));
        x.push_back(-sqrt(y2));
    }

    return x.size();
}

// Unit test

// f1
TEST(FunctionTest, F1_Correct) {
    EXPECT_EQ(f1(11), 22);   // x > 10
    EXPECT_EQ(f1(5), -5);    // x <= 10
    EXPECT_EQ(f1(-3), 3);    // x <= 10
}

TEST(FunctionTest, F1_Wrong) {
    EXPECT_EQ(f1_wrong(11), 22);
    EXPECT_EQ(f1_wrong(5), -5);
    // Wrong code still testing the error branch
    EXPECT_EQ(f1_wrong(-3), 3); 
}

// f2 
TEST(FunctionTest, F2_Test) {
    EXPECT_EQ(f2(5), 10);
    EXPECT_EQ(f2(15), 30);
    EXPECT_EQ(f2(1), 2);
}

// f3 
TEST(FunctionTest, F3_Test) {
    EXPECT_EQ(f3(1), 2);
    EXPECT_EQ(f3(10), 20);
}

// findMax
TEST(FunctionTest, FindMax_Test) {
    EXPECT_EQ(findMax(5, 3, 2), 5);
    EXPECT_EQ(findMax(3, 6, 1), 6);
    EXPECT_EQ(findMax(1, 4, 7), 7);
    // Wrong code will FAIL
    EXPECT_EQ(findMax(2, 2, 2), 2);   
    EXPECT_EQ(findMax(-1, -2, -3), -1); 
}

// Quartic solve
TEST(QuarticSolverTest, BasicCases) {
    vector<double> x;

    // Infinite solutions
    EXPECT_EQ(solveQuartic(0, 0, 0, x), -1); 
    // No solution
    EXPECT_EQ(solveQuartic(0, 0, 5, x), 0); 

    EXPECT_EQ(solveQuartic(0, 2, -8, x), 2);
    EXPECT_NEAR(x[0], 2.0, 1e-6);
    EXPECT_NEAR(x[1], -2.0, 1e-6);

    EXPECT_EQ(solveQuartic(1, -3, 2, x), 4);
    vector<double> expected = { sqrt(2), -sqrt(2), 1.0, -1.0 };
    for (size_t i = 0; i < x.size(); i++)
        EXPECT_NEAR(x[i], expected[i], 1e-6);
}

// main
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

