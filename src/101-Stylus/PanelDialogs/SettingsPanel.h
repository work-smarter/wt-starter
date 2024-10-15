#pragma once
#include "101-Stylus/PanelDialogs/BaseDialogPanel.h"

class Stylus;

struct StylusState
{
    bool stylus_active_;

    bool left_active_;
    bool right_active_;
    bool edditor_active_;
    bool settings_active_;
    // bool quick_commands_active_;
    bool files_manager_active_;
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
    Wt::WCheckBox *files_manager_toggler_;

    // BasePanelMode right_dialog_panels_mode_;

    // void createRefreshSessionsWidget();

    // void createRightPanelSettings(Wt::WContainerWidget *wrapper);
    // void createLeftPanelSettings(Wt::WContainerWidget *wrapper);
    // void createFilesManagerPanelSettings(Wt::WContainerWidget *wrapper);
    // void createQuickCommandsPanelSettings(Wt::WContainerWidget *wrapper);

    // void readDataFromXml();

    // void toggleStylusActive();

    // void toggleSettingsPanelActive();
    // void toggleRightDialogActive();
    // void toggleLeftDialogActive();
    // void toggleQuickCommandsDialogActive();

    // void togglefilesManagerDialogActive();
    // void togglefilesManagerLeftMenuActive();

    // void setFileManagerFoldersTreeState();

private:
};