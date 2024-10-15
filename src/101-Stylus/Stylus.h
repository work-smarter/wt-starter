#pragma once
#include "002-Dbo/Session.h"
#include "101-Stylus/Tables/XmlTemplate.h"
#include "101-Stylus/Tables/TemplateFile.h"
#include "101-Stylus/Tables/TemplateApp.h"

class Stylus
{
public:
    Stylus(Session &session, Wt::WString app_name);

    void readOverideWtXmlFile(Wt::WString file_path);
    void readXmlFile(Wt::WString file_path, Wt::WString app_name);

private:
    Session &session_;
};