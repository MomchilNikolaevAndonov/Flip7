# Flip7_NN

A C++ prototype that simulates rounds of a Flip 7-style card game and uses a small neural network to choose whether each of four players should keep drawing or end their turn.

## Features

- Builds a deck with one zero card and one copy of each card value from 1 through 13.
- Simulates four players, scoring non-busted rounds until a player reaches 200 points.
- Feeds players' card counts to a neural network with a `14 -> 14 -> 7 -> 1` layer layout.
- Applies random mutations to network weights and biases.
- Runs 100 games and prints per-turn information and final scores to the console.

## Prerequisites

- CMake 3.20 or newer
- A C++ compiler with C++14 support

## Build and run

Run these commands from the repository root.

### Windows

Configure and build:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

With the default Visual Studio generator, run:

```powershell
.\build\Release\Flip7_NN.exe
```

With a single-configuration generator such as Ninja, run:

```powershell
.\build\Flip7_NN.exe
```

### Linux and macOS

```sh
cmake -S . -B build
cmake --build build --parallel
./build/Flip7_NN
```

The program writes detailed simulation output to the console and completes after 100 games.

## Project structure

| Path | Purpose |
| --- | --- |
| `CMakeLists.txt` | Defines the CMake project, C++ standard, and `Flip7_NN` executable |
| `files/Flip7.cpp` | Simulation entry point, turn flow, and neural-network inputs |
| `files/Players.cpp` | Player state, scoring, bust checks, and network mutation |
| `files/Game.cpp` | Deck creation, reshuffling, and game-ending condition |
| `files/header.h` | `Players` and `Game` declarations |
| `files/neural_network.h` | Neural-network declarations and configuration |
| `files/neural_network.cpp` | Neural-network forward pass and mutation implementation |

## Status

This is an experimental console prototype, not a complete user-facing game. The number of players, score target, and number of games are fixed in the source; decisions are made by the neural network, and the current run does not provide interactive player controls or save trained networks.
