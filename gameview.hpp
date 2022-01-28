#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "view.hpp"

#include "smv/basegameview.hpp"
#include "smv/basepausedgameview.hpp"

class GameView : public stf::smv::BaseGameView
{
public:
    GameView(stf::smv::BaseModel *model);

    void show(stf::Renderer& renderer) override;
};

class PausedGameView : public stf::smv::BasePausedGameView
{
public:
    PausedGameView(stf::smv::BaseModel *model);

    void show(stf::Renderer& renderer) override;
};


#endif // GAMEVIEW_HPP
