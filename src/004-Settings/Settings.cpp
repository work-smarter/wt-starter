#include "004-Settings/Settings.h"
#include <iomanip>
#include <sstream>
#include <chrono>
#include <ctime>

// std::string timePointToString(const std::chrono::system_clock::time_point &tp)
// {
//     std::time_t time = std::chrono::system_clock::to_time_t(tp);
//     std::tm *tm = std::localtime(&time);
//     std::ostringstream oss;
//     oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
//     return oss.str();
// }

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
    bindString("user-dark-mode", user_info->darkMode ? "dark" : "light");
    bindString("user-join-date", Wt::WDateTime(user_info->joinDate).toString("yyyy-MM-dd | hh:mm:ss"));

    t.commit();
}