# SFML Minesweeper

A GUI-based implementation of the classic puzzle game Minesweeper, built in C++ using SFML (Simple and Fast Multimedia Library).

<img width="450" alt="Minesweeper Demo Gif" src="https://github.com/user-attachments/assets/8cc16414-01b2-4ba1-9b0c-6a54d970c2c6" />

## Features

- **Flood-fill reveal:** clicking an empty tile cascades to reveal all connected safe tiles
- **Flagging system:** right-click to flag/unflag suspected mines, with a live counter showing mines remaining
- **Game State Management:** clicking a mine ends the game and reveals the full board; clearing all safe tiles wins
- **Configurable board setup:** board dimensions and mine count are read from configuration data and used to dynamically render the grid, rather than hardcoding a fixed layout
- **Randomized board:** mine layout is shuffled every game
- **Reset button:** the smiley face resets the board and tracks game state (happy / win / lose)
- **Debug tools:** built-in buttons to reveal all mines or load preset board layouts, for faster manual testing during development

## Built With

- **C++11** (or higher)
- **SFML 2.5.1** (rendering, input, and window management)
- **Visual Studio**

## Architecture

Built with an object-oriented design in C++, separating game logic, rendering, and resource management across dedicated classes:
- `Board`: manages the grid of tiles, mine placement, reveal/flag logic, and win/loss conditions
- `Tile`: represents a single cell's state (mine, flagged, revealed, adjacent mine count) and rendering
- `Buttons`: UI buttons including the reset face and debug tools
- `Counter`: tracks and displays the remaining mine count
- `TextureManager`: handles loading and sharing of sprite textures

## Getting Started

### Prerequisites
Download and extract [SFML 2.5.1 for Visual C++](https://www.sfml-dev.org/download/sfml/2.5.1/).

### Installation

1. Clone the repo
```bash
   git clone https://github.com/mathews526/sfml-minesweeper.git
```
2. **Open the project:**
   Open `SFML-Minesweeper.sln` in Visual Studio.
3. **Configure SFML Paths:**
   Right-click the project in **Solution Explorer** and select **Properties**:
   - **C/C++ > General > Additional Include Directories**: Add the path to your SFML `include/` folder (e.g., `C:\SFML-2.5.1\include`).
   - **Linker > General > Additional Library Directories**: Add the path to your SFML `lib/` folder (e.g., `C:\SFML-2.5.1\lib`).
4. **Build & Run:**
   Select your build configuration (**Debug** or **Release**) and build the project (`F5`).

> **Note on Static Linking:** This project links SFML statically (`SFML_STATIC`). The library code is compiled directly into the executable using static libraries (`sfml-*-s.lib`) and native Windows dependencies (`opengl32.lib`, `winmm.lib`, `gdi32.lib`). **No SFML `.dll` files are required in the output folder to run the application.**

## License
Distributed under the MIT License. See [LICENSE](./LICENSE) for more information.
