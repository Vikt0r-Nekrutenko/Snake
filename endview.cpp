#include "endview.hpp"

EndView::EndView(stf::smv::BaseModel *model)
    : BaseEndView(model)
{}

void EndView::show(stf::Renderer &renderer)
{
    m_end.show(renderer, renderer.Size / 2 - m_end.Size() / 2 - stf::Vec2d(0, 9));
    renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 0), "SCORE: %d", model<GameModel>()->hunterModels().at(0)->score());
    renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 2), "LEVEL: %d", model<GameModel>()->hunterModels().at(0)->lvl());
}
