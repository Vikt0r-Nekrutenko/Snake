#include "endview.hpp"

EndView::EndView(GameModel *model)
    : View(model),
      m_end("end.spr")
{ }

void EndView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    m_end.show(renderer, renderer.Size / 2 - m_end.Size() / 2 - stf::Vec2d(0, 11));
    renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 0), "SCORE: %d", m_model->hunterModels().at(0)->score());
    renderer.draw(renderer.Size / 2 - stf::Vec2d(4, 2), "LEVEL: %d", m_model->hunterModels().at(0)->lvl());
}

Signal EndView::keyEvents(const int key)
{
    m_model->reset();
    return Signal::pause;
}
