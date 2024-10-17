#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "101-Stylus/XMLBrain.h"

#include <Wt/WButtonGroup.h>
#include <Wt/WRadioButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>

class EdditorPanel : public BaseDialogPanel
{
public:
    EdditorPanel(Stylus *stylus_brain);

private:
    std::shared_ptr<Wt::WButtonGroup> display_set_group_;

    Wt::WContainerWidget *header_wrapper_;
    Wt::WContainerWidget *content_wrapper_;

    void createDefaultDisplay();
    void createAppDisplay(Wt::WString app_name);

    void createFileTemplates(std::vector<XmlDboRecord> xml_temp_objects, Wt::WContainerWidget *wrapper);
};