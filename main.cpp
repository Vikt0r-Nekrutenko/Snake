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
    GameModel model = GameModel(renderer.Size);

    PausedGameView1 paused = PausedGameView1(&model);
    MenuView1 menu1 = MenuView1(&model, renderer.Size);
    GameView1 game1 = GameView1(&model);
    EndView1 end1 = EndView1(&model);
    stf::smv::BaseView *current1 = &menu1;
    bool  gameIsContinue = true;

public:

    Game() : Window() {}

    bool onUpdate(const float dt) override
    {
        current1->update(dt);
        current1->show(renderer);

        return gameIsContinue;
    }

    stf::smv::BaseView* viewSwitcher(stf::smv::ModelBaseState state)
    {
        switch (state) {
        case stf::smv::ModelBaseState::start:   return &game1;
        case stf::smv::ModelBaseState::end:     return &end1;
        case stf::smv::ModelBaseState::menu:    return &menu1;
        case stf::smv::ModelBaseState::pause:   return &paused;
        case stf::smv::ModelBaseState::none:    return current1;
        case stf::smv::ModelBaseState::exit:
            gameIsContinue = false;
            return current1;
        }
    }

    void keyEvents(const int key) override
    {
        current1 = viewSwitcher(current1->keyEventsHandler(key));
    }

    void mouseEvents(const MouseRecord &mr) override
    {
        current1 = viewSwitcher(current1->mouseEventsHandler(mr));
    }
};

int main()
{
    Game snake;
    return snake.run();
}
