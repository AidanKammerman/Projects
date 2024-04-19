class Player:
    def __init__(self, name, sign):
        self.name = name  # player's name
        self.sign = sign  # player's sign O or X
        cells = [1, 2, 3, 4, 5, 6, 7, 8, 9]

    def get_sign(self):

        # return an instance sign
        sign = self.sign
        return sign

    def get_name(self):
        # return an instance name
        name = self.name
        return name

    def choose(self, board):
        # prompt the user to choose a cell # Fix the While loop to check for already filled squares

        cell = input(Player.get_name(self) + " , " + Player.get_sign(self) + ": Enter a cell [A-C][1-3]: ")

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

        cells = [1, 2, 3, 4, 5, 6, 7, 8, 9]

        while ((cell not in cells) or board.isempty(cell) == False):

            cells = [1, 2, 3, 4, 5, 6, 7, 8, 9]

            if cell == "A1":
                cell = 1
            elif cell  == "A2":
                cell = 2
            elif cell  == "A3":
                cell = 3
            elif cell  == "B1":
                cell = 4
            elif cell  == "B2":
                cell = 5
            elif cell  == "B3":
                cell = 6
            elif cell  == "C1":
                cell = 7
            elif cell  == "C2":
                cell = 8
            elif cell  == "C3":
                cell = 9
            if (cell not in cells):
                print("You did not choose correctly.")
                cell = input(Player.get_name(self) + " , " + Player.get_sign(self) + ": Enter a cell [A-C][1-3]: ")
            elif (board.isempty(cell) == False):
                print("You did not choose correctly.")
                cell = input(Player.get_name(self) + " , " + Player.get_sign(self) + ": Enter a cell [A-C][1-3]: ")



# if the user enters a valid string and the cell on the board is empty, update the board
        else:
            board.set(cell, Player.get_sign(self))
# otherwise print a message that the input is wrong and rewrite the prompt

# use the methods board.isempty(cell), and board.set(cell, sign)
# you need to convert A1, B1, …, C3 cells into index values from 1 to 9
# you can use a tuple ("A1", "B1",...) to obtain indexes
# you can do the conversion here in the player.py or in the board.py
# this implementation is up to you