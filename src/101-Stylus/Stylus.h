#pragma once
#include "002-Dbo/Session.h"
#include "101-Stylus/Tables/XmlTemplate.h"
#include "101-Stylus/Tables/TemplateFile.h"
#include "101-Stylus/Tables/TemplateApp.h"

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
};