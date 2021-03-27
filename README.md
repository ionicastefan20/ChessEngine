# <strong> Chess Engine </strong>

## <strong> Table of Contents </strong>

- [<strong> Chess Engine </strong>](#-chess-engine-)
  - [<strong> Table of Contents </strong>](#-table-of-contents-)
  - [<strong> Compiling Instructions </strong>](#-compiling-instructions-)
  - [Project Structure](#project-structure)
    - [Piece](#piece)
  - [Algorithms Details](#algorithms-details)
  - [Inspiration Sources](#inspiration-sources)
  - [Member's Responsabilities](#members-responsabilities)
  - [Examples of running](#examples-of-running)
  
## <strong> Compiling Instructions </strong>

    make clean
    make build
    make run

## Project Structure

### Piece

The Piece class contains the constants used for the codification of each
existing chess piece. A piece is represented on 5 bits and the type of the piece
can be found by checking the last 3 bits of the codification. A piece is white
if the 4th bit is set to 1 or black if the 5th bit is set to 1. The 4th and the
5th bits CANNOT be set to 1 simultaneously.

Examples (the color of the piece is marked with <span
style="color:green">green</span> and the type of the piece is marked with <span
style="color:red">red</span>):

White Pawn &rarr; <span style="color:green">01</span><span
style="color:red">001</span>

Black Knight &rarr; <span style="color:green">10</span><span
style="color:red">011</span>

<br>

The "initDistancesAndDirections()" method in the Move class 


Board Class is used to represent the chess table. It is formed from 63 squares.
For their representation, we use a static int pointer named “squares”.
“colorOnMove” variable is used to represent the color of the player that has to
move next. “botColor” variable represents the color of the bot (black/white).
The “initBoard()” method initializes the pieces on board, putting every piece on
its corresponding square (for example, the white queen is on the 5th square and
the black queen on 60th square). We use “getOpositeBotColor” to make a bitwise
xor with a mask of 11000, to change the current color to the oposite one. The
methond “encodeMove” takes a pair of integers that represent a square’s location
and returns a string that represents a move on the table (example”a3a4”). As an
opposite to it, the method "decodeMove" recieves a move as a string that will be
decoded as an index to the corresponding square in the squares array. The
"makeMove" method takes a string as an argument (it represents a move) and makes
that move on the table. The "colorOnMove" variable will get the color of the
player that has to move. The move from parameter is decoded as a result and it
directly "moves" the piece.



Move Class represents a move on the table. It 

## Algorithms Details

## Inspiration Sources

## Member's Responsabilities 

## Examples of running

For proving that the bot resigns once there is no pawn it can move we present
the following scenario :

1. The board is in the following state and the knight is about to capture the
last black pawn

![image](images/black_resigns_pre.PNG)

2. After the capture we can see that the <strong>xboard</strong> received the
   <em>resign</em> command (black resigned)

![image](images/black_resigns_post.PNG)

