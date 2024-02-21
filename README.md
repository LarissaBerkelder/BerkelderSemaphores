# Roller Coaster Queue Simulator

This project simulates the queue system of the Baron 1898 roller coaster at Efteling theme park, focusing on efficient loading of carts with groups and single riders using semaphore synchronization.

## Overview

The simulation models the behavior of groups and single riders queuing to ride the Baron 1898 coaster. It implements semaphores for synchronization to manage the roller coaster's cart loading process efficiently, ensuring that groups can sit together and single seats are filled whenever possible.

## Getting Started

### Prerequisites

- CMake version 3.22 or higher
- A C compiler (GCC recommended)
- pthread library for threading support


### Building the Project
1. Clone the repository to your local machine (adjust the command with the actual repository URL):

    ```bash
    git clone 
    ```

2. Navigate to the project directory:

    ```bash
    cd BerkelderSemaphore
    ```

3. Create a `build` directory and navigate into it:

    ```bash
    mkdir build && cd build
    ```

4. Run CMake to configure the project:

    ```bash
    cmake ..
    ```

5. Build the project:

    ```bash
    make
    ```

### Running the Simulation

After building, you can run the executable generated in the `build` directory:

```bash
./BerkelderSemaphore 
```


### Project Structure
- src/: Contains the source files for the simulation.
- inc/: Contains the header files for the simulation.
- CMakeLists.txt: CMake configuration file to build the project.