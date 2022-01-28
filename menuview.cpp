#include "menuview.hpp"
#include "random.hpp"
#include "model.hpp"

MenuView::MenuView(stf::smv::BaseModel *model, const stf::Vec2d &wndSize)
    : BaseMenuView(model),
      m_bgrnd("bgrnd.spr")
{
    m_controls.push_back(new stf::smv::Box({10, 3},
                                           wndSize / 2 - 5 - stf::Vec2d(0, 0),
                                           "Start",
                                           (stf::smv::TMouseEventHandler)&MenuView::onStartBtnClick));

    m_controls.push_back(new stf::smv::Box({10, 3},
                                           wndSize / 2 - 5 + stf::Vec2d(0, 3),
                                           "Normal",
                                           (stf::smv::TMouseEventHandler)&MenuView::onNormalBtnClick));

    m_controls.push_back(new stf::smv::Box({10, 3},
                                           wndSize / 2 - 5 + stf::Vec2d(0, 6),
                                           "Survival",
                                           (stf::smv::TMouseEventHandler)&MenuView::onSurvivalBtnClick));

    m_controls.push_back(new stf::smv::Box({10, 3},
                                           wndSize / 2 - 5 + stf::Vec2d(0, 9),
                                           "Exit",
                                           (stf::smv::TMouseEventHandler)&MenuView::onExitBtnClick));
}

void MenuView::show(stf::Renderer &renderer)
{
    m_bgrnd.show(renderer, renderer.Size / 2 - m_bgrnd.Size() / 2 - stf::Vec2d(0, 9));
    stf::smv::BaseView::show(renderer);
}

stf::smv::ModelBaseState MenuView::onStartBtnClick(const stf::MouseRecord &mr)
{
    return stf::smv::ModelBaseState::start;
}

stf::smv::ModelBaseState MenuView::onSurvivalBtnClick(const stf::MouseRecord &mr)
{
    model<GameModel>()->reset(stf::Random(time(0)).getNum(game_model_settings::SURVIVAL_SNAKES_MIN_COUNT, game_model_settings::SURVIVAL_SNAKES_MAX_COUNT),
                              stf::Random(time(0)).getNum(game_model_settings::SURVIVAL_MOUSES_MIN_COUNT, game_model_settings::SURVIVAL_MOUSES_MAX_COUNT));
    return stf::smv::ModelBaseState::start;
}

stf::smv::ModelBaseState MenuView::onNormalBtnClick(const stf::MouseRecord &mr)
{
    model<GameModel>()->reset(game_model_settings::NORMAL_SNAKES_COUNT, game_model_settings::NORMAL_MOUSE_COUNT);
    return stf::smv::ModelBaseState::start;
}

stf::smv::ModelBaseState MenuView::onExitBtnClick(const stf::MouseRecord &mr)
{
    return stf::smv::ModelBaseState::exit;
}
