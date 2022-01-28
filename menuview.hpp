#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "view.hpp"

class MenuView : public View
{
public:
    MenuView(GameModel* model);
    void show(stf::Renderer &renderer, const stf::Vec2d &camera = {0,0}) override;
    Signal keyEvents(const int key) override;
private:
    stf::AnimSprite m_menu;
    stf::Sprite     m_bgrnd;
    uint8_t m_selector = 0;
};

#include "smv/basemenuview.hpp"
#include "random.hpp"

class MenuView1 : public stf::smv::BaseMenuView
{
public:
    MenuView1(stf::smv::BaseModel *model, const stf::Vec2d& wndSize)
        : BaseMenuView(model)
    {
        m_controls.push_back(new stf::smv::Box({10, 3},
                                               wndSize / 2 - 5 - stf::Vec2d(0, 0),
                                               "Start",
                                               (stf::smv::TMouseEventHandler)&MenuView1::onStartBtnClick));

        m_controls.push_back(new stf::smv::Box({10, 3},
                                               wndSize / 2 - 5 + stf::Vec2d(0, 3),
                                               "Normal",
                                               (stf::smv::TMouseEventHandler)&MenuView1::onNormalBtnClick));

        m_controls.push_back(new stf::smv::Box({10, 3},
                                               wndSize / 2 - 5 + stf::Vec2d(0, 6),
                                               "Survival",
                                               (stf::smv::TMouseEventHandler)&MenuView1::onSurvivalBtnClick));

        m_controls.push_back(new stf::smv::Box({10, 3},
                                               wndSize / 2 - 5 + stf::Vec2d(0, 9),
                                               "Exit",
                                               (stf::smv::TMouseEventHandler)&MenuView1::onExitBtnClick));
    }

    void show(stf::Renderer &renderer) override
    {
        stf::smv::BaseView::show(renderer);
    }

    stf::smv::ModelBaseState onStartBtnClick(const stf::MouseRecord& mr)
    {
        return stf::smv::ModelBaseState::start;
    }

    stf::smv::ModelBaseState onSurvivalBtnClick(const stf::MouseRecord& mr)
    {
        model<GameModel>()->reset(stf::Random(time(0)).getNum(game_model_settings::SURVIVAL_SNAKES_MIN_COUNT, game_model_settings::SURVIVAL_SNAKES_MAX_COUNT),
                                  stf::Random(time(0)).getNum(game_model_settings::SURVIVAL_MOUSES_MIN_COUNT, game_model_settings::SURVIVAL_MOUSES_MAX_COUNT));
        return stf::smv::ModelBaseState::start;
    }

    stf::smv::ModelBaseState onNormalBtnClick(const stf::MouseRecord& mr)
    {
        model<GameModel>()->reset(game_model_settings::NORMAL_SNAKES_COUNT, game_model_settings::NORMAL_MOUSE_COUNT);
        return stf::smv::ModelBaseState::start;
    }

    stf::smv::ModelBaseState onExitBtnClick(const stf::MouseRecord& mr)
    {
        return stf::smv::ModelBaseState::exit;
    }
};

#endif // MENUVIEW_HPP
