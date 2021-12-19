#include <iostream>
#include "window.hpp"
#include "snake.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    Snake snake;
    float t = 0.f;
public:
    bool onUpdate(const float dt) override
    {
        if(t > 1.f)
        {
            snake.update();
            t = 0.f;
        }
        snake.show(renderer);
        t += dt;
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
