#include "gameview.hpp"
#include "player.hpp"

GameView::GameView(GameModel* model)
    : View(model)
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

    for(auto hunter : m_model->hunterModels()) {
        hunter->show(renderer, camera);
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
