#include "view.hpp"

GameView::GameView(Model* model) : m_model(model) { }

void GameView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(auto &s : m_model->snake().body())
        renderer.drawPixel(s - camera, '#');
    renderer.drawPixel(m_model->eat(), '~');
    renderer.draw({10, 0}, "SCORE: %d LVL: %d", m_model->score(), m_model->lvl());

    for(int y = 1; y < m_model->mapSize().y; ++y)
        for(int x = 0; x < m_model->mapSize().x; ++x)
            if(x==0||y==1||x==m_model->mapSize().x-1||y==m_model->mapSize().y-1)
                renderer.drawPixel({x,y}, '*');
}

Signal GameView::keyEvents(const int key)
{
    return m_model->keyEvents(key);
}

MenuView::MenuView() : m_menu("menu.spr") { }

void MenuView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    m_menu.show(renderer, renderer.Size / 2 - m_menu.Size() / 2);
}

Signal MenuView::keyEvents(const int key)
{
    switch (key) {
    case 'w': m_menu.prev(); if(m_selector == 0) m_selector = 3; else --m_selector; break;
    case 's': m_menu.next(); if(m_selector == 3) m_selector = 0; else ++m_selector; break;
    case ' ':
        switch (m_selector) {
        case 0: return Signal::start;
        case 3: return Signal::end;
        }
    }
    return Signal::none;
}

void EndView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    renderer.drawText({1,1}, "Game over! Press any key");
}

Signal EndView::keyEvents(const int key)
{
    return Signal::pause;
}
