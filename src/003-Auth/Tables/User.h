#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class User;
class CalendarEntry;

using AuthInfo = Wt::Auth::Dbo::AuthInfo<User>;

class UserRole
{
public:
  Wt::WString name;
  dbo::collection<dbo::ptr<User>> users;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, name, "name");
    dbo::hasMany(a, users, dbo::ManyToOne, "user_role");
  }
};

class User
{
public:
  Wt::WString first_name;
  Wt::WString last_name;
  Wt::WString phone;
  Wt::WString photo_url;
  bool dark_mode;
  Wt::WDateTime join_date;

  dbo::weak_ptr<AuthInfo> auth_info;
  dbo::ptr<UserRole> role;
  dbo::collection<dbo::ptr<CalendarEntry>> entries;

  dbo::collection<dbo::ptr<CalendarEntry>> entriesInRange(const Wt::WDate &from, const Wt::WDate &until) const;

  template <class Action>
  void persist(Action &a)
  {
    dbo::hasOne(a, auth_info, "user");
    dbo::belongsTo(a, role, "user_role");
    dbo::field(a, first_name, "first_name");
    dbo::field(a, last_name, "last_name");
    dbo::field(a, phone, "phone");
    dbo::field(a, dark_mode, "dark_mode");
    dbo::field(a, join_date, "join_date");
    dbo::field(a, photo_url, "photo_url");
    dbo::hasMany(a, entries, dbo::ManyToOne, "user");
  }
};
