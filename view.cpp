#include "view.hpp"

GameView::GameView(GameModel* model) : m_model(model) { }

void GameView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(int y = 1; y < m_model->mapSize().y; ++y)
        for(int x = 0; x < m_model->mapSize().x; ++x)
            if(x==0||y==1||x==m_model->mapSize().x-1||y==m_model->mapSize().y-1)
                renderer.drawPixel(stf::Vec2d(x,y) - camera, '*');

    showPlayerSnake(*m_model->snakeModels().at(0)->snake(), renderer, camera);
    for(size_t s = 1; s < m_model->snakeModels().size(); ++s)
        showSnake(*m_model->snakeModels().at(s)->snake(), renderer, camera);

    for(auto food : m_model->foodModel().getPossibleFood())
        renderer.drawPixel(food->pos() - camera, food->symbol());

    const Player* player = dynamic_cast<const Player *>(m_model->snakeModels().at(0));
    renderer.draw({10, 0}, "SCORE: %d LVL: %d LIFES: %d",
                  player->score(),
                  player->lvl(),
                  player->lifes());
}

Signal GameView::keyEvents(const int key)
{
    return m_model->keyEvents(key);
}

void GameView::showSnake(const Snake &snake, stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(size_t i = 0; i < snake.body().size(); ++i) {
        renderer.drawPixel(snake.body().at(i) - camera, i % 2 ? 'x' : 'o');
    }
}

void GameView::showPlayerSnake(const Snake &snake, stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(size_t i = 0; i < snake.body().size(); ++i) {
        renderer.drawPixel(snake.body().at(i) - camera, i % 2 ? 'X' : 'O');
    }
}

MenuView::MenuView() : m_menu("menu.spr"), m_bgrnd("bgrnd.spr") { }

void MenuView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    m_menu.show(renderer, renderer.Size / 2 - m_menu.Size() / 2);
    m_bgrnd.show(renderer, renderer.Size / 2 - m_bgrnd.Size() / 2 - stf::Vec2d(0, 7));
}

Signal MenuView::keyEvents(const int key)
{
    switch (key) {
    case 'w': m_menu.prev(); if(m_selector == 0) m_selector = m_menu.frames()-1; else --m_selector; break;
    case 's': m_menu.next(); if(m_selector == m_menu.frames()-1) m_selector = 0; else ++m_selector; break;
    case ' ':
        if (m_selector == 0) return Signal::start;
        else if (m_selector == m_menu.frames() - 1) return Signal::end;
    }
    return Signal::none;
}

EndView::EndView(GameModel *model) : GameView(model), m_end("end.spr") { }

void EndView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    m_end.show(renderer, renderer.Size / 2 - m_end.Size() / 2 - stf::Vec2d(0, 11));
    renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 0), "SCORE: %d", m_model->snakeModels().at(0)->score());
    renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 2), "LEVEL: %d", m_model->snakeModels().at(0)->lvl());
}

Signal EndView::keyEvents(const int key)
{
    m_model->reset();
    return Signal::pause;
}
