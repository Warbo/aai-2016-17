#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// It's useful to output strings of text while programming, since it can show us
// what's going on without having to use a debugger. This is known as "printf
// debugging".

// In C, strings of text are arrays (pointers to) characters. We can manipulate
// such strings using functions like strcpy and strcat. Be sure you have enough
// memory to store your string! You can check the length of a string using
// strlen, and allocate memory using malloc; remember to free the memory after!

// Here is an example of manipulating strings: creating a greeting from a name
char* hello(char* s) {
  int   slen    = strlen(s);         // Find the length of string s
  char* message = malloc(slen + 8);  // 8 chars for "Hello ", "!" and a NUL byte

  strcpy(message, "Hello ");  // strcpy puts the string at the start of message
  strcat(message, s);         // strcat puts the string at the first NUL
  strcat(message, "!");

  return message;  // Remember to free this once you're done with it
}

// Here's an example of using the hello function in a program, and how we can
// output strings using the printf function. If we rename this function "main"
// (and comment-out the "main" function defined at the bottom of this file!) it
// will be used as the "start" of the program when compiled and executed.
int exampleMain() {
  // Store the result in a variable so we can use it twice: once in our output
  // and once to free the memory afterwards.
  char* message = hello("Bob");

  // The first argument to printf is a "format string". There is a very detailed
  // description available at https://en.wikipedia.org/wiki/Printf_format_string
  printf("%s\n", message);

  // Reclaim the allocated memory to avoid a "memory leak"
  free(message);

  // 0 indicates that we've finished without error
  return 0;
}

// Writing checks inside a "main" function like this is a very laborious and
// error-prone approach, since the checks can get mixed up with the real code,
// we may have to throw away checks as more of our real main function gets
// written, we might end up spitting out lots of debugging messages during
// normal operation, and the output may have to be read by a person to figure
// out if anything went wrong or not.

// A much better approach is to define a "test suite", separate from the real
// code, where we can add all kinds of checks, and have them tested over and
// over automatically. This way, we can be confident that our code is working
// as intended, will continue to be checked in the future, and we don't need to
// see useless debugging noise in the terminal when using our programs.

// Test suites can be large and complicated, but we'll just use these little
// macros to define and run tests. You don't need to understand them, but if you
// want to they're explained at http://www.jera.com/techinfo/jtns/jtn002.html
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++;     \
    if (message) return message; } while (0)
int tests_run;

// Here are some unit tests which demonstrate how to use the hello function, and
// automatically check whether it's behaving as it should. The code which runs
// the tests is at the bottom of this file.
char* test_hello() {
  char* greeting;
  int   result;

  // hello produces a greeting when given a name
  greeting = hello("Bob");
  result   = !strcmp(greeting, "Hello Bob!"); // result = 1 for equal strings

  free(greeting);  // Free before asserting so it's freed even if the test fails
  mu_assert("hello didn't greet correctly", result);  // Fails if result = 0

  // hello will work for any name
  greeting = hello("Jo");
  result   = !strcmp(greeting, "Hello Jo!");

  free(greeting);
  mu_assert("Didn't greet 'Jo' correctly", result);

  // An empty string is an edge case, but it still works
  greeting = hello("");
  result   = !strcmp(greeting, "Hello !");

  free(greeting);
  mu_assert("Empty string wasn't greeted", result);

  // At this point, our tests have passed, which we indicate by returning 0
  return 0;
}

// Now that we know how to debug with printf, and use test suites to check and
// document our code, we can begin the exercises.

// Fill in the definitions of the following functions and test suites, where one
// implementation uses an iterative algorithm and the other uses a recursive
// algorithm.

// Here is an example to get you started: adding two non-negative numbers
// together by incrementing one and decrementing the other.

int  rec_add(int x, int y) {
  return (x == 0)? y
                 : rec_add(x-1, y+1);
}

int iter_add(int x, int y) {
  while (x > 0) {
    x = x-1;
    y = y+1;
  }
  return y;
}

char* test_add() {
  // Check a few values to make sure they're added together
  mu_assert( "rec_add should add",  rec_add(5, 7) == 12);
  mu_assert("iter_add should add", iter_add(5, 7) == 12);

  // Check some edge cases
  mu_assert( "rec_add handles 0 first" ,  rec_add(0, 10) == 10);
  mu_assert( "rec_add handles 0 second",  rec_add(0, 10) == 10);
  mu_assert("iter_add handles 0 first" , iter_add(10, 0) == 10);
  mu_assert("iter_add handles 0 second", iter_add(10, 0) == 10);

  // Check that some general properties hold for whole bunch of inputs
  for (int x = 0; x < 100; ++x) {
    mu_assert( "rec_add left  identity",  rec_add(0, x) == x);
    mu_assert( "rec_add right identity",  rec_add(x, 0) == x);
    mu_assert("iter_add left  identity", iter_add(0, x) == x);
    mu_assert("iter_add right identity", iter_add(x, 0) == x);
    for (int y = 0; y < 100; ++y) {
      mu_assert( "rec_add matches +",        rec_add(x, y) == x + y);
      mu_assert( "rec_add matches iter_add", rec_add(x, y) == iter_add(x, y));
      mu_assert( "rec_add commutative",      rec_add(x, y) ==  rec_add(y, x));
      mu_assert("iter_add commutative",     iter_add(x, y) == iter_add(y, x));
    }
  }
  return 0; // passed
}

// Factorial function: f(x) = x!. Be careful testing this, as the output gets
// very big and might overflow!

int    rec_factorial(int x) {}

int   iter_factorial(int x) {}

char* test_factorial() {
  return "Replace this with your factorial tests";
}

// Exponential function: f(c, n) = c^n, for any constant c.

int    rec_exponential(int x, int y) {}

int   iter_exponential(int x, int y) {}

char* test_exponential() {
  return "Replace this with your exponential tests";
}

// Euclidean greatest common divisor algorithm.

int    rec_gcd(int x, int y) {}

int   iter_gcd(int x, int y) {}

char* test_gcd() {
  return "Replace this with your gcd tests";
}

// Find all odd numbers from 0 to n.

int    rec_odds(int x, int y) {}

int   iter_odds(int x, int y) {}

char* test_odds() {
  return "Replace this with your odds tests";
}

// Compute the sum of n elements in an array a

int    rec_sum(int x, int y) {}

int   iter_sum(int x, int y) {}

char* test_sum() {
  return "Replace this with your sum tests";
}

// This will run all of the tests, one after another
char* all_tests() {
  mu_run_test(test_hello      );
  mu_run_test(test_add        );
  mu_run_test(test_factorial  );
  mu_run_test(test_exponential);
  mu_run_test(test_gcd        );
  mu_run_test(test_odds       );
  mu_run_test(test_sum        );
  return 0;
}

int main() {
  char* result = all_tests();
  if (result != 0) {
    printf("%s\n", result);
  }
  else {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
