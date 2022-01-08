#include <iostream>
#include "window.hpp"
#include "model.hpp"
#include "gameview.hpp"
#include "menuview.hpp"
#include "endview.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    GameModel model;
    GameView  game;
    MenuView menu;
    EndView  end;
    View* current;
    bool  gameIsContinue = true;
public:
    Game() : Window(), model(renderer.Size), game(&model), end(&model), current(&menu) {}

    bool onUpdate(const float dt) override
    {
        current->show(renderer, {0,0});
        if(current == &game) {
            if(model.onUpdate(dt) == Signal::end) {
                current = &end;
            }
        }


        return gameIsContinue;
    }

    void keyEvents(const int key) override
    {
        switch (current->keyEvents(key)) {
        case Signal::start: current = &game;        break;
        case Signal::pause: current = &menu;        break;
        case Signal::end:   gameIsContinue = false; break;
        case Signal::none:                          break;
        }
    }

    void mouseEvents(const MouseRecord &mr) override {}
};

int main()
{
    Game snake;
    return snake.run();
}
