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

## How to Run

1. Clone the repo
2. Open the project in Visual Studio
3. Make sure SFML is linked (see [SFML setup docs](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) if needed)
4. Build and run

## License
Distributed under the MIT License. See [LICENSE](./LICENSE) for more information.
