#include "App.h"
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include "004-Settings/Settings.h"

#include "100-Utils/AwsConnect.h"

#include <Wt/WCalendar.h>
#include "005-Calendar/Calendar.h"

App::App(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "../dbo.db"),
      stylus_(session_)

{
    setTitle("Starter App");

    messageResourceBundle().use("../xml-templates/app/app");
    messageResourceBundle().use("../xml-templates/app/inputs");
    messageResourceBundle().use("../xml-templates/app/strings");
    messageResourceBundle().use("../xml-templates/app/calendar");

    messageResourceBundle().use("../xml-templates/overide-wt/auth");
    messageResourceBundle().use("../xml-templates/overide-wt/auth_strings");

    // CSS
    require("https://cdn.tailwindcss.com");

    useStyleSheet("static/css/tailwind-out.css");
    // JSs
    require(docRoot() + "/static/js/utils.js");

    // stack_ = root()->addWidget(std::make_unique<Wt::WStackedWidget>());

    auto authWidget = std::make_unique<AuthWidget>(session_);
    authWidget->model()->addPasswordAuth(&Session::passwordAuth());
    authWidget->model()->addOAuth(Session::oAuth());
    authWidget->setRegistrationEnabled(true);

    auth_ = root()->addWidget(std::move(authWidget));
    root_temp_ = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("starter.app")));
    root_temp_->bindWidget("navbar", std::make_unique<Wt::WContainerWidget>())->setStyleClass("bg-gray-800 text-white p-4");

    auth_->login().changed().connect([=]
                                     {
        if (auth_->login().loggedIn()) {
            auth_->hide();
            createUi();
        }else {
            auth_->show();
        } });

    internalPathChanged().connect([=](std::string path)
                                  {
        std::cout << "\nPath: " << path << std::endl;
        if (path == "/home") {
            createHome();
        } else if (path == "/test") {
            createTest();
        } else if (path == "/profile") {
            createProfile();
        } else if (path == "/settings") {
            createSettings();
        }else {
            setInternalPath("/home");
            createHome();
        } });

    auth_->processEnvironment();
}

void App::createUi()
{
    auto navbar = root_temp_->bindWidget("navbar", std::make_unique<Wt::WTemplate>(Wt::WString::tr("starter.navbar")));
    navbar->bindString("title", "Starter App");
    auto home_link = navbar->bindWidget("home-link", std::make_unique<Wt::WText>("Home"));
    auto test_link = navbar->bindWidget("test-link", std::make_unique<Wt::WText>("Test"));
    auto user_menu_btn = navbar->bindWidget("user-menu", std::make_unique<Wt::WPushButton>());
    user_menu_btn->setIcon(Wt::WLink("static/util/user-icon.png"));

    home_link->clicked().connect([=]
                                 { setInternalPath("/home");
                                    internalPathChanged().emit("/home"); });
    test_link->clicked().connect([=]
                                 { setInternalPath("/test"); 
                                    internalPathChanged().emit("/test"); });

    auto popup_meun = std::make_unique<Wt::WPopupMenu>();
    popup_meun->setAutoHide(true, 1000);

    auto profile_link = popup_meun->addItem("Profile");
    profile_link->setStyleClass("p-2 px-4 cursor-pointer hover:bg-gray-200");
    profile_link->clicked().connect([=]
                                    { setInternalPath("/profile");
                                      internalPathChanged().emit("/profile"); });

    auto settings_link = popup_meun->addItem("Settings");
    settings_link->setStyleClass("p-2 px-4 cursor-pointer hover:bg-gray-200");
    settings_link->clicked().connect([=]
                                     { setInternalPath("/settings");
                                      internalPathChanged().emit("/settings"); });

    auto logout_menu_item = popup_meun->addItem("Logout");
    logout_menu_item->setStyleClass("p-2 px-4 cursor-pointer hover:bg-gray-200");
    logout_menu_item->clicked().connect([=]
                                        { session_.login().logout(); });

    user_menu_btn->setMenu(std::move(popup_meun));

    internalPathChanged()
        .emit(internalPath());
}

void App::createHome()
{
    root_content_ = root_temp_->bindWidget("content", std::make_unique<Wt::WContainerWidget>());
    root_content_->addWidget(std::make_unique<Wt::WText>("Home Page"));
    auto test_btn = root_content_->addWidget(std::make_unique<Wt::WPushButton>("Test"));
    test_btn->setStyleClass("btn-green");
    test_btn->clicked().connect([=]
                                {
                                    // AwsConnect aws;
                                    // // aws.displayBuckets();
                                    // // auto result_url = aws.sendFile(appRoot() + "../image.png", "image.png");
                                    // // auto image = root_content_->addWidget(std::make_unique<Wt::WImage>(result_url));

                                    // auto result = aws.deleteFile("starterApp/wt9aTGKF/1/profile.jpg");
                                    // // auto result = aws.deleteFile("https://aipro-storage.s3.eu-north-1.amazonaws.com/starterApp/wt9aTGKF/1/profile.jpg");
                                    // if (result) {
                                    //     std::cout << "\n File deleted \n";
                                    // } else {
                                    //     std::cout << "\n File not deleted \n";
                                    // }
                                });

    Wt::WCalendar *c1 = root_content_->addNew<Wt::WCalendar>();
    Calendar *c2 = root_content_->addNew<Calendar>(session_.user());
}

void App::createTest()
{
    root_content_ = root_temp_->bindWidget("content", std::make_unique<Wt::WContainerWidget>());
    root_content_->addWidget(std::make_unique<Wt::WText>("Test Page"));
}

void App::createProfile()
{
    root_content_ = root_temp_->bindWidget("content", std::make_unique<Wt::WContainerWidget>());
    root_content_->addWidget(std::make_unique<Wt::WText>("Profile Page"));
}

void App::createSettings()
{
    root_content_ = root_temp_->bindWidget("content", std::make_unique<Wt::WContainerWidget>());
    root_content_->addWidget(std::make_unique<Settings>(session_));
}
