#ifndef VIEW_HPP
#define VIEW_HPP

#include "renderer.hpp"
#include "model.hpp"

class View
{
public:
    virtual void show(stf::Renderer &renderer, const stf::Vec2d& camera = {0,0}) = 0;
    virtual Signal keyEvents(const int key) = 0;
};

class GameView : public View
{
public:
    GameView(Model* model);

    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    Model* m_model = nullptr;
};

#endif // VIEW_HPP
