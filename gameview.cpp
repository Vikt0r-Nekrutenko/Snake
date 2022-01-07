#include "gameview.hpp"
#include "player.hpp"

GameView::GameView(GameModel* model)
    : m_model(model)
{ }

void GameView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    for(int y = 1; y < m_model->mapSize().y; ++y) {
        for(int x = 0; x < m_model->mapSize().x; ++x) {
            if(x==0||y==1||x==m_model->mapSize().x-1||y==m_model->mapSize().y-1) {
                renderer.drawPixel(stf::Vec2d(x,y) - camera, '*');
            }
        }
    }

    for(auto food : m_model->foodModel().getPossibleFood()) {
        renderer.drawPixel(food->pos() - camera, food->symbol());
    }

    for(size_t s = 0; s < m_model->hunterModels().size(); ++s) {
        for (size_t i  = 0; i < m_model->hunterModels().at(s)->hunter()->body().size(); ++i) {
            renderer.drawPixel(m_model->hunterModels().at(s)->hunter()->body().at(i) - camera, i % 2 ? 'x' : '0');
        }
    }



    const Player* player = dynamic_cast<const Player *>(m_model->hunterModels().at(0));
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
