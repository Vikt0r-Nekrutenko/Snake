#include "gameview.hpp"
#include "player.hpp"


GameView::GameView(stf::smv::BaseModel *model)
    : BaseGameView(model)
{}

void GameView::show(stf::Renderer &renderer)
{
    for(int y = 1; y < model<GameModel>()->mapSize().y; ++y) {
        for(int x = 0; x < model<GameModel>()->mapSize().x; ++x) {
            if(x==0||y==1||x==model<GameModel>()->mapSize().x-1||y==model<GameModel>()->mapSize().y-1) {
                renderer.drawPixel(stf::Vec2d(x,y), '*');
            }
        }
    }

    for(auto food : model<GameModel>()->foodModel().getPossibleFood()) {
        renderer.drawPixel(food->pos(), food->symbol());
    }

    for(auto hunter : model<GameModel>()->hunterModels()) {
        hunter->show(renderer, {0,0});
    }

    const Player* player = dynamic_cast<const Player *>(model<GameModel>()->hunterModels().at(0));
    renderer.draw({10, 0}, "SCORE: %d LVL: %d LIFES: %d",
                  player->score(),
                  player->lvl(),
                  player->lifes());

}

PausedGameView::PausedGameView(stf::smv::BaseModel *model)
    : BasePausedGameView(model)
{}

void PausedGameView::show(stf::Renderer &renderer)
{
    for(auto food : model<GameModel>()->foodModel().getPossibleFood()) {
        renderer.drawPixel(food->pos(), food->symbol());
    }

    for(auto hunter : model<GameModel>()->hunterModels()) {
        hunter->show(renderer, {0,0});
    }

    const Player* player = dynamic_cast<const Player *>(model<GameModel>()->hunterModels().at(0));
    renderer.draw({10, 0}, "SCORE: %d LVL: %d LIFES: %d",
                  player->score(),
                  player->lvl(),
                  player->lifes());

}
