#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>

namespace chess {
    enum sides { white, black };

    struct cell {
        int x, y;
        cell(const std::string &str_cell);
        cell(int x, int y) : x(x), y(y) {};
    };


    class Entity {
    public:
        Entity*** board;
        cell position;
        const sides side;
        std::string img;
    public:
        Entity(Entity ***board, cell &pos, const sides &side, std::string img) : position(pos), side(side), img(img)
        {
            this->board = board;
        };

        virtual void step(const cell &to) {};
    };


    class ChessBoard {
    private:
        Entity*** board;

    public:
        ChessBoard();
        ~ChessBoard();

        std::string printBoard();

        void addFigure(const cell &to, Entity *figure);

        void move(const cell &from, const cell &to);
    
        void addRawFigure(const std::string &side, const std::string &figure, const std::string &place);

        void deleteRawFigure(const std::string &side);

        void setBoard();
    };

    class Horse : public Entity {
    public:
        Horse(Entity ***board, cell pos, const sides &side, std::string img) : Entity(board, pos, side, img) {}

        void step(const cell &to);
    };

    class Pawn : public Entity {
        public:
        Pawn(Entity ***board, cell pos, const sides &side, std::string img) : Entity(board, pos, side, img) {}

        void step(const cell &to);
    };

    class Bishop : public Entity {
    public:
        Bishop(Entity ***board, cell pos, const sides &side, std::string img) : Entity(board, pos, side, img) {}

        void step(const cell &to);
    };

    class Rook : public Entity {
    public:
        Rook(Entity ***board, cell pos, const sides &side, std::string img) : Entity(board, pos, side, img) {}

        void step(const cell &to);
    };

    class Queen : public Entity {
    public:
        Queen(Entity ***board, cell pos, const sides &side, std::string img) : Entity(board, pos, side, img) {}

        void step(const cell &to);
    };

    class King : public Entity {
    public:
        King(Entity ***board, cell pos, const sides &side, std::string img) : Entity(board, pos, side, img) {}

        void step(const cell &to);
    };
}

#endif