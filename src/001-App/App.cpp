#include "App.h"
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>

App::App(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "../dbo.db")

{
    setTitle("Wt Starter");

    messageResourceBundle().use("../xml-templates/overide-wt/auth");
    messageResourceBundle().use("../xml-templates/overide-wt/auth_strings");

    // CSS
    require("https://cdn.tailwindcss.com");

    useStyleSheet("static/css/tailwind-out.css");
    // JSs
    require(docRoot() + "/static/js/utils.js");

    stack_ = root()->addWidget(std::make_unique<Wt::WStackedWidget>());

    auto authWidget = std::make_unique<AuthWidget>(session_);
    authWidget->model()->addPasswordAuth(&Session::passwordAuth());
    authWidget->model()->addOAuth(Session::oAuth());
    authWidget->setRegistrationEnabled(false);

    auth_ = stack_->addWidget(std::move(authWidget));
    root_ = stack_->addWidget(std::make_unique<Wt::WContainerWidget>());

    auth_->login().changed().connect([=]
                                     {
        if (auth_->login().loggedIn()) {
            stack_->setCurrentWidget(root_);
            createUi();
        }else {
            stack_->setCurrentWidget(auth_);
        } });

    auth_->processEnvironment();
}

void App::createUi()
{
    root_->clear();
    root_->addWidget(std::make_unique<Wt::WText>("Welcome to Wt Starter App"));
}
