# 🐍 Snake and Ladder Game (OOP – Console Based)

This project is a **console-based Snake and Ladder game** developed in **C++** using **Object-Oriented Programming (OOP)** principles.  
It supports **single-player (Player vs Computer)** and **two-player** modes with dynamic snakes and ladders, dice mechanics, colored output, and game history saving.
---

## 🎮 Game Features

✔ Single-player mode (Play against Computer)  
✔ Two-player mode (Human vs Human)  
✔ Dynamic winning position (user-defined, ≥ 50)  
✔ Random dice rolling using two dice  
✔ Extra turn when both dice have the same value  
✔ Automatically generated snakes and ladders  
✔ Snake bite & ladder boost logic  
✔ Colored console output for better user experience  
✔ Keyboard-controlled turns (Enter / Space bar)  
✔ Game result saved to a file (`Game_history.txt`)  

---

## 🧠 OOP Concepts Implemented

This project clearly demonstrates the use of core **Object-Oriented Programming concepts**:

- **Classes & Objects**  
  - `player`, `board`, `Game`
- **Encapsulation**  
  - Game logic is encapsulated inside classes
- **Constructors & Destructors**  
  - Dynamic memory allocation and cleanup
- **Abstraction**  
  - Separate responsibilities for board, player, and game flow
- **Dynamic Memory Allocation**  
  - Snakes and ladders generated using dynamic arrays
- **Modular Design**  
  - Well-structured methods for game control

---

## 🛠️ Technologies & Libraries Used

- **Language:** C++  
- **Paradigm:** Object-Oriented Programming  
- **Libraries Used:**
  - `<iostream>`
  - `<ctime>`
  - `<fstream>`
  - `<conio.h>`
  - `<thread>`
  - `<chrono>`
  - `<algorithm>`

---

## 🎯 Game Rules (As Implemented)

- Both players start at position **0**
- Player rolls **two dice**
- If both dice have the same value → **extra turn**
- Landing on:
  - 🐍 **Snake head** → player moves down
  - 🪜 **Ladder bottom** → player moves up
- If position exceeds winning square → position is adjusted
- First player to reach the **winning position** wins

---

## ⌨️ Controls

- **Player 1:** Press **ENTER** to roll dice  
- **Player 2:** Press **SPACE BAR** to roll dice  
- **Computer:** Rolls automatically  

---

File Handling in the Game

Description:
This game uses file handling to save the results of each match automatically.
How it Works:
After a game ends, the program writes the results to a file called Game_history.txt.
Implemented using ofstream in C++.
The file stores the following information:
Winning position
Player names
Winner and loser
Snake and ladder positions


