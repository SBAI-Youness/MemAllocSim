# MemAllocSim

Memory Allocation Algorithm Simulator in C

## Description
This project implements several memory allocation algorithms:
- Contiguous allocation
- Paged allocation
- Segmented allocation
- Segmented paged allocation

The simulator allows you to visualize and compare the performance of different memory allocation algorithms in a controlled environment.

## Project Structure
```
MemAllocSim/
├── build/           # Compiled files
├── docs/            # Project documentation
├── include/         # Header files (.h)
├── source/          # Source code (.c)
├── test/            # Unit tests
├── Makefile         # Build file
├── LICENSE          # MIT License
└── README.md        # Main documentation
```

## Prerequisites
- GCC (GNU Compiler Collection)
- Make
- Git (for cloning)

## Installation
To get started with the project, clone this repository to your local machine:

```shell
git clone https://github.com/SBAI-Youness/MemAllocSim.git
cd MemAllocSim
```

## Compilation
To compile the project, simply run the following command from the root directory:
```shell
make
```

## Usage
After building the project, you can run the simulator as follows:

1. Navigate to the `build/` directory:
   ```shell
   cd build
   ```
2. Run the simulator:
   ```shell
   ./memallocsim
   ```

### Configuration Options
The simulator accepts several command-line parameters:
- `-h` : Display help
- `-a <algorithm>` : Specify the algorithm to use
- `-m <size>` : Set memory size
- `-p <size>` : Set page size (for paged algorithms)

## Tests
To run the unit tests:
```bash
make test
```

## Documentation
Detailed documentation is available in the `docs/` directory.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Feel free to open an issue or submit a pull request.
