#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

class Stylus;

struct StylusState
{
    bool left_active_ = false;
    bool right_active_ = false;
    bool edditor_active_ = false;
    bool quick_commands_active_ = false;
    bool settings_active_ = false;
};

class SettingsPanel : public BaseDialogPanel
{
public:
    SettingsPanel(Stylus *stylus);
    std::string radio_checkbox_btn_styles_;

    StylusState stylus_state_;

    Wt::WCheckBox *left_toggler_;
    Wt::WCheckBox *right_toggler_;
    Wt::WCheckBox *quick_commands_toggler_;
    Wt::WCheckBox *edditor_toggler_;

    // RIGHT_PANEL_MODE right_dialog_panels_mode_;

    // void createRefreshSessionsWidget();

    void createRightPanelSettings(Wt::WContainerWidget *wrapper);
    void createLeftPanelSettings(Wt::WContainerWidget *wrapper);
    void createEdditorPanelSettings(Wt::WContainerWidget *wrapper);
    void createQuickCommandsPanelSettings(Wt::WContainerWidget *wrapper);

    void readStateFromXmlFile();

    // void toggleStylusActive();

    void toggleRightDialogActive();
    void toggleLeftDialogActive();
    void toggleEdditorDialogActive();
    void toggleQuickCommandsDialogActive();
    void toggleSettingsDialogActive();

    // void togglefilesManagerDialogActive();
    // void togglefilesManagerLeftMenuActive();

    // void setFileManagerFoldersTreeState();

private:
    const char *xml_file_path = "stylus_config.xml";

    tinyxml2::XMLDocument *settings_xml_doc_;
    tinyxml2::XMLElement *left_xml_node_;
    tinyxml2::XMLElement *right_xml_node_;
    tinyxml2::XMLElement *edditor_xml_node_;
    tinyxml2::XMLElement *quick_commands_xml_node_;
    tinyxml2::XMLElement *settings_xml_node_;
};