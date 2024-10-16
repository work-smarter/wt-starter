#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>

class EdditorPanel : public BaseDialogPanel
{
public:
    EdditorPanel(Stylus *stylus_brain);

private:
    std::shared_ptr<Wt::WButtonGroup> display_set_group_;
};