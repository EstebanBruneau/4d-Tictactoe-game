from game import Game

def print_instructions():
    print("Welcome to 4D Tic-Tac-Toe!")
    print("The board is a 3x3 grid where each cell is a tic-tac-toe board by itself.")
    print("Players take turns to play in the small board where the previous player played.")
    print("The first player to align 3 of their symbols on the big board wins.")
    print("If no one can do it, it's a tie.")
    print("To make a move, enter the board row, board column, cell row, and cell column (all 0-2).")
    print("For example, to play in the top left cell of the top left board, enter: 0 0 0 0")

def main():
    game = Game()
    # print_instructions()

    while not game.is_game_over():
        print(game)
        try:
            board_row, board_col, cell_row, cell_col = map(int, input(f"Player {game.current_player}, enter your move (board_row board_col cell_row cell_col): ").split())
            if not game.make_move(board_row, board_col, cell_row, cell_col):
                print("Invalid move. Try again.")
        except ValueError:
            print("Invalid input. Please enter four integers separated by spaces.")
    
    print(game)
    print("Game over!")
    if game.current_player == 'O':
        print("Player X wins!")
    elif game.current_player == 'X':
        print("Player O wins!")
    else:
        print("It's a tie!")

if __name__ == "__main__":
    main()