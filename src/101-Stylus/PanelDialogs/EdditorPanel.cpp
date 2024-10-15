#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/Stylus.h"

EdditorPanel::EdditorPanel(Stylus *stylus)
    : BaseDialogPanel(stylus)
{
    // contents()->addStyleClass("!text-black flex border-x border-solid border-gray-400");
    // titleBar()->addStyleClass("!text-black");
    setOffsets(0, Wt::Side::Top | Wt::Side::Bottom);
    setOffsets(450, Wt::Side::Right);
    setOffsets(380, Wt::Side::Left);
    auto content_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
}
