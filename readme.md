# Ford-Fulkerson Algorithm for Maximum Flow

This repository contains a C implementation of the Ford-Fulkerson algorithm for finding the maximum flow in a network.

## Overview

The Ford-Fulkerson algorithm is a method for finding the maximum flow in a network (directed graph) with capacities assigned to its edges. The algorithm iteratively finds augmenting paths from the source to the sink, updating the flow in the network until no more augmenting paths can be found.

## Usage

1. **Compilation:**

   - Compile the code using a C compiler (e.g., GCC).
     ```bash
     gcc ford_fulkerson.c -o ford_fulkerson
     ```

2. **Execution:**

   - Run the compiled executable, providing the input as necessary.
     ```bash
     ./ford_fulkerson
     ```

3. **Input:**
   - The network and its capacities are defined in the `red` matrix in the code.
   - Modify the `fuente` (source) and `sumidero` (sink) variables in the `main` function as needed.

## Important Notes

- The algorithm assumes non-negative capacities on edges. If negative capacities are present, the algorithm may not work correctly.
- The `red` matrix represents the adjacency matrix with edge capacities.

## Contributing

Feel free to contribute to enhance the algorithm or provide improvements. Open issues and submit pull requests to collaborate.

## License

This code is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
