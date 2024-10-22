#pragma once
#include <Wt/WApplication.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WImage.h>
#include <Wt/WLink.h>
#include <Wt/WPopupMenu.h>
// #include <Wt/WTemplate.h>

#include <Wt/Auth/AuthWidget.h>
#include <Wt/Auth/PasswordService.h>

#include "003-Auth/AuthWidget.h"
#include "002-Dbo/Session.h"
#include "003-Auth/AuthWidget.h"
#include "101-Stylus/Stylus.h"

class App : public Wt::WApplication
{
public:
    App(const Wt::WEnvironment &env);
    AuthWidget *auth_;
    Wt::WTemplate *root_temp_;
    Wt::WContainerWidget *root_content_;

    static App *app()
    {
        return (App *)WApplication::instance();
    }

    Session session_;
    Stylus stylus_;
    // std::shared_ptr<Stylus> stylus_;

private:
    void createUi();
    void createHome();
    void createProfile();
    void createSettings();
    void createTest();
};