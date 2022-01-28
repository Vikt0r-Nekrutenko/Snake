#ifndef ENDVIEW_HPP
#define ENDVIEW_HPP

#include "smv/baseendview.hpp"
#include "model.hpp"
#include "sprite.hpp"

class EndView : public stf::smv::BaseEndView
{
public:
    EndView(stf::smv::BaseModel *model);

    void show(stf::Renderer& renderer) override;

private:
    stf::Sprite m_end = stf::Sprite("end.spr");

};

#endif // ENDVIEW_HPP
