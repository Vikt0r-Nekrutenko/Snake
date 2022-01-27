#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "view.hpp"

class GameView : public View
{
public:
    GameView(GameModel* model);

    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
};

#include "smv/basegameview.hpp"
#include "smv/basepausedgameview.hpp"
#include "model.hpp"
#include "player.hpp"

class GameView1 : public stf::smv::BaseGameView
{
public:
    GameView1(stf::smv::BaseModel *model)
        : BaseGameView(model)
    {}

    void show(stf::Renderer& renderer) override
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
};

class PausedGameView1 : public stf::smv::BasePausedGameView
{
public:
    PausedGameView1(stf::smv::BaseModel *model)
        : BasePausedGameView(model)
    {}

    void show(stf::Renderer& renderer) override
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
};


#endif // GAMEVIEW_HPP
