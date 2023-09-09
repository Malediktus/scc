# Simple C Compiler (SCC)
## Overview

SCC (Simple C Compiler) is a C11 compiler written in C, designed to provide a minimalistic and easy-to-understand implementation of a C compiler. It aims to be a learning resource for those interested in understanding the basics of compiler design and implementation.

## Features

- Supports a most of the C11 standard.
- Generates x86_64 assembly code.
- Minimalistic codebase for educational purposes.
- Built using autotools for easy compilation and installation.

## Getting Started

These instructions will help you get a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites

To build and run SCC, you'll need:

- [GCC](https://gcc.gnu.org/) or a compatible C compiler.
- [Autotools](https://www.gnu.org/software/automake/) for building the project.

## Building SCC

1. Clone this repository:

   ```bash
   git clone https://github.com/yourusername/scc.git
   ```

2. Run autotools (not required for packaged releases):

   ```bash
   autoreconf -vi
   ```

3. Run the configure script:

   ```bash
   ./configure
   ```

4. Build the project:

   ```bash
   make
   ```

## Usage

After successfully building SCC, you can use it to compile C programs:

```bash
./scc source.c -o output
```

## Example

Here's a simple example of using SCC to compile a C program:

```c
// hello.c
#include <stdio.h>

int main() {
  printf("Hello, World!\n");
  return 0;
}
```

Compile it using SCC:

```bash
./scc hello.c -o hello
```

Run the compiled executable:

```bash
./hello
```

This should output:

```
Hello, World!
```

## Authors

- Nico Grundei (malediktusrgb@gmail.com)

## License

This project is licensed under the [GNU General Public License (GPL) version 3](LICENSE). Please see the [LICENSE](LICENSE) file for the full text of the license.