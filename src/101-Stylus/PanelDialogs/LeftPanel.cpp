#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/Stylus.h"

LeftPanel::LeftPanel(Stylus *stylus)
    : BaseDialogPanel(stylus)
{
    addStyleClass("w-[380px] relative");
    setOffsets(0, Wt::Side::Left | Wt::Side::Bottom | Wt::Side::Top);
    auto content_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    contents()->addStyleClass("!bg-gray-800");
}

void LeftPanel::createTree(std::shared_ptr<XMLBrain> xml_brain)
{
    contents()->clear();
    contents()->addWidget(std::make_unique<PTree>(xml_brain, xml_brain->message_node_));
}
