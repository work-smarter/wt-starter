#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "101-Stylus/XMLBrain.h"
#include "101-Stylus/Preview/PTree.h"

class LeftPanel : public BaseDialogPanel
{
public:
    LeftPanel(Stylus *stylus_brain);

    void createTree(std::shared_ptr<XMLBrain> xml_brain);
    
private:
    XMLBrain *xml_brain_;
};