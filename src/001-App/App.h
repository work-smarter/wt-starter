#pragma once
#include <Wt/WApplication.h>
#include <Wt/WStackedWidget.h>
// #include <Wt/WTemplate.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include "003-Auth/AuthWidget.h"
#include "002-Dbo/Session.h"
#include "003-Auth/AuthWidget.h"

class App : public Wt::WApplication
{
public:
    App(const Wt::WEnvironment &env);
    AuthWidget *auth_;
    Wt::WTemplate *root_temp_;
    Wt::WContainerWidget *root_content_;

private:
    Session session_;

    void createUi();
    void createHome();
    void createTest();
};