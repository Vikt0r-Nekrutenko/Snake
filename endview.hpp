#ifndef ENDVIEW_HPP
#define ENDVIEW_HPP

#include "view.hpp"

class EndView : public View
{
public:
    EndView(GameModel* model);
    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    stf::Sprite m_end;
};

#include "smv/baseendview.hpp"
#include "model.hpp"

class EndView : public stf::smv::BaseEndView
{
public:
    EndView(stf::smv::BaseModel *model)
        : BaseEndView(model)
    {}

    void show(stf::Renderer& renderer) override
    {
        renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 0), "SCORE: %d", model<GameModel>()->hunterModels().at(0)->score());
        renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 2), "LEVEL: %d", model<GameModel>()->hunterModels().at(0)->lvl());
    }
};

#endif // ENDVIEW_HPP
