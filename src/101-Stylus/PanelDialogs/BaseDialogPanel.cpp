#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "101-Stylus/Stylus.h"

BaseDialogPanel::BaseDialogPanel(Stylus *stylus)
    : stylus_(stylus)
{
    titleBar()->children()[0]->removeFromParent();
    setStyleClass("!border-0 shadow-lg rounded-xl overflow-x-visible");
    titleBar()->hide();
    titleBar()->setStyleClass("p-0 bg-gray-300 flex items-center overflow-x-visible h-[40px]");
    contents()->setStyleClass("h-full bg-gray-200 overflow-y-auto overflow-x-visible");
    setModal(false);
    setResizable(true);
    setMovable(false);
}