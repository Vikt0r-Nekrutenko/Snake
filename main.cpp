#include <iostream>
#include "window.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
public:
    bool onUpdate(const float dt) override
    {
        return true;
    }

    void keyEvents(const int key) override
    {

    }

    void mouseEvents(const MouseRecord &mr) override
    {

    }
};

int main()
{
    Game snake;
    return snake.run();
}
