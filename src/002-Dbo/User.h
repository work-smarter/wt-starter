#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class User;
using AuthInfo = Wt::Auth::Dbo::AuthInfo<User>;

class UserRole
{
public:
  Wt::WString name;
  dbo::collection<dbo::ptr<User>> users;

  template <class Action>
  void persist(Action &a)
  {
    dbo::hasMany(a, users, dbo::ManyToOne, "user_role");
    dbo::field(a, name, "name");
  }
};

class User
{
public:
  Wt::WString first_name;
  Wt::WString last_name;
  Wt::WString phone;
  Wt::WString photo;
  bool dark_mode;
  // std::chrono::system_clock::time_point join_date;
  Wt::WDateTime join_date;

  dbo::weak_ptr<AuthInfo> auth_info;
  dbo::ptr<UserRole> role;

  template <class Action>
  void persist(Action &a)
  {
    dbo::hasOne(a, auth_info, "user");
    dbo::belongsTo(a, role, "user_role");
    dbo::field(a, first_name, "first_name");
    dbo::field(a, last_name, "last_name");
    dbo::field(a, phone, "phone");
    dbo::field(a, dark_mode, "darkMode");
    dbo::field(a, join_date, "joinDate");
    dbo::field(a, photo, "photo");
  }
};
