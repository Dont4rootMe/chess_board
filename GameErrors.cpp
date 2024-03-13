#include "GameErrors.hpp"


play_errors::WrongInput::WrongInput(const std::string &message){
    this->msg = "Folowing command is unproccessable: " + message + "\n" + "Please, check the syntax\n";
}

play_errors::WrongStep::WrongStep(const std::string &message)
{
    this->msg = "Wrong move code: " + message + "\n" + "Reconsider your input\n";
}

std::string play_errors::Game_Error::message()
{
    return this->msg;
}
