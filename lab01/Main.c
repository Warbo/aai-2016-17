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
// written, and the output may have to be read by a person to figure out if
// anything went wrong or not.

// A much better approach is to define a "test suite", separate from the real
// code, where we can add all kinds of checks, and have them tested over and
// over automatically.

// Test suites can be large and complicated, but we'll just use these little
// macros to define and run tests. You don't need to understand them, but if you
// want to they're explained at http://www.jera.com/techinfo/jtns/jtn002.html
#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++;     \
    if (message) return message; } while (0)
int tests_run;

// Here are some unit tests which demonstrate how to use the hello function, and
// automatically check whether it's behaving as it should. The code which runs
// the tests is at the bottom of the file.
char* test_hello() {
  char* greeting;
  int   result;

  // hello produces a greeting when given a name
  greeting = hello("Bob");
  result   = !strcmp(greeting, "Hello Bob!");  // 1 if the strings are equal

  free(greeting);  // Free before asserting so it's freed even if the test fails
  mu_assert("Didn't greet 'Bob' correctly", result);  // Fails if result is 0

  // hello will work for any name
  greeting = hello("Jo");
  result   = !strcmp(greeting, "Hello Jo!");

  free(greeting);
  mu_assert("Didn't greet 'Jo' correctly", result);

  // An empty string is an edge case, but it still works
  greeting = hello("");
  result   = !strcmp(greeting, "Hello !");

  free(greeting);
  mu_assert("Empty string failed", result);

  // At this point, our tests have passed, which we indicate by returning 0
  return 0;
}

// Now that we know how to debug with printf, and use test suites to check and
// document our code, we can begin the exercises.

// We will be writing functions which use the following boolean type, of which
// there are two values: false and true. These values can be used with C's usual
// operations, like "if", "while", etc. and even in our unit tests (this is
// because they act like new names for the numbers 0 and 1)
typedef enum { false, true } boolean;

// Fill in the definitions of the following functions and test suites, using the
// boolean values we've defined above.

// Here is a definition to get you started: myAnd should return true only if
// both of the inputs are true.
boolean myAnd(boolean x, boolean y) {
  return x ? y : false;
}

char* test_myAnd() {
  // Straight from the specification written above
  mu_assert("myAnd gives true when required", myAnd(true, true));

  // The specification says "only", so we should make sure the other
  // possibilities don't return true
  mu_assert("myAnd(false, false)", !myAnd(false, false));
  mu_assert("myAnd(false,  true)", !myAnd(false,  true));
  mu_assert("myAnd( true, false)", !myAnd( true, false));

  return 0;
}

// myOr should return false only if both of the inputs are false.
boolean myOr(boolean x, boolean y) {}

// Check the behaviour of myOr using a test suite
char* test_myOr() {
  return "Replace this with your tests";
}

// myImply(x, y) should return false only if x is true and y is false. For the
// other cases it returns true.
boolean myImply(boolean x, boolean y) {}

char* test_myImply() {
  return "Replace this with your tests";
}

// myXor is called "exclusive disjunction" (AKA "exclusive or"). It is a logical
// operation that outputs true whenever both inputs differ (one is true, the
// other is false)
boolean myXor(boolean x, boolean y) {}

char* test_myXor() {
  return "Replace this with your tests";
}

// You may have noticed that printing boolean values makes numbers appear. To
// avoid this, define a function that converts a boolean value to its
// corresponding string, e.g. so boolToString(true) gives "true".
char* boolToString(boolean x) {}

char* test_boolToString() {
  mu_assert("Get string for true",  !strcmp(boolToString( true),  "true"));
  mu_assert("Get string for false", !strcmp(boolToString(false), "false"));
  return 0;
}

// Now we list all of the test suites, and define a "main" function which will
// run them all for us.
char* all_tests() {
  mu_run_test(test_hello       );
  mu_run_test(test_myAnd       );
  mu_run_test(test_myOr        );
  mu_run_test(test_myImply     );
  mu_run_test(test_myXor       );
  mu_run_test(test_boolToString);
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
