#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "view.hpp"

class MenuView : public View
{
public:
    MenuView(GameModel* model);
    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    stf::AnimSprite m_menu;
    stf::Sprite     m_bgrnd;
    uint8_t m_selector = 0;
};

#endif // MENUVIEW_HPP
