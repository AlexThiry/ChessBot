#include <iostream>
#include <map>
#include <vector>

class Piece {
    public:
        const int None = 0;
        const int King = 1;
        const int Queen = 2;
        const int Bishop = 3;
        const int Knight = 4;
        const int Rook = 5;
        const int Pawn = 6;

        const int White = 8;
        const int Black = 16;
};

class King {};

class Queen {};

class Bishop {};

class Knight {};

class Rook {};

class PawnWhite {
    public:
        const int Value = 14;
        const int Color = 8;
        const int Piece = 6;
        bool Moved;

        std::pair<int,int> Position;
        std::string boardState[8][8];

        PawnWhite (std::pair<int,int> pos) {
            Position.first, Position.second = pos.first, pos.second;
            Moved = pos.first == 6 ? true : false; //If on 6th rank (0 indexed) means that it hasn't moved
        }

        std::vector<std::pair<int,int>> getMoves() {
            std::vector<std::pair<int,int>> moves;
            if (boardState[Position.first-1][Position.second] == "-") { //If square ahead is empty
                moves.push_back(std::pair<int,int> (Position.first-1, Position.second));
            } else if (!Moved && boardState[Position.first-2][Position.second] == "-") { //If square 2-away is empty
                moves.push_back(std::pair<int,int> (Position.first-2, Position.second));
            }
            return moves;
        }

        std::vector<std::pair<int,int>> getLegalMoves() {
            //En passant for later
            //Check for check
            return getMoves();
        }
};

class Board {
    public:
        std::string board[8][8];
        std::string startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        const std::map<char, int> fenToNum = {
            {'K', 9},
            {'Q', 10},
            {'B', 11},
            {'N', 12},
            {'R', 13},
            {'P', 14},
            {'k', 17},
            {'q', 18},
            {'b', 19},
            {'n', 20},
            {'r', 21},
            {'p', 22},
            {'-', 0}
        };

        Board() {
            convertFen(startingFen);
        }

        void convertFen(std::string fen) {
            int currentRank = 0;
            int currentFile = 0;
            for (char& letter : fen) {
                if (letter == '/') {
                    currentRank++;
                    currentFile = 0;
                } else if (isdigit(letter)) {
                    int count = letter - '0';
                    currentFile += count;
                } else {
                    board[currentRank][currentFile] = letter;
                    currentFile++;
                }
            }
        }

        void updateBoard() {}

        void displayBoad() {
            for (int rank = 0; rank < 8; rank++) {
                for (int file = 0; file < 8; file++) {
                    file==7? std::cout << (board[rank][file].empty() ? "-" : board[rank][file]) <<"\n" : std::cout << (board[rank][file].empty() ? "-" : board[rank][file]) <<" | ";
                }
            }
        }
        std::vector<std::vector<std::string>> getBoard() {
            std::vector<std::vector<std::string>> copy(8, std::vector<std::string>(8));
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    copy[i][j] = board[i][j];
                }
            }
            return copy;
        }
};

int main() {
    Board gameBoard;
    std::vector<std::vector<std::string>> boardString = gameBoard.getBoard();

    for (std::vector i : boardString) {
        for (std::string j : i) {
            std::cout<< j;
        }
    }
    
    //gameBoard.displayBoad();
    return 0;
}