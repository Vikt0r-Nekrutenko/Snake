#include "menuview.hpp"
#include "random.hpp"

MenuView::MenuView(GameModel *model)
    : View(model),
      m_menu("menu.spr"),
      m_bgrnd("bgrnd.spr")
{}

void MenuView::show(stf::Renderer &renderer, const stf::Vec2d &camera)
{
    m_menu.show(renderer, renderer.Size / 2 - m_menu.Size() / 2);
    m_bgrnd.show(renderer, renderer.Size / 2 - m_bgrnd.Size() / 2 - stf::Vec2d(0, 7));
}

Signal MenuView::keyEvents(const int key)
{
    switch (key) {
    case 'w':
        m_menu.prev();
        if(m_selector == 0) {
            m_selector = m_menu.frames()-1;
        } else {
            --m_selector;
        }
        break;

    case 's':
        m_menu.next();
        if(m_selector == m_menu.frames()-1) {
            m_selector = 0;
        } else {
            ++m_selector;
        }
        break;

    case ' ':
        if (m_selector == 0) {
            return Signal::start;
        } else if (m_selector == 1) {
            m_model->reset(game_model_settings::NORMAL_SNAKES_COUNT, game_model_settings::NORMAL_MOUSE_COUNT);
            return Signal::normal;
        } else if (m_selector == 2) {
            m_model->reset(stf::Random(time(0)).getNum(game_model_settings::SURVIVAL_SNAKES_MIN_COUNT, game_model_settings::SURVIVAL_SNAKES_MAX_COUNT),
                           stf::Random(time(0)).getNum(game_model_settings::SURVIVAL_MOUSES_MIN_COUNT, game_model_settings::SURVIVAL_MOUSES_MAX_COUNT));
            return Signal::survival;
        } else if (m_selector == m_menu.frames() - 1) {
            return Signal::end;
        }
    }
    return Signal::none;
}

