Lab 1 Programming
=================

The main purpose of this lab is to make sure everyone has a working setup and
is able to write C code relatively comfortably. It is recommended to use a Linux
machine, either in the labs or on your own machine (this could be in a virtual
machine like [VirtualBox](https://www.virtualbox.org)).

You will need:

 - GCC, the GNU Compiler Collection
 - Git
 - A text editor, such as Emacs or Kate
 - A terminal (if you're using Emacs, it has several built in)

1. Obtain a copy of this repository according to the following instructions.
    - In a terminal window, clone the git repository to your local machine and
        open *lab01* directory:

        ```sh
        $ git clone https://github.com/Warbo/aai-2016-17.git
        $ cd aai-2016-17/lab01
        ```

    - If you are not familiar with the Git version control system and want to
      know more, see the Git Book (https://git-scm.com/book)

2. Use GCC to compile the given code to a standalone executable according to the
   following instructions.

   - Open file *Main.c* in a text editor and read along.
   - Compile it in the terminal with:

        ```sh
        $ gcc -o Main Main.c
        ```

   - You can then run the executable from the terminal (`./Main` on Unix/Linux
     systems, `Main.exe` on Windows). By default, it should tell you that
     the exercises haven't been completed yet!

        ```sh
        $ ./Main
        Replace this with your tests
        Tests run: 3
        ```

3. Read through `Main.c` to see how it works. If you get stuck with anything or
   want to know more, just ask for help.

    - Try changing the `hello` function so that it says "Goodbye" instead of
      "Hello". If you have problems, you may want to use a `main` function and
      `printf` to see what the code is doing.

    - Make sure the original `main` function is in place at the bottom of the
      file, then re-compile and re-run the program. You can do this with one
      command like this:

        ```
        $ gcc Main.c -o Main && ./Main
        ```

    - The test suite should have spotted your misbehaving `hello` function! Read
      through the `test_hello` function in `Main.c` to see how it checks the
      `hello` function (you don't need to understand the `mu_assert` or
      `mu_run_test` macros).

    - Put back the original definition of `hello`. Now you can start writing
      your own definitions.

4. There are a few functions and test suites which have no implementation. Write
   implementations for the functions `myAnd`, `myOr`, `myImply`, and `myXor`,
   and come up with some test suites for them, based on the description in the
   associated comment. You may find it easier to write the tests first based on
   the comment, then write the function based on the tests!

5. Implement a function that converts boolean value to their string
   representation. A test suite is provided.
