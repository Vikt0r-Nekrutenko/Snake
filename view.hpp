#ifndef VIEW_HPP
#define VIEW_HPP

#include "renderer.hpp"
#include "model.hpp"
#include "animsprite.hpp"

class View
{
public:
    View(GameModel* model) : m_model(model) { };

    virtual void show(stf::Renderer &renderer, const stf::Vec2d& camera = {0,0}) = 0;
    virtual Signal keyEvents(const int key) = 0;

protected:
    GameModel* m_model = nullptr;
};

#endif // VIEW_HPP
