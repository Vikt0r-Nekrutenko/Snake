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

    GameView1 game1 = GameView1(&model);
    EndView1 end1 = EndView1(&model);
    stf::smv::BaseView *current1 = &game1;
    bool  gameIsContinue = true;
public:
    Game() : Window(), model(renderer.Size), game(&model), menu(&model), end(&model), current(&menu) {}

    bool onUpdate(const float dt) override
    {
        current1->update(dt);
        current1->show(renderer);
//        if(current == &game) {
//            if(model.onUpdate(dt) == Signal::end) {
//                current = &end;
//            }
//        }
        return gameIsContinue;
    }

    stf::smv::BaseView* viewSwitcher(stf::smv::ModelBaseState state)
    {
        switch (state) {
        case stf::smv::ModelBaseState::start:   return &game1;
        case stf::smv::ModelBaseState::end:     return &end1;
//        case stf::smv::ModelBaseState::menu:    return &menu;
//        case stf::smv::ModelBaseState::pause:   return &pause;
        case stf::smv::ModelBaseState::exit:    return current1;
        case stf::smv::ModelBaseState::none:    return current1;
        }
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
        current1 = viewSwitcher(current1->keyEventsHandler(key));
    }

    void mouseEvents(const MouseRecord &mr) override {}
};

int main()
{
    Game snake;
    return snake.run();
}
