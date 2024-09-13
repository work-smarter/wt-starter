#include "App.h"

App::App(const Wt::WEnvironment &env)
    : 
    WApplication(env)
{
    setTitle("Wt Starter");
    
    // messageResourceBundle().use("../xml-templates/overide-wt/auth");
    // messageResourceBundle().use("../xml-templates/overide-wt/auth_strings");

    // CSS
    require("https://cdn.tailwindcss.com");

    useStyleSheet("static/css/tailwind-out.css");
    // JSs
    require(docRoot() + "/static/js/utils.js");

    root()->addWidget(std::make_unique<Wt::WText>("Wt Starter App"));

}