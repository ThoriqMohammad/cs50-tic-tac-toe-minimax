# Tic-Tac-Toe with Minimax Algorithm – CS50 Final Project
#### Video Demo:  <https://youtu.be/your-video-id>
#### Description:
This project is a command-line implementation of the classic Tic‑Tac‑Toe game where you play against an **unbeatable computer opponent**. The computer uses the **minimax algorithm** to play optimally – you can never win, only draw or lose. The game is written entirely in C and features a clean, interactive interface.

**Key Features:**
- **Human vs. Computer** – You play as `'X'`, the computer as `'O'`.
- **Random First Player** – Each game randomly chooses whether you or the computer starts, adding variety.
- **Replay Loop with Score Tracking** – After each game, the program displays updated scores (human wins, computer wins, draws) and asks if you want to play again. Scores accumulate until you quit.
- **Minimax Algorithm** – The computer evaluates all possible future moves to select the best one, guaranteeing perfect play.
- **Clear Instructions** – The board is numbered 1–9, making move entry intuitive.

**How to Compile and Run:**
- Compile with any C compiler, e.g., `gcc -o tictactoe tictactoe.c`
- Run with `./tictactoe`

**Code Structure:**
- `main()` – Handles the replay loop, random starter selection, and scorekeeping.
- `playTicTacToe()` – Manages a single round, alternating turns between human and computer.
- `minimax()` – Recursive function that evaluates board positions.
- `bestMoveForMinimizer()` – Chooses the optimal move for the computer (as the minimizing player).
- Helper functions for displaying the board, checking wins, and input validation.

**Acknowledgments and Modifications:**
This project is based on the **Tic Tac Toe Game in C** article from [GeeksforGeeks](https://www.geeksforgeeks.org/c/tic-tac-toe-game-in-c/). The original code provided the minimax foundation and basic game structure. However, I have made **significant modifications** to create a unique submission for CS50:

1. **Random First Player** – The original always had the computer start; now the starter is chosen randomly each game.
2. **Replay Loop and Scoring** – Added persistent score tracking and the ability to play multiple rounds.
3. **Corrected Minimax for Computer as `'O'`** – The original `findBestMove()` only worked for the maximizer. I added `bestMoveForMinimizer()` so the computer correctly minimises the score.
4. **Code Cleanup** – Removed unused variables and improved comments for clarity.
5. **Enhanced Input Validation** – Handles invalid entries gracefully.

All new code and modifications are my own work and are clearly commented. This project demonstrates a solid understanding of recursion, game trees, and algorithmic decision‑making.
