#include "console.hpp"
#include "GameErrors.hpp"

#include <string>
#include <iostream>
#include <cstdio>

void console::print_help()
{
    system("clear");
    std::string tmp = "list of all commands\n - help\n - exit\n - addFigure\n - deleteFigure\n - [cell to grab figure] [cell to move figure in]\n";
    std::cout << tmp << "Press enter to continue...";
    std::getchar();
    std::getchar();
}

void console::initialize()
{
    system("clear");
    std::string tmp = "     _/_/_/  _/    _/  _/_/_/_/    _/_/_/    _/_/_/        _/_/_/  _/_/_/    _/_/_/ \n  _/        _/    _/  _/        _/        _/            _/        _/    _/  _/    _/\n _/        _/_/_/_/  _/_/_/      _/_/      _/_/        _/        _/_/_/    _/_/_/   \n_/        _/    _/  _/              _/        _/      _/        _/        _/        \n _/_/_/  _/    _/  _/_/_/_/  _/_/_/    _/_/_/    _/    _/_/_/  _/        _/         \n";
    tmp += "\nPress enter to continue...";
    std::cout << tmp;
    std::getchar();
    system("clear");
    tmp = "Do you want to start new game or set figures by your own: Y/N   ";
    std::cout << tmp;
    std::cin >> tmp;


    chess::ChessBoard board;

    if(tmp == "Y") {
        board.setBoard();
    } else if(tmp == "N") {
        tmp = "please enter new entities in format: Color Figure Place\n";
        std::cout << tmp;
        while(1) {
            std::string side, figure, place;
            std::cin >> side;
            if (side == "stop") { break; }
            std::cin >> figure >> place;
            
            try{
                board.addRawFigure(side, figure, place);
            } catch (play_errors::WrongInput & e) {
                std::cout << "Something went wrong -> " + e.message();
                std::getchar();
            }
        }
    }

    console::mainLoop(board);
}

void console::mainLoop(chess::ChessBoard &board)
{
    std::string tmp;
    while(1) {
        console::paintDesk(board);

        std::cin >> tmp;

        if(tmp == "help") {
            console::print_help();
            continue;
        }
        if(tmp == "exit") {
            system("clear");
            exit(0);
        }
        if(tmp == "addFigure") {
            std::string side, figure, place;
            std::cin >> side;
            if (side == "stop") { break; }
            std::cin >> figure >> place;
            
            try{
                board.addRawFigure(side, figure, place);
                continue;
            } catch (play_errors::WrongInput & e) {
                std::cout << "Something went wrong -> " + e.message();
                std::getchar();
                std::getchar();
            }
        }
        if(tmp == "deleteFigure") {
            std::string place;
            std::cin >> place;
            
            try{
                board.deleteRawFigure(place);
                continue;
            }catch (play_errors::WrongInput & e) {
                std::cout << "Something went wrong -> " + e.message();
                std::getchar();
                std::getchar();
            }catch (play_errors::WrongStep & e) {
                std::cout << "You can't choose that cell -> " + e.message();
                std::getchar();
                std::getchar();
            }

        }
        try {
            chess::cell from(tmp);
            std::string move;
            std::cin >> move;
            chess::cell to(move);
            board.move(from, to);

        } catch (play_errors::WrongInput & e) {
            std::cout << "Something went wrong -> " + e.message();
            std::getchar();
            std::getchar();
        } catch (play_errors::WrongStep & e) {
            std::cout << "You can't make that move -> " + e.message();
            std::getchar();
            std::getchar();
        }

    }
}

void console::paintDesk(chess::ChessBoard &board)
{
    system("clear");
    std::string tmp = "", board_row = board.printBoard();

    tmp += "  A B C D E F G H\n";

    for(int i = 0; i < 8; i++) 
    {
        tmp += '8' - i;
        tmp += " " + board_row.substr(i * 8 * 4, 8 * 4) + "\n";
    }
    std::cout << tmp << std::endl;

}

int main() {
    console::initialize();
}