#include <iostream>
#include "window.hpp"
#include "snake.hpp"
#include "random.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    stf::Vec2d eat {21, 4};
    Snake snake;
    float t = 0.f;
public:
    bool onUpdate(const float dt) override
    {
        if(t > .025f)
        {
            if(snake.head().x > eat.x) snake.A();
            if(snake.head().x < eat.x) snake.D();
            if(snake.head().y > eat.y) snake.W();
            if(snake.head().y < eat.y) snake.S();
            snake.update();
            if(snake.head().diff(eat) < 1.f) {
                snake.feed(); eat = Vec2d(Random(time(0)).getNum(2, renderer.Size.x-1),
                                          Random(time(0)).getNum(2, renderer.Size.y-1));
            }
            if(snake.isAteHerself()) return false;
            snake.wrapping(1,1, renderer.Size.x, renderer.Size.y);
            t = 0.f;
        }
        snake.show(renderer);
        renderer.drawPixel(eat, '~');
        t += dt;
        return true;
    }

    void keyEvents(const int key) override
    {
        switch (key) {
        case 'w': snake.W(); break;
        case 'a': snake.A(); break;
        case 's': snake.S(); break;
        case 'd': snake.D(); break;
        }
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
