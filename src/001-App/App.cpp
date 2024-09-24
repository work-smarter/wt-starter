#include "App.h"
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>

App::App(const Wt::WEnvironment &env)
    : WApplication(env),
      session_(appRoot() + "../dbo.db")

{
    setTitle("Wt Starter");

    messageResourceBundle().use("../xml-templates/app/app");

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
    authWidget->setRegistrationEnabled(false);

    auth_ = root()->addWidget(std::move(authWidget));
    root_temp_ = root()->addWidget(std::make_unique<Wt::WTemplate>(Wt::WString::tr("starter.app")));

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
        }else {
            setInternalPath("/home");
            createHome();
        } });

    auth_->processEnvironment();
}

void App::createUi()
{

    auto navbar = root_temp_->bindWidget("navbar", std::make_unique<Wt::WTemplate>(Wt::WString::tr("starter.navbar")));
    navbar->bindString("title", "Wt Starter");
    auto home_link = navbar->bindWidget("home-link", std::make_unique<Wt::WText>("Home"));
    auto test_link = navbar->bindWidget("test-link", std::make_unique<Wt::WText>("Test"));
    auto user_menu_btn = navbar->bindWidget("user-menu", std::make_unique<Wt::WPushButton>());
    user_menu_btn->setIcon(Wt::WLink("static/util/user-icon.png"));
    // user_menu_btn->setStyleClass("");
    // auto user_icon = user_menu_btn->addWidget(std::make_unique<Wt::WImage>(Wt::WLink("static/util/user-icon.png")));
    // user_icon->setAlternateText("User Icon");
    // user_icon->setStyleClass("");

    home_link->clicked().connect([=]
                                 { setInternalPath("/home");
                                    internalPathChanged().emit("/home"); });
    test_link->clicked().connect([=]
                                 { setInternalPath("/test"); 
                                    internalPathChanged().emit("/test"); });

    auto popup_meun = std::make_unique<Wt::WPopupMenu>();
    popup_meun->setAutoHide(true, 1000);

    auto popup_menu_item_1 = popup_meun->addItem("popup-1", std::make_unique<Wt::WText>("popup page 1"));
    popup_menu_item_1->setStyleClass("p-2 px-4 cursor-pointer hover:bg-gray-200");
    popup_menu_item_1->setPathComponent("popup-1");

    auto popup_menu_item_2 = popup_meun->addItem("popup-2", std::make_unique<Wt::WText>("popup page 2"));
    popup_menu_item_2->setStyleClass("p-2 px-4 cursor-pointer hover:bg-gray-200");
    popup_menu_item_2->setPathComponent("popup-2");

    auto logout_menu_item = popup_meun->addItem("logout");
    logout_menu_item->setStyleClass("p-2 px-4 cursor-pointer hover:bg-gray-200");
    logout_menu_item->clicked().connect([=]
                                        { session_.login().logout(); });

    user_menu_btn->setMenu(std::move(popup_meun));

    internalPathChanged()
        .emit(internalPath());

    // auto path = Wt::WApplication::instance()->internalPath();
    // if (path.compare("/") == 0)
    // {
    //     setInternalPath("/home");
    //     internalPathChanged().emit("/home");
    // }
    // else
    // {
    //     internalPathChanged().emit(path);
    // }
}

void App::createHome()
{
    root_content_ = root_temp_->bindWidget("content", std::make_unique<Wt::WContainerWidget>());
    root_content_->addWidget(std::make_unique<Wt::WText>("Home Page"));
}

void App::createTest()
{
    root_content_ = root_temp_->bindWidget("content", std::make_unique<Wt::WContainerWidget>());
    root_content_->addWidget(std::make_unique<Wt::WText>("Test Page"));
}
