class Board:
    def __init__(self):
        # board is a list of cells that are represented
        # by strings (" ", "O", and "X")
        # initially it is made of empty cells represented
        # by " " strings
        self.sign = " "
        self.size = 3
        self.board = list(self.sign * self.size ** 2)
        # the winner's sign O or X
        self.winner = ""

    def show(self):
        print(" A   B   C ")
        print("+---+---+---+")
        print("1| " + self.board[0] + " | " + self.board[3] + " | " + self.board[6] + " |")
        print("+---+---+---+")
        print("2| " + self.board[1] + " | " + self.board[4] + " | " + self.board[7] + " |")
        print("+---+---+---+")
        print("3| " + self.board[2] + " | " + self.board[5] + " | " + self.board[8] + " |")
        print("+---+---+---+")
        # draw the board

    def get_winner(self):
        winner = self.winner
        return winner

    # return the winner's sign O or X (an instance winner)

    def isempty(self, cell):

        if cell == "A1":
            cell = 1
        elif cell == "A2":
            cell = 2
        elif cell == "A3":
            cell = 3
        elif cell == "B1":
            cell = 4
        elif cell == "B2":
            cell = 5
        elif cell == "B3":
            cell = 6
        elif cell == "C1":
            cell = 7
        elif cell == "C2":
            cell = 8
        elif cell == "C3":
            cell = 9

        if self.board[cell - 1] == " ":
            return True
        else:
            return False
    # return True if the cell is empty (not marked with X or O)

    def set(self, cell, sign):
        self.board[int(cell) - 1] = sign
    # mark the cell on the board with the sign X or O

    def isdone(self):
        done = False
        # check all game terminating conditions, if one of them is present, assign the var done to True
        if ((self.board[0] == "X" and self.board[1] == "X" and self.board[2]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[3] == "X" and self.board[4] == "X" and self.board[5]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[6] == "X" and self.board[7] == "X" and self.board[8]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[0] == "X" and self.board[3] == "X" and self.board[6]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[1] == "X" and self.board[4] == "X" and self.board[7]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[2] == "X" and self.board[5] == "X" and self.board[8]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[0] == "X" and self.board[4] == "X" and self.board[8]) == "X"):
            done = True
            self.winner = "X"
        elif ((self.board[2] == "X" and self.board[4] == "X" and self.board[6]) == "X"):
            done = True
            self.winner = "X"

        # depending on conditions assign the instance var winner to O or X

         # check all game terminating conditions, if one of them is present, assign the var done to True
        if ((self.board[0] == "O" and self.board[1] == "O" and self.board[2]) == "O"):
             done = True
             self.winner = "O"
        elif((self.board[3] == "O" and self.board[4] == "O" and self.board[5]) == "O"):
            done = True
            self.winner = "O"
        elif((self.board[6] == "O" and self.board[7] == "O" and self.board[8]) == "O"):
            done = True
            self.winner = "O"
        elif((self.board[0] == "O" and self.board[3] == "O" and self.board[6]) == "O"):
            done = True
            self.winner = "O"
        elif ((self.board[1] == "O" and self.board[4] == "O" and self.board[7]) == "O"):
            done = True
            self.winner = "O"
        elif ((self.board[2] == "O" and self.board[5] == "O" and self.board[8]) == "O"):
            done = True
            self.winner = "O"
        elif ((self.board[0] == "O" and self.board[4] == "O" and self.board[8]) == "O"):
            done = True
            self.winner = "O"
        elif ((self.board[2] == "O" and self.board[4] == "O" and self.board[6]) == "O"):
            done = True
            self.winner = "O"

        cells = [1, 2, 3, 4, 5, 6, 7, 8, 9]

        if (self.isempty(0) == False and self.isempty(1) == False and self.isempty(2) == False and self.isempty(3) == False and self.isempty(4) == False and self.isempty(5) == False and self.isempty(6) == False and self.isempty(7) == False and self.isempty(8) == False):
            done = True
            # depending on conditions assign the instance var winner to O or X

        return done




