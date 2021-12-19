#include "view.hpp"

GameView::GameView(Model* model) : m_model(model) { }

void GameView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(auto &s : m_model->snake().body()) renderer.drawPixel(s - camera, '#');
    renderer.drawPixel(m_model->eat(), '~');
}
