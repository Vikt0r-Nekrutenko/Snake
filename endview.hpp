#ifndef ENDVIEW_HPP
#define ENDVIEW_HPP

#include "gameview.hpp"

class EndView : public GameView
{
public:
    EndView(GameModel* model);
    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    stf::Sprite m_end;
};

#endif // ENDVIEW_HPP
