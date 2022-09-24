/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "testing/SimpleTest.h"
#include "perfect.h"
using namespace std;




/* This function takes one argument `n` and calculates the sum
 * of all proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division.
 *
 * Note: long is a C++ type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* This function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* This function does an exhaustive search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: This function is using sqrt method to minimize the calculation
 * compare to the divisorsum function from N^2 to N*sqrt(N).
 * It also cause a judgement whether the input n is a square number.
 * it need to judge whether it is a int_sqrt number.
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */
    long total;
    if(int(sqrt(n)) * int(sqrt(n)) == n){
         total = -n - int(sqrt(n));
    }
    else{
         total = -n;
    }
    for (long divisor = 1; divisor <= int(sqrt(n)); divisor++) {
        if (n % divisor == 0) {
            total += (divisor + n / divisor);
        }
    }
    return total;
}

/* TODO: This function is to judge whether the number is  a perfect number using a faster factor number sum function
 *
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
    return (n != 0) && (n == smarterSum(n));

}

/* TODO: This function does an more smart search for perfect numbers.
 * It takes one argument `stop` and searches the range 1 to `stop`,
 * checking each number to see whether it is perfect and if so,
 * printing it to the console.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: This function using Euclid to find perfect number if (2^k-1) is prime number
 * so 2^(k-1)*(2^k-1) is perfect number.
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    int k;
    int i = 0;
    for(k=1;;k++){
        if(smarterSum(pow(2,k)-1) == 1){
            i++;

        }
        if(i == n){
            return pow(2,(k - 1)) * (pow(2,k) - 1);
        }
    }
}


/* * * * * * Test Cases * * * * * */

/* Note: Do not add or remove any of the PROVIDED_TEST tests.
 * You should add your own STUDENT_TEST tests below the
 * provided tests.
 */


void findNthPerfectEuclid_test(const long &n){
    int i;
    for (i=1;i<10000;i++){
    findNthPerfectEuclid(n);

    }

}

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trials of findPerfects on doubling input sizes") {
    TIME_OPERATION(10000, findPerfects(10000));
    TIME_OPERATION(20000, findPerfects(20000));
    TIME_OPERATION(40000, findPerfects(40000));
}

// TODO: add your student test cases here
//STUDENT_TEST("Time trials of findPerfects on doubling input sizes") {

//    TIME_OPERATION(15000, findPerfects(15000));
//    TIME_OPERATION(30000, findPerfects(30000));
//    TIME_OPERATION(60000, findPerfects(60000));
//    TIME_OPERATION(120000, findPerfects(120000));
//}

STUDENT_TEST("for test whether is perfect can detect the negative value and return false"){
    EXPECT(!isPerfect(5));
    EXPECT(!isPerfect(1000));
    EXPECT(!isPerfect(323));

}
STUDENT_TEST("whether smarter be strong for replace divisorSum") {
    EXPECT_EQUAL(divisorSum(25),smarterSum(25));
    EXPECT_EQUAL(divisorSum(10000),smarterSum(10000));
    EXPECT_EQUAL(divisorSum(323231),smarterSum(323231));
}

//STUDENT_TEST("Time trials of findPerfectsSmarter on doubling input sizes") {
//    TIME_OPERATION(600000, findPerfectsSmarter(600000));
//    TIME_OPERATION(1200000, findPerfectsSmarter(1200000));
//    TIME_OPERATION(2400000, findPerfectsSmarter(2400000));
//    TIME_OPERATION(4800000, findPerfectsSmarter(4800000));
//}

STUDENT_TEST("To Verify the correctness of the function findNthPerfectEuclid") {
    EXPECT(isPerfectSmarter(findNthPerfectEuclid(3)));//normal test
    //abnormal test
    EXPECT_EQUAL(findNthPerfectEuclid(1),6);//edge test
    TIME_OPERATION(4,findNthPerfectEuclid_test(4));
    TIME_OPERATION(5,findNthPerfectEuclid_test(5));//edge test

}

