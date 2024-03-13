#include <string>
#include "chess.hpp"
#include "GameErrors.hpp"
#include "console.hpp"

#include <iostream>

void validate(const chess::Entity *figure, const chess::cell &to) {
    if((figure->board[to.x][to.y] != nullptr) && (figure->side == figure->board[to.x][to.y]->side)){
        throw (play_errors::WrongStep("You can't step on your figures"));
    }
}

void move(chess::Entity *figure, const chess::cell &to) {
    if(figure->board[to.x][to.y] != nullptr) {
        delete figure->board[to.x][to.y];
    }
    figure->board[to.x][to.y] = figure;
    figure->board[figure->position.x][figure->position.y] = nullptr;
    figure->position.x = to.x;
    figure->position.y = to.y;
}

chess::ChessBoard::ChessBoard()
{
    this->board = new chess::Entity **[8];
    for (int i = 0; i < 8; i++) {
        this->board[i] = new chess::Entity *[8];
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

}

chess::ChessBoard::~ChessBoard()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr)
            {
                delete board[i][j];
            }
        }
        delete[] board[i];
    }
    delete[] board;
}

std::string chess::ChessBoard::printBoard()
{
    std::string boardView; 
    for(int i = 7; i >= 0; i--) 
    {
        for(int j = 0; j < 8; j++)
        {
            if(this->board[j][i] == nullptr) {
                boardView += (i + j) & 1 ? "◻ " : "◼ ";
            }
            else {
                boardView += this->board[j][i]->img;
            }
        }
    }
    
    return boardView;
}

void chess::ChessBoard::addFigure(const cell &to, Entity *figure)
{
    this->board[to.x][to.y] = figure;
}

void chess::ChessBoard::move(const cell &from, const cell &to)
{
    if (this->board[from.x][from.y] == nullptr) {
        throw(play_errors::WrongStep("there\'s no any figure in cell"));
    } else {
        this->board[from.x][from.y]->step(to);
    }
}

void chess::ChessBoard::addRawFigure(const std::string &side, const std::string &figure, const std::string &place)
{
    chess::sides s;
    chess::cell c(place);

    if(side == "white") {
        s = chess::sides::white;
    } else if(side == "black") {
        s = chess::sides::black;
    } else {
        throw play_errors::WrongInput("You can't make figure be " + side + "color");
    }

    if(this->board[c.x][c.y] != nullptr) {
        throw play_errors::WrongInput("There is already a figure in cell");
    }

    if (figure == "pawn") {
        this->board[c.x][c.y] = new chess::Pawn(this->board, c, s, s==chess::sides::black ? "♟ " : "♙ ");
    } else if (figure == "horse") {
        this->board[c.x][c.y] = new chess::Horse(this->board, c, s, s==chess::sides::black ? "♞ " : "♘ ");
    } else if (figure == "bishop") {
        this->board[c.x][c.y] = new chess::Bishop(this->board, c, s, s==chess::sides::black ? "♝ " : "♗ ");
    } else if (figure == "rook") {
        this->board[c.x][c.y] = new chess::Rook(this->board, c, s, s==chess::sides::black ? "♜ " : "♖ ");
    } else if (figure == "queen") {
        this->board[c.x][c.y] = new chess::Queen(this->board, c, s, s==chess::sides::black ? "♛ " : "♕ ");
    } else if (figure == "king") {
        this->board[c.x][c.y] = new chess::King(this->board, c, s, s==chess::sides::black ? "♚ " : "♔ ");
    } else {
        throw play_errors::WrongInput("There is no such figure as " + figure);
    }
}

void chess::ChessBoard::deleteRawFigure(const std::string &side)
{
    chess::cell c(side);
    if(this->board[c.x][c.y] == nullptr) {
        throw play_errors::WrongStep("there is no figure in the cell");
    }
    delete this->board[c.x][c.y];
    this->board[c.x][c.y] = nullptr;
}

void chess::ChessBoard::setBoard()
{
    for(int i = 0; i < 8; i++)
    {
        this->board[i][1] = new chess::Pawn(this->board, cell(i, 1), sides::white, "♙ ");
        this->board[i][6] = new chess::Pawn(this->board, cell(i, 6), sides::black, "♟ ");
    }
    this->board[0][0] = new chess::Rook(this->board, cell(0, 0), sides::white, "♖ ");
    this->board[7][0] = new chess::Rook(this->board, cell(7, 0), sides::white, "♖ ");
    this->board[0][7] = new chess::Rook(this->board, cell(0, 7), sides::black, "♜ ");
    this->board[7][7] = new chess::Rook(this->board, cell(7, 7), sides::black, "♜ ");
    this->board[1][0] = new chess::Horse(this->board, cell(1,0), sides::white, "♘ ");
    this->board[6][0] = new chess::Horse(this->board, cell(6,0), sides::white, "♘ ");
    this->board[1][7] = new chess::Horse(this->board, cell(1,7), sides::black, "♞ ");
    this->board[6][7] = new chess::Horse(this->board, cell(6,7), sides::black, "♞ ");
    this->board[2][0] = new chess::Bishop(this->board, cell(2,0), sides::white, "♗ ");
    this->board[5][0] = new chess::Bishop(this->board, cell(5,0), sides::white, "♗ ");
    this->board[2][7] = new chess::Bishop(this->board, cell(2,7), sides::black, "♝ ");
    this->board[5][7] = new chess::Bishop(this->board, cell(5,7), sides::black, "♝ ");
    this->board[3][0] = new chess::Queen(this->board, cell(3,0), sides::white, "♕ ");
    this->board[4][0] = new chess::King(this->board, cell(4,0), sides::white, "♔ ");
    this->board[4][7] = new chess::King(this->board, cell(4,7), sides::black, "♚ ");
    this->board[3][7] = new chess::Queen(this->board, cell(3,7), sides::black, "♛ ");
}

chess::cell::cell(const std::string &str)
{
    if ((str.length() == 2) && (str[0] >= 'A') && (str[0] <= 'H') && (str[1] >= '1') && (str[1] <= '8')){
        this->x = str[0] - 'A';
        this->y = str[1] - '0' - 1;
    }else{
        throw play_errors::WrongInput(str);
    }
}

void chess::Horse::step(const cell &to)
{
    validate(this, to);
    if((std::abs(to.x - this->position.x) == 1) && (std::abs(to.y - this->position.y) == 2) || (std::abs(to.x - this->position.x) == 2) && (std::abs(to.y - this->position.y) == 1)) {
        move(this, to);
    }else{
        // char tmp[] = {'A' + to.x, '0' + to.y, '\n'};
        throw(play_errors::WrongInput("you cant step on there"));
    }
}

void chess::Pawn::step(const cell &to)
{
    validate(this, to);

    if(to.x - this->position.x == 0) 
    {
        if((to.y - this->position.y) * (static_cast<int>(this->side) * 2 - 1) > 0) {
            throw play_errors::WrongStep("Wrong diraction of pawn");
        }
        if(((to.y - this->position.y) * (static_cast<int>(this->side) * 2 - 1) == -1) && (this->board[to.x][to.y] == nullptr)) 
        {
            move(this, to);
            return;
        }
        if(((to.y - this->position.y) * (static_cast<int>(this->side) * 2 - 1) == -2) && (this->board[to.x][to.y] == nullptr) && (this->board[to.x][to.y - 1] == nullptr) && ((this->position.y == 1) || (this->position.y == 6))) 
        {
            move(this, to);
            return;
        }
        else {
            const char tmp[] = "The only first move allows you to go forward for two cells";
            throw play_errors::WrongStep(tmp);
        }
    }

    if((abs(to.x - this->position.x) == 1) && ((to.y - this->position.y) * (static_cast<int>(this->side) * 2 - 1) == -1))
    {
        if (this->board[to.x][to.y] == nullptr) { throw play_errors::WrongStep("Pawn can only eat diagonaly"); }

        if(this->board[to.x][to.y]->side != this->side)
        {
            move(this, to);
            return;
        }
        else {
            const char tmp[] = "You can only eat on the diagonals by pawn";
            throw play_errors::WrongStep(tmp);
        }
    }

    throw play_errors::WrongInput("you cant step on there");
}

void chess::Bishop::step(const cell &to)
{
    validate(this, to);

    if(abs(this->position.x - to.x) == abs(this->position.y - to.y))
    {
        int signX = to.x > this->position.x ? 1 : -1, signY = to.y > this->position.y ? 1 : -1;

        for(int i = 1; i < abs(this->position.x - to.x); i++)
        {   
            if(this->board[this->position.x + (i * signX)][this->position.y + (i * signY)] != nullptr)
            {
                throw play_errors::WrongStep("You can't move through other figures");
            }
        }

        move(this, to);
    } else {
        throw play_errors::WrongStep("With Bishop you can go only diagonaly");
    }
}

void chess::Rook::step(const cell &to)
{
    validate(this, to);

    if((this->position.x != to.x) && (this->position.y != to.y)) 
    {
        throw play_errors::WrongStep("Rook can only move by stright lines");
    } else {
        int signX = to.x > this->position.x ? 1 : -1, signY = to.y > this->position.y ? 1 : -1;

        for(int i = 1; i < abs(this->position.x - to.x); i++)
        {
            if(this->board[this->position.x + (i * signX)][this->position.y] != nullptr)
            {
                throw play_errors::WrongStep("You can't move through other figures");
            }
        }
        for(int i = 1; i < abs(this->position.y - to.y); i++)
        {
            if(this->board[this->position.x][this->position.y + (i * signY)] != nullptr)
            {
                throw play_errors::WrongStep("You can't move through other figures");
            }
        }

        move(this, to);
    }


}

void chess::Queen::step(const cell &to)
{
    validate(this, to);

    if((abs(this->position.x - to.x) != abs(this->position.y - to.y)) && ((this->position.x != to.x) && (this->position.y != to.y)))
    {
        throw play_errors::WrongStep("Queen can only move by stright lines or diagonaly");
    } else {
        int signX = to.x > this->position.x ? 1 : -1, signY = to.y > this->position.y ? 1 : -1;

        if (abs(this->position.x - to.x) == abs(this->position.y - to.y))
        {
            for(int i = 1; i < abs(this->position.x - to.x); i++)
            {   
                if(this->board[this->position.x + (i * signX)][this->position.y + (i * signY)] != nullptr)
                {
                    throw play_errors::WrongStep("You can't move through other figures");
                }
            }
        } else {
            for(int i = 1; i < abs(this->position.x - to.x); i++)
            {
                if(this->board[this->position.x + (i * signX)][this->position.y] != nullptr)
                {
                    throw play_errors::WrongStep("You can't move through other figures");
                }
            }
            for(int i = 1; i < abs(this->position.y - to.y); i++)
            {
                if(this->board[this->position.x][this->position.y + (i * signY)] != nullptr)
                {
                    throw play_errors::WrongStep("You can't move through other figures");
                }
            }
        }

        move(this, to);
    }
}

void chess::King::step(const cell &to)
{
    validate(this, to);

    if((abs(this->position.x - to.x) <= 1) && (abs(this->position.y - to.y)))
    {
        move(this, to);
    } else {
        throw play_errors::WrongStep("King can't move to cell out of nearest scuare");
    }
}
