#include "view.hpp"

GameView::GameView(Model* model) : m_model(model) { }

void GameView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(auto &s : m_model->snake().body())
        renderer.drawPixel(s - camera, '#');
    renderer.drawPixel(m_model->eat(), '~');

    for(int y = 1; y < m_model->mapSize().y; ++y)
        for(int x = 0; x < m_model->mapSize().x; ++x)
            if(x==0||y==1||x==m_model->mapSize().x-1||y==m_model->mapSize().y-1)
                renderer.drawPixel({x,y}, '*');
}

Signal GameView::keyEvents(const int key)
{
    return m_model->keyEvents(key);
}
