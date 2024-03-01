# trimtrain

`trimtrain` is a Unix command-line utility written in C++ designed to normalize input columns of data, converting multiple spaces or tabs into a single space separator. This tool is useful for data scientists, developers, or anyone working with text files that require uniform spacing for proper alignment for further processing.

`trimtrain` is designed to be chained in pipelines with other unix tools

## Table of Contents

- [Installing](#installing)
- [Building](#building)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Installing

Before building `trimtrain`, ensure you have a C++ compiler (such as g++) and `cmake` installed on your system.

Clone the `trimtrain` repository from GitHub:

```sh
git clone https://github.com/jac18281828/trimtrain.git
cd trimtrain
```

## Building

`trimtrain` uses a Makefile for easy compilation. To build the program, navigate to the cloned directory and use the `make` command:

```sh
mkdir -p build
cmake -H. -Bbuild -DPROJECT_NAME=trimtrain -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE=on -Wno-dev "-GUnix Makefiles"
make -j
```

This will compile the source code into an executable named `trimtrain`. To install `trimtrain` into your system's standard executable path, use:

```sh
sudo make install
```

## Usage

After installation, you can run `trimtrain` by piping input into it or specifying an input file. Here are some examples:

To normalize a file and output to standard output:

```sh
trimtrain < inputfile.txt
```

To normalize a file and save the output to another file:

```sh
trimtrain < inputfile.txt > outputfile.txt
```

## Contributing

Contributions to `trimtrain` are welcome! Here are some ways you can contribute:

- Reporting bugs
- Suggesting enhancements
- Adding new features
- Improving documentation

## License

`trimtrain` is released under the BSD-3-Clause [LICENSE](https://github.com/jac18281828/trimtrain/LICENSE)
