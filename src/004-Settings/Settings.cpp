#include "004-Settings/Settings.h"
#include "002-Dbo/UserFormView.h"

Settings::Settings(Session &session) : session_(session)
{
    setTemplateText(Wt::WString::tr("starter.settings"));
    auto user = session_.login().user();

    bindString("user-id", user.id());
    bindString("user-email", user.email());

    dbo::Transaction t(session_);
    auto user_info = session_.find<User>().where("id = ?").bind(user.id()).resultValue();
    bindString("user-first-name", user_info->first_name);
    bindString("user-last-name", user_info->last_name);
    bindString("user-phone", user_info->phone);
    bindString("user-dark-mode", user_info->dark_mode ? "dark" : "light");
    bindString("user-join-date", Wt::WDateTime(user_info->join_date).toString("yyyy-MM-dd | hh:mm:ss"));

    t.commit();

    auto user_form = bindWidget("user-settings-form", std::make_unique<UserFormView>(session_));
}