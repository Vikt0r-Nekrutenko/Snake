#ifndef MENUVIEW_HPP
#define MENUVIEW_HPP

#include "smv/basemenuview.hpp"
#include "random.hpp"
#include "sprite.hpp"

class MenuView : public stf::smv::BaseMenuView
{
public:
    MenuView(stf::smv::BaseModel *model, const stf::Vec2d& wndSize);

    void show(stf::Renderer &renderer) override;

    stf::smv::ModelBaseState onStartBtnClick(const stf::MouseRecord& mr);

    stf::smv::ModelBaseState onSurvivalBtnClick(const stf::MouseRecord& mr);

    stf::smv::ModelBaseState onNormalBtnClick(const stf::MouseRecord& mr);

    stf::smv::ModelBaseState onExitBtnClick(const stf::MouseRecord& mr);

private:
    stf::Sprite     m_bgrnd;
};

#endif // MENUVIEW_HPP
