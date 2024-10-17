#pragma once
#include "002-Dbo/Session.h"
#include "101-Stylus/Tables/XmlTemplate.h"
#include "101-Stylus/Tables/TemplateFile.h"
#include "101-Stylus/Tables/TemplateApp.h"
#include "101-Stylus/XMLBrain.h"

#include <Wt/WSignal.h>

class LeftPanel;
class RightPanel;
class EdditorPanel;
class SettingsPanel;
class QuickCommandsPanel;

class Stylus
{
public:
    Stylus(Session &session, Wt::WString app_name, Wt::WString templates_root_path);

    void readDefaultXmlFile(Wt::WString file_path);

    void writeDefaultFile(Wt::WString file_name, Wt::WString destination_file_path);
    void writeAppFile(Wt::WString app_name, Wt::WString file_name, Wt::WString destination_file_path);
    void readAppXmlFile(Wt::WString app_name, Wt::WString file_path);

    LeftPanel *left_panel_;
    RightPanel *right_panel_;
    EdditorPanel *edditor_panel_;
    SettingsPanel *settings_panel_;
    QuickCommandsPanel *quick_commands_panel_;

    Session &session_;
    Wt::WString templates_root_path_;
    Wt::WString default_folder_name = "default";

    void setXmlBrain(std::shared_ptr<XMLBrain> xml_brain);
    Wt::Signal<> &node_selected() { return node_selected_; }

    std::shared_ptr<XMLBrain> xml_brain_;

private:
    void processKeyEvent(Wt::WKeyEvent e);
    Wt::Signal<> node_selected_;

};