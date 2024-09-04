class Board:
    def __init__(self):
        self.board = [[' ' for _ in range(3)] for _ in range(3)]
        self.winner = None

    def make_move(self, row, col, player):
        if self.board[row][col] == ' ':
            self.board[row][col] = player
            if self.check_winner(player):
                self.winner = player
            return True
        return False

    def check_winner(self, player):
        # Check rows, columns, and diagonals
        for i in range(3):
            if all(self.board[i][j] == player for j in range(3)) or all(self.board[j][i] == player for j in range(3)):
                return True
        if self.board[0][0] == self.board[1][1] == self.board[2][2] == player or self.board[0][2] == self.board[1][1] == self.board[2][0] == player:
            return True
        return False

    def is_full(self):
        return all(self.board[row][col] != ' ' for row in range(3) for col in range(3))

    def __str__(self):
        # Grid lines
        line1 = ' | ' + self.board[0][0] + ' | ' + self.board[0][1] + ' | ' + self.board[0][2] + ' | ' + '\n' + '-' * 11
        line2 = ' | ' + self.board[1][0] + ' | ' + self.board[1][1] + ' | ' + self.board[1][2] + ' | ' + '\n' + '-' * 11
        line3 = ' | ' + self.board[2][0] + ' | ' + self.board[2][1] + ' | ' + self.board[2][2] + ' | ' + '\n' + '-' * 11
        return line1 + '\n' + line2 + '\n' + line3

class Game:
    def __init__(self):
        self.boards = [[Board() for _ in range(3)] for _ in range(3)]
        self.current_player = 'X'
        self.next_board = None

    def make_move(self, board_row, board_col, cell_row, cell_col):
        if self.next_board and (board_row, board_col) != self.next_board:
            print(f"Invalid move. You must play in board {self.next_board}.")
            return False

        if self.boards[board_row][board_col].make_move(cell_row, cell_col, self.current_player):
            if self.boards[board_row][board_col].winner:
                print(f"Player {self.current_player} wins board ({board_row}, {board_col})!")
            self.next_board = (cell_row, cell_col)
            self.current_player = 'O' if self.current_player == 'X' else 'X'
            return True
        return False

    def is_game_over(self):
        for row in range(3):
            for col in range(3):
                if self.boards[row][col].winner:
                    if self.check_winner(row, col):
                        return True
        return all(self.boards[row][col].is_full() for row in range(3) for col in range(3))

    def check_winner(self, row, col):
        player = self.boards[row][col].winner
        if player:
            # Check rows, columns, and diagonals on the big board
            for i in range(3):
                if all(self.boards[row][j].winner == player for j in range(3)) or all(self.boards[j][col].winner == player for j in range(3)):
                    return True
            if self.boards[0][0].winner == self.boards[1][1].winner == self.boards[2][2].winner == player or self.boards[0][2].winner == self.boards[1][1].winner == self.boards[2][0].winner == player:
                return True
        return False

    def __str__(self):
        return '\n\n'.join(['\n'.join([' '.join([str(self.boards[row][col]) for col in range(3)]) for row in range(3)])])


if __name__ == "__main__":
    game = Game()
    while not game.is_game_over():
        print(game)
        board_row = int(input("Enter the board row (0-2): "))
        board_col = int(input("Enter the board column (0-2): "))
        cell_row = int(input("Enter the cell row (0-2): "))
        cell_col = int(input("Enter the cell column (0-2): "))
        if not game.make_move(board_row, board_col, cell_row, cell_col):
            print("Invalid move. Try again.")
    print("Game over!")