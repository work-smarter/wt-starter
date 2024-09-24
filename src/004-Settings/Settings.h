#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WTemplate.h>

#include "002-Dbo/Session.h"
#include "002-Dbo/User.h"

#include <Wt/WDateTime.h>

class Settings : public Wt::WTemplate
{
public:
    Settings(Session &session);

private:
    Session &session_;
};