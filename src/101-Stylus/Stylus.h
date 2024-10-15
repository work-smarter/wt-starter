#pragma once
#include "002-Dbo/Session.h"
#include "101-Stylus/Tables/XmlTemplate.h"
#include "101-Stylus/Tables/TemplateFile.h"
#include "101-Stylus/Tables/TemplateApp.h"

class LeftPanel;
class RightPanel;
class EdditorPanel;
class SettingsPanel;
class QuickCommandsPanel;

class Stylus
{
public:
    Stylus(Session &session, Wt::WString app_name);

    void readXmlFile(Wt::WString file_path);
    void readAppXmlFile(Wt::WString file_path, Wt::WString app_name);

    void writeFile(Wt::WString file_path, Wt::WString destination_file_path);
    void writeAppFile(Wt::WString app_name, Wt::WString file_path, Wt::WString destination_file_path);

private:
    Session &session_;

    LeftPanel *left_panel_;
    RightPanel *right_panel_;
    EdditorPanel *edditor_panel_;
    SettingsPanel *settings_panel_;
    QuickCommandsPanel *quick_commands_panel_;
    void processKeyEvent(Wt::WKeyEvent e);
};