#include <iostream>
#include "window.hpp"
#include "model.hpp"
#include "view.hpp"

using namespace std;
using namespace stf;

class Game : public Window
{
    Model model;
    GameView  game;
    MenuView menu;
    EndView  end;
    View* current;
    bool  gameIsContinue = true;
public:
    Game() : Window(), model(renderer.Size), game(&model), end(&model), current(&menu) {}

    bool onUpdate(const float dt) override
    {
        if(current == &game)
            if(model.onUpdate(dt) == Signal::end) {
                current = &end;
            }
        current->show(renderer);

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

    void mouseEvents(const MouseRecord &mr) override
    {

    }
};

int main()
{
    Game snake;
    return snake.run();
}
