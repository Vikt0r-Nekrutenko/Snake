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
    EndView1 end1 = EndView1(&model);
    View* current;
    stf::smv::BaseView *current1 = &end1;
    bool  gameIsContinue = true;
public:
    Game() : Window(), model(renderer.Size), game(&model), menu(&model), end(&model), current(&menu) {}

    bool onUpdate(const float dt) override
    {
        current1->show(renderer);
//        if(current == &game) {
//            if(model.onUpdate(dt) == Signal::end) {
//                current = &end;
//            }
//        }
        return gameIsContinue;
    }

    void keyEvents(const int key) override
    {
        switch (current->keyEvents(key)) {
        case Signal::normal:
        case Signal::survival:
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
