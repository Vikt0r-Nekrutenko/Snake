#ifndef VIEW_HPP
#define VIEW_HPP

#include "renderer.hpp"
#include "model.hpp"
#include "animsprite.hpp"

class View
{
public:
    virtual void show(stf::Renderer &renderer, const stf::Vec2d& camera = {0,0}) = 0;
    virtual Signal keyEvents(const int key) = 0;
};



class MenuView : public View
{
public:
    MenuView();
    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    stf::AnimSprite m_menu;
    stf::Sprite     m_bgrnd;
    uint8_t m_selector = 0;
};

class EndView : public GameView
{
public:
    EndView(GameModel* model);
    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    stf::Sprite m_end;
};

#endif // VIEW_HPP
