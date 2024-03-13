#include <string>

namespace play_errors {
    class Game_Error {
    public:
        std::string message();
    protected:
        std::string msg;
    };

    class WrongStep : public Game_Error {
    public:
        WrongStep(const std::string &message);
    };

    class WrongInput : public Game_Error {
    public:
        WrongInput(const std::string &message);
    };
}
