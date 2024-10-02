#include "004-Settings/Settings.h"
#include "002-Dbo/UserFormView.h"

#include <Wt/Auth/Identity.h>

Settings::Settings(Session &session) : session_(session)
{
    setTemplateText(Wt::WString::tr("starter.settings"));
    auto user = session_.login().user();

    bindString("user-id", user.id());
    bindString("user-email", user.email());

    dbo::Transaction t(session_);
    // auto user_info = session_.find<User>().where("id = ?").bind(user.id()).resultValue();
    // bindString("user-first-name", user_info->first_name);
    bindString("user-user-name", session_.login().user().identity(Wt::Auth::Identity::LoginName));
    bindString("user-first-name", session_.user()->first_name);
    bindString("user-last-name", session_.user()->last_name);
    bindString("user-phone", session_.user()->phone);
    bindString("user-dark-mode", session_.user()->dark_mode ? "dark" : "light");
    bindString("user-join-date", Wt::WDateTime(session_.user()->join_date).toString("yyyy-MM-dd | hh:mm:ss"));

    t.commit();

    auto user_form = bindWidget("user-settings-form", std::make_unique<UserFormView>(session_));
}