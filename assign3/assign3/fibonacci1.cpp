/******************************************************************************
;@
;@ Student Name 1: student1
;@ Student 1 #: 123456781
;@ Student 1 userid (email): stu1 (stu1@sfu.ca)
;@
;@ Student Name 2: student2
;@ Student 2 #: 123456782
;@ Student 2 userid (email): stu2 (stu2@sfu.ca)
;@
;@ Below, edit to list any people who helped you with the code in this file,
;@      or put ‘none’ if nobody helped (the two of) you.
;@
;@ Helpers: _everybody helped us/me with the assignment (list names or put ‘none’)__
;@
;@ Also, reference resources beyond the course textbook and the course pages on Canvas
;@ that you used in making your submission.
;@
;@ Resources:  ___________
;@
;@% Instructions:
;@ * Put your name(s), student number(s), userid(s) in the above section.
;@ * Edit the "Helpers" line and "Resources" line.
;@ * Your group name should be "A3_<userid1>_<userid2>" (eg. A3_stu1_stu2)
;@ * Form groups as described at:  https://courses.cs.sfu.ca/docs/students
;@ * Submit your file to courses.cs.sfu.ca
;@
;@ Name        : fibonacci1.cpp
******************************************************************************/
//#include <array>
#include "fibonacci1.hpp"

static long highestSubscript{1};

static fibonacciType1 evenSubscriptFib{0};

static fibonacciType1 oddSubscriptFib{1};

void fibonacciOdd(long subscript);

// mutually recursive functions

// function that calculates a Fibonacci number with an even index
void fibonacciEven(long subscript)
{
   if (subscript > highestSubscript) {
      fibonacciEven(subscript - 2); // recursion step
      fibonacciOdd(subscript - 1);  // recursion step
      highestSubscript = subscript;
      evenSubscriptFib += oddSubscriptFib;
   }
}

// function that calculates a Fibonacci number with an odd index
void fibonacciOdd(long subscript)
{
   if (subscript > highestSubscript) {
      fibonacciOdd(subscript - 2);  // recursion step
      fibonacciEven(subscript - 1); // recursion step
      highestSubscript = subscript;
      oddSubscriptFib += evenSubscriptFib;
   }
}

// Fibonacci function
fibonacciType1& fibonacci1(long subscript)
{
   // *** put a static array here ***
//   static constexpr std::array eSFA{
//      #include "eSFA-contents-cpp_int.txt"
//   };
   // *** put a static array here ***

   if (subscript < highestSubscript - 1) {
      highestSubscript = 1;
//      fibonacciType1 tempE{"1500000000000000"}; // create large number from a string
//      evenSubscriptFib = tempE;
      evenSubscriptFib = 0;
      oddSubscriptFib = 1;
   }
   if (subscript % 2) {
      fibonacciOdd(subscript);
      return oddSubscriptFib;
   }
   else {
      fibonacciEven(subscript);
      return evenSubscriptFib;
   }
}



