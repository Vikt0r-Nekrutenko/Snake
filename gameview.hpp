#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "view.hpp"

class GameView : public View
{
public:
    GameView(GameModel* model);

    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
protected:
    GameModel* m_model = nullptr;
};

#endif // GAMEVIEW_HPP
