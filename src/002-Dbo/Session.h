#pragma once
#include <Wt/Auth/Login.h>
#include <Wt/Auth/Dbo/UserDatabase.h>
#include <Wt/Dbo/Session.h>
#include <Wt/Dbo/ptr.h>
#include <Wt/WString.h>

#include "003-Auth/Tables/User.h"
#include "005-Calendar/Tables/CalendarEntry.h"

#include "101-Stylus/Tables/XmlTemplate.h"
#include "101-Stylus/Tables/TemplateFile.h"
#include "101-Stylus/Tables/TemplateApp.h"

using namespace Wt;

namespace dbo = Wt::Dbo;

using UserDatabase = Wt::Auth::Dbo::UserDatabase<AuthInfo>;

class Session : public dbo::Session
{
public:
    explicit Session(const std::string &sqliteDb);

    dbo::ptr<User> user();
    dbo::ptr<User> user(const Auth::User &user);

    Auth::AbstractUserDatabase &users();
    Auth::Login &login() { return login_; }

    static const Auth::AuthService &auth();
    static const Auth::PasswordService &passwordAuth();
    static std::vector<const Auth::OAuthService *> oAuth();

private:
    std::unique_ptr<UserDatabase> users_;
    Auth::Login login_;

    void configureAuth();
    void createInitialData();
};