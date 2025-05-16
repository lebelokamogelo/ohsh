# OHSH - Oh SHell

A simple Unix-like shell implementation in C.

## Features

- Interactive command line interface
- Executes external commands
- Built-in commands:
  - `help` - Display help information
  - `exit` - Exit the shell
- Command parsing and argument handling
- Child process management

## Building

To compile the shell:

```bash
make
```

This will compile the source files from the `src` directory and place the executable in the `build` directory.

To run the shell:

```bash
make run
```

Or run it directly:

```bash
./build/ohsh
```

### Example Commands

```bash
$ ls -l
$ pwd
$ echo "Hello, World!"
$ help
$ exit
```

## Project Structure

- `src/` - Source code directory
- `build/` - Build output directory
- `README.md` - This documentation file

## Requirements

- Make build system
- GCC compiler
- Unix-like operating system (Linux, macOS, or WSL on Windows)

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to submit issues and pull requests to improve the shell.
