#pragma once
#include "002-Dbo/Session.h"
#include "101-Stylus/Tables/XmlTemplate.h"
#include "101-Stylus/Tables/TemplateFile.h"
#include "101-Stylus/Tables/TemplateApp.h"

class Stylus
{
public:
    Stylus(Session &session);

private:
    Session &session_;
};