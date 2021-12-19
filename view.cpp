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

void MenuView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    renderer.drawText({1,1}, "press S to start, E to end");
}

Signal MenuView::keyEvents(const int key)
{
    switch (key) {
    case 's': return Signal::start;
    case 'e': return Signal::end;
    }
    return Signal::none;
}
