#include <iostream>
#include <vector>
#include <stdexcept>











struct TicTacToe_Board
{
    std::vector<std::vector<int>> board = std::vector<std::vector<int>>(3, std::vector<int>(3, 0));
    int player1 = 1;
    int player2 = 2;
    int moves = 0;
    bool gameOver = false;
    int winner = 0;

    TicTacToe_Board() {}

    TicTacToe_Board(int player1, int player2)
    {
        this->player1 = player1;
        this->player2 = player2;
    }

    void play(int player, int row, int col)
    {
        if (gameOver)
        {
            throw std::invalid_argument("This board's game is already over.");
        }
        if (board[row][col] == 0)
        {
            board[row][col] = player;
            moves++;
        }
        if (checkWin(player, row, col))
        {
            gameOver = true;
            winner = player;
        }
        else if (moves == 9)
        {
            gameOver = true;
        }
    }

    bool checkWin(int player, int row, int col)
    {
        if (board[row][0] == player && board[row][1] == player && board[row][2] == player)
        {
            gameOver = true;
            return true;
        }
        if (board[0][col] == player && board[1][col] == player && board[2][col] == player)
        {
            gameOver = true;
            return true;
        }
        if (row == col)
        {
            if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            {
                gameOver = true;
                return true;
            }
        }
        if (row + col == 2)
        {
            if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            {
                gameOver = true;
                return true;
            }
        }
        return false;
    }

    void print()
    {
        std::cout << "[";
        for (int i = 0; i < 3; i++)
        {
            if (i != 0 && i != 3)
            {
                std::cout << std::endl;
            }
            std::cout << "[";
            for (int j = 0; j < 3; j++)
            {
                std::cout << board[i][j];
                if (j != 2)
                {
                    std::cout << ", ";
                }
                if (j == 2)
                {
                    std::cout << "]";
                }
            }
        }
        std::cout << "]" << std::endl;
    };

    void fill(int num)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = num;
            }
        }
    }

    int operator[](int index) const
    {
        if (index < 0 || index > 8)
        {
            throw std::invalid_argument("Invalid index");
        }
        return board[index / 3][index % 3];
    };

};

struct BIG_TicTacToe_Board
{
    std::vector<std::vector<TicTacToe_Board>> bigBoard = std::vector<std::vector<TicTacToe_Board>>(3, std::vector<TicTacToe_Board>(3));
    TicTacToe_Board simplifiedBoard;
    int player1 = 1;
    int player2 = 2;
    int moves = 0;
    bool gameOver = false;
    int winner = 0;

    BIG_TicTacToe_Board() {}

    BIG_TicTacToe_Board(int player1, int player2)
    {
        this->player1 = player1;
        this->player2 = player2;
    }

    int getBoardNumber(int row, int col)
    {
        return row * 3 + col + 1;
    }

    TicTacToe_Board getBoard(int row, int col)
    {
        if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            throw std::invalid_argument("Invalid row or column");
        }
        return bigBoard[row][col];
    }

    TicTacToe_Board& getBoard(int boardNumber)
    {
        if (boardNumber < 1 || boardNumber > 9)
        {
            throw std::invalid_argument("Invalid board number");
        }
        return bigBoard[(boardNumber - 1) / 3][(boardNumber - 1) % 3];
    }

    void playSimplified(int player, int row, int col)
    {
        simplifiedBoard.play(player, row, col);
    }

    void play(int player, int bigRow, int bigCol, int row, int col)
    {
        bigBoard[bigRow][bigCol].play(player, row, col);
        moves++;
    }

    bool isBigGameOver()
    {
        if (simplifiedBoard.gameOver)
        {
            return true;
        }
        return false;
    }

    bool checkBigWin(int player, int bigRow, int bigCol) // checks if the big board has been won
    {
        if (simplifiedBoard.checkWin(player, bigRow, bigCol))
        {
            return true;
        }
    }

    bool checkSmallWin(int player, int boardRow, int boardCol, int row, int col) // checks if a small board has been won
    {
        return bigBoard[boardRow][boardCol].checkWin(player, row, col);
    }

    void printSimplified()
    {
        simplifiedBoard.print();
    }

    void testFill() // fills boards 1-9 with numbers 1-9 for testing purposes
    {
        int value = 1;
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                bigBoard[i][j].fill(value);
                ++value;
            }
        }
    }

    void print(int boardRow, int boardCol) // prints a single board
    {
        bigBoard[boardRow][boardCol].print();
    };

    void print() // prints the entire big board (all 9 boards)
    {
        std::vector<TicTacToe_Board> boards = {
            getBoard(0, 0), getBoard(0, 1), getBoard(0, 2),
            getBoard(1, 0), getBoard(1, 1), getBoard(1, 2),
            getBoard(2, 0), getBoard(2, 1), getBoard(2, 2)
        };

        printAllBoards(boards);
    }

    void printAllBoards(std::vector<TicTacToe_Board> boards) // prints (up to) 9 boards
    {
        std::cout << "[" << std::endl;
        for (int row = 0; row < 9; ++row)
        {
            int boardRow = row % 3;
            int boardSet = row / 3;

            for (int i = 0; i < 3; ++i)
            {
                TicTacToe_Board board = boards[boardSet * 3 + i];
                std::cout << "  |" << board[boardRow * 3] << " " << board[boardRow * 3 + 1] << " " << board[boardRow * 3 + 2] << "|  ";
            }

            std::cout << std::endl;
            if (boardRow == 2 && row != 8)
            {
                std::cout << std::endl;
            }
        }
        std::cout << "]" << std::endl;
    }

    void updateSimplifiedBoard(int row, int col) // updates the simplified board
    {
        if (bigBoard[row][col].gameOver)
        {
            simplifiedBoard.play(bigBoard[row][col].winner, row, col);
        }
    }

    bool canPlay(int bigRow, int bigCol, int row, int col) // checks if a player can play in a small board
    {
        if (bigBoard[bigRow][bigCol].gameOver)
        {
            std::cout << "Board already over." << std::endl;
            return false;
        }
        if (bigBoard[bigRow][bigCol].board[row][col] == 0)
        {
            return true;
        }
        return false;
    }

    std::vector<int> getRowColFromBoardNumber(int boardNumber) // returns the row and column of a board given its number
    {
        std::vector<int> rowCol;
        rowCol.push_back((boardNumber - 1) / 3);
        rowCol.push_back((boardNumber - 1) % 3);
        return rowCol;
    }

    int chooseAdjacentBoard(int boardNumber)
    {
        int row = (boardNumber - 1) / 3;
        int col = (boardNumber - 1) % 3;
        std::vector<int> adjacentBoards = getAdjacentBoards(row, col);
        int choice;
        bool validChoice = false;
        std::cout << "The target board is over." << std::endl << "Opponent can choose an adjacent board to play in: ";
        for (int i = 0; i < adjacentBoards.size(); ++i)
        {
            std::cout << adjacentBoards[i] << " ";
        }
        std::cout << std::endl;
        while (validChoice == false)
        {
            std::cin >> choice;
            if (validChoice == false)
            {
                for (int i = 0; i < adjacentBoards.size(); ++i)
                {
                    if (choice == adjacentBoards[i])
                    {
                        validChoice = true;
                        return choice;
                    }
                }
            }
            if (validChoice == false)
            {
                std::cout << "Invalid choice. Choose an adjacent board to play in: ";
            }
        }
        return choice;
    }

    std::vector<int> getAdjacentBoards(int row, int col) // returns a vector of adjacent boards
    {
        std::vector<int> adjacentBoards;
        if (row == 0 && col == 0)
        {
            if (!bigBoard[0][1].gameOver)
            {
                adjacentBoards.push_back(2);
            }
            if (!bigBoard[1][0].gameOver)
            {
                adjacentBoards.push_back(4);
            }
        }
        if (row == 0 && col == 1)
        {
            if (!bigBoard[0][0].gameOver)
            {
                adjacentBoards.push_back(1);
            }
            if (!bigBoard[0][2].gameOver)
            {
                adjacentBoards.push_back(3);
            }
            if (!bigBoard[1][1].gameOver)
            {
                adjacentBoards.push_back(5);
            }
        }
        if (row == 0 && col == 2)
        {
            if (!bigBoard[0][1].gameOver)
            {
                adjacentBoards.push_back(2);
            }
            if (!bigBoard[1][2].gameOver)
            {
                adjacentBoards.push_back(6);
            }
        }
        if (row == 1 && col == 0)
        {
            if (!bigBoard[0][0].gameOver)
            {
                adjacentBoards.push_back(1);
            }
            if (!bigBoard[1][1].gameOver)
            {
                adjacentBoards.push_back(5);
            }
            if (!bigBoard[2][0].gameOver)
            {
                adjacentBoards.push_back(7);
            }
        }
        if (row == 1 && col == 1)
        {
            if (!bigBoard[0][1].gameOver)
            {
                adjacentBoards.push_back(2);
            }
            if (!bigBoard[1][0].gameOver)
            {
                adjacentBoards.push_back(4);
            }
            if (!bigBoard[1][2].gameOver)
            {
                adjacentBoards.push_back(6);
            }
            if (!bigBoard[2][1].gameOver)
            {
                adjacentBoards.push_back(8);
            }
        }
        if (row == 1 && col == 2)
        {
            if (!bigBoard[0][2].gameOver)
            {
                adjacentBoards.push_back(3);
            }
            if (!bigBoard[1][1].gameOver)
            {
                adjacentBoards.push_back(5);
            }
            if (!bigBoard[2][2].gameOver)
            {
                adjacentBoards.push_back(9);
            }
        }
        if (row == 2 && col == 0)
        {
            if (!bigBoard[1][0].gameOver)
            {
                adjacentBoards.push_back(4);
            }
            if (!bigBoard[2][1].gameOver)
            {
                adjacentBoards.push_back(8);
            }
        }
        if (row == 2 && col == 1)
        {
            if (!bigBoard[1][1].gameOver)
            {
                adjacentBoards.push_back(5);
            }
            if (!bigBoard[2][0].gameOver)
            {
                adjacentBoards.push_back(7);
            }
            if (!bigBoard[2][2].gameOver)
            {
                adjacentBoards.push_back(9);
            }
        }
        if (row == 2 && col == 2)
        {
            if (!bigBoard[1][2].gameOver)
            {
                adjacentBoards.push_back(6);
            }
            if (!bigBoard[2][1].gameOver)
            {
                adjacentBoards.push_back(8);
            }
        }
        return adjacentBoards;
    }

};

struct Human
{
    int player;
    std::string name;

    Human(int player, std::string name)
    {
        this->player = player;
        this->name = name;
    }

    int chooseBoard()
    {
        int boardNumber;
        std::cout << name << ", enter a board number (1 to 9): ";
        std::cin >> boardNumber;
        return boardNumber;
    }

    void play(TicTacToe_Board &board)
    {
        int row, col;
        std::cout << name << ", enter the row, then column you would like to play in: ";
        std::cin >> row >> col;
        board.play(player, row, col);
    }

    int play(BIG_TicTacToe_Board &bigBoard, int bigRow, int bigCol)
    {
        int row, col;
        int boardNumber = bigBoard.getBoardNumber(bigRow, bigCol);
        bool canPlay;

        std::cout << name << ", you are playing in board " << boardNumber << std::endl;
        
        row = -1;
        col = -1;
        canPlay = false;

        while (!canPlay){
            while (row < 1 or row > 3){
                std::cout << "Row: ";
                std::cin >> row;
                if (row < 1 or row > 3){
                    std::cout << "Rows go from 1 to 3" << std::endl;
                }
            }
            while (col < 1 or col > 3){
                std::cout << "Col: ";
                std::cin >> col;
                if (col < 1 or col > 3){
                    std::cout << "Columns go from 1 to 3" << std::endl;
                }
            }
            if (bigBoard.canPlay(bigRow, bigCol, row-1, col-1)){
                canPlay = true;
            } else {
                canPlay = false;
                row = -1;
                col = -1;
                std::cout << "Invalid move, try again." << std::endl;
            }
        }

        boardNumber = bigBoard.getBoardNumber(row-1, col-1);
        return boardNumber; // returns the coordinates of the move
    }

    int chooseValidBoard(){
        int boardNumber = -1;
        while (boardNumber < 1 || boardNumber > 9) {
            std::cout << name << " chooses where the opponent will play." << std::endl;
            boardNumber = chooseBoard();
            if (boardNumber < 1 || boardNumber > 9) {
                std::cout << "Invalid board number, try again." << std::endl;
            }
        }
        return boardNumber;
    }

};

// Function to play a turn
int playTurn(Human& player, int currentBoardNumber, BIG_TicTacToe_Board& bigBoard) {
    int oldBoardNumber = currentBoardNumber;
    currentBoardNumber = player.play(bigBoard, (currentBoardNumber - 1) / 3, (currentBoardNumber - 1) % 3);
    bigBoard.play(player.player, (oldBoardNumber - 1) / 3, (oldBoardNumber - 1) % 3, (currentBoardNumber - 1) / 3, (currentBoardNumber - 1) % 3);
    return currentBoardNumber;
}

// Function to check for events and update the board
bool checkAndUpdateBoard(Human& player, int oldBoardNumber, int currentBoardNumber, BIG_TicTacToe_Board& bigBoard) {
    if (bigBoard.checkSmallWin(player.player, (oldBoardNumber - 1) / 3, (oldBoardNumber - 1) % 3, (currentBoardNumber - 1) / 3, (currentBoardNumber - 1) % 3)) {
        std::cout << "Board " << oldBoardNumber << " has been won by " << player.name << std::endl;
        bigBoard.updateSimplifiedBoard((oldBoardNumber - 1) / 3, (oldBoardNumber - 1) % 3);
    }
    if (bigBoard.getBoard((currentBoardNumber - 1) / 3, (currentBoardNumber - 1) % 3).gameOver) {
        currentBoardNumber = bigBoard.chooseAdjacentBoard(currentBoardNumber);
    }
    bigBoard.print();
    return bigBoard.isBigGameOver();
}

void game(Human Human1, Human Human2) {
    BIG_TicTacToe_Board bigBoard;
    TicTacToe_Board currentBoard;
    int currentBoardNumber, oldBoardNumber, bigRow, bigCol;

    std::cout << "Game starts, "<< Human1.name << " (Human) : " << Human1.player << " vs " << Human2.name << " (Human) : " << Human2.player << std::endl;
    bigBoard.print();

    currentBoardNumber = Human2.chooseValidBoard();

    while (true) {
        currentBoardNumber = playTurn(Human1, currentBoardNumber, bigBoard);
        if (checkAndUpdateBoard(Human1, currentBoardNumber, currentBoardNumber, bigBoard)) {
            break;
        }
        currentBoardNumber = playTurn(Human2, currentBoardNumber, bigBoard);
        if (checkAndUpdateBoard(Human2, currentBoardNumber, currentBoardNumber, bigBoard)) {
            break;
        }
    }
    std::cout << "Game over." << std::endl;
}

int main()
{
    Human Human1(1, "Player 1");
    Human Human2(2, "Player 2");

    game(Human1, Human2);
    

    return 0;
}
