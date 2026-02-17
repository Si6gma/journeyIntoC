<!--
Suggested GitHub Topics:
c, learning, data-structures, algorithms, state-machine, linked-list, interview-prep, systems-programming, memory-management, educational
-->

# journeyIntoC

> A personal learning journey through the fundamentals and complexities of C programming.

## What It Is

This repository documents my hands-on exploration of C programming concepts, from basic state machine implementations to advanced data structures. It serves as a practical playground for understanding memory management, pointers, and systems-level programming.

The project contains two main components:
- **Interactive State Machine Simulator** (`prog/`): A console-based simulation of a connected entertainment/shopping box system with user state management
- **Data Structures Practice** (`dsA/`): Implementations of fundamental data structures including linked lists and alphabetized dictionaries

## Why It Exists

I created this repository to:
- Deepen my understanding of low-level programming concepts
- Practice manual memory management without garbage collection safety nets
- Build intuition for pointers, structs, and dynamic allocation
- Document my learning progression in a tangible, reviewable format

C programming can be challenging - the segfaults, memory leaks, and pointer arithmetic can feel overwhelming. This repository captures that learning journey, from early struggles to working implementations.

## Tech Stack

- **Language**: C (C99/C11)
- **Compiler**: GCC / Clang
- **Tools**: PlantUML (for state diagrams), VS Code

## Project Structure

```
journeyIntoC/
├── prog/                  # State machine simulation
│   ├── main.c            # Main interactive program with menu system
│   ├── code.c            # Type definitions and design notes
│   └── main.puml         # State machine diagram (PlantUML)
├── dsA/                   # Data structures & algorithms practice
│   ├── linkedlist.c      # Complete singly linked list implementation
│   └── dictionary.c      # Alphabet-indexed dictionary using linked lists
├── out/                   # Build output directory
└── README.md             # This file
```

## How to Build & Run

### Prerequisites
- C compiler (gcc or clang)
- Make (optional)

### Building

```bash
# Build the state machine simulator
cd prog
gcc -o main main.c -Wall -Wextra -std=c11

# Build linked list example
cd dsA
gcc -o linkedlist linkedlist.c -Wall -Wextra -std=c11

# Build dictionary example
gcc -o dictionary dictionary.c -Wall -Wextra -std=c11
```

### Running

```bash
# Run the state machine simulator
./prog/main

# Run data structure examples
./dsA/linkedlist
./dsA/dictionary
```

## Key Learnings

### State Machine Design
- Implemented hierarchical state machines for device/user state management
- Used enums to define clear, type-safe state representations
- Separated concerns with modular menu functions

### Data Structures
- **Linked Lists**: Insertion, deletion, reversal, sorting, merging operations
- **Dictionary**: Multi-level structure using alphabet nodes with word lists
- Pointer manipulation for node traversal and modification

### Memory Management
- Dynamic allocation with `malloc()` / `calloc()`
- Proper cleanup with `free()` to prevent memory leaks
- Edge case handling for allocation failures
- Safe pointer null-checks before dereferencing

### Best Practices Applied
- Defensive programming with comprehensive edge case handling
- Cross-platform compatibility (clear screen for Windows/Unix)
- Modular function design with single responsibilities
- Comment documentation for complex logic

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

*This repository represents an ongoing learning journey. Code quality and completeness vary as it documents progression from early experiments to more polished implementations.*
