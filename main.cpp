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

    PausedGameView paused = PausedGameView(&model);
    MenuView menu = MenuView(&model, renderer.Size);
    GameView game = GameView(&model);
    EndView end = EndView(&model);
    stf::smv::BaseView *current = &menu;
    bool  gameIsContinue = true;

public:

    Game() : Window() {}

    bool onUpdate(const float dt) override
    {
        current->update(dt);
        current->show(renderer);

        return gameIsContinue;
    }

    stf::smv::BaseView* viewSwitcher(stf::smv::ModelBaseState state)
    {
        switch (state) {
        case stf::smv::ModelBaseState::start:   return &game;
        case stf::smv::ModelBaseState::end:     return &end;
        case stf::smv::ModelBaseState::menu:    return &menu;
        case stf::smv::ModelBaseState::pause:   return &paused;
        case stf::smv::ModelBaseState::none:    return current;
        case stf::smv::ModelBaseState::exit:
            gameIsContinue = false;
            return current;
        }
    }

    void keyEvents(const int key) override
    {
        current = viewSwitcher(current->keyEventsHandler(key));
    }

    void mouseEvents(const MouseRecord &mr) override
    {
        current = viewSwitcher(current->mouseEventsHandler(mr));
    }
};

int main()
{
    Game snake;
    return snake.run();
}
