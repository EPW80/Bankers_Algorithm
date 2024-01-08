# Bankers Algorithm

## Project Overview

Banker's Algorithm is designed to avoid deadlocks in systems where multiple processes request and hold resources. The algorithm functions like a bank loan system, where the operating system must selectively approve resource requests from processes to ensure all processes can run to completion without deadlocking.

## Running the project

- Ensure you have a C++ compiler installed (like g++).
- Compile the program. For example, if the main file is main.cpp, use the following command:

```bash
sudo g++ -o bankers bankers.cpp semaphore_layer.c -lpthread
```

- This will compile the program and create an executable named bankers.

## Execution

Run the program using the command:

```bash
./bankers

```

Provide input as required by the program, either through stdin or by redirecting input from a file, e.g.:

```bash
./bankers < data/bankers_tiny.txt
```

## data folder

Test the program with various provided data files (e.g., data/bankers_tinier.txt, data/bankers_tiny.txt, data/bankers_small.txt, etc.).

## Demo

<div>
    <a href="https://www.loom.com/share/070ac790116847569222d7a06050ef44">
      <p></p>
    </a>
    <a href="https://www.loom.com/share/070ac790116847569222d7a06050ef44">
      <img style="max-width:300px;" src="https://cdn.loom.com/sessions/thumbnails/070ac790116847569222d7a06050ef44-with-play.gif">
    </a>
</div>

## Contributor

Erik Williams
