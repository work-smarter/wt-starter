#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/Stylus.h"

RightPanel::RightPanel(Stylus *stylus)
    : BaseDialogPanel(stylus)
{
    addStyleClass("w-[450px] relative");

    setOffsets(0, Wt::Side::Top | Wt::Side::Right | Wt::Side::Bottom);
    auto content_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    contents()->addStyleClass("!bg-gray-700");
}
