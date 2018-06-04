# Instructions
In order to build the project, open the terminal in the root directory and do as
follows:

``` shell
mkdir build && cd build
cmake ..
```

After that, you can:
``` shell
make # To compile everything
make tests # To compile only the tests
make main # To compile only the source, without tests
```

You can execute the tests with `./tests` and the game with `./main`.