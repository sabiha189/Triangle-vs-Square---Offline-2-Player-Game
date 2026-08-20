# Triangle vs Square - Offline 2 Player Game

A simple **offline 2D two-player game** developed using **C++ and OpenGL (GLUT)**.

In this game, two players compete on the same computer. One player controls a gray square using the keyboard, while the other player controls an orange triangle using the mouse.

## Game Features

- Offline 2-player gameplay
- Two players on the same computer
- 2D graphics using OpenGL
- Keyboard-controlled square
- Mouse-controlled triangle
- Square rotation
- Triangle teleportation through mouse clicks
- Collision detection
- 30-second game timer
- Winner and draw system
- Game restart option

## Players

### Player 1 - Gray Square

The gray square is controlled by the keyboard.

| Key | Action |
|-----|--------|
| W | Move Up |
| A | Move Left |
| S | Move Down |
| D | Move Right |
| F | Rotate Anti-clockwise |
| G | Rotate Clockwise |
| R | Restart Game |

### Player 2 - Orange Triangle

The orange triangle is controlled using the mouse.

| Mouse Control | Action |
|---------------|--------|
| Left Click | Teleport Triangle to the clicked position |

## Game Rules

1. The game is played offline by two players on the same computer.
2. Player 1 controls the gray square using the keyboard.
3. Player 2 controls the orange triangle using the mouse.
4. The triangle teleports to the position where Player 2 clicks.
5. If the triangle touches the square, the **Triangle Player wins**.
6. If the square touches the triangle, the **Square Player wins**.
7. Players have **30 seconds** to catch each other.
8. If neither player catches the other within 30 seconds, the game ends in a **Draw**.
9. Press `R` to restart the game.

## Technologies Used

- C++
- OpenGL
- GLUT (OpenGL Utility Toolkit)
- Code::Blocks

## Project Structure

```text
Triangle-vs-Square/
│
├── main.cpp
├── pair project.cbp
└── README.md
