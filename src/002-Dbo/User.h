#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>

namespace dbo = Wt::Dbo;

class User;
using AuthInfo = Wt::Auth::Dbo::AuthInfo<User>;

class UserRole
{
public:
  std::string name;
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
  std::string first_name;
  std::string last_name;
  std::string phone;
  bool darkMode;
  std::chrono::system_clock::time_point joinDate;

  dbo::weak_ptr<AuthInfo> authInfo;
  dbo::ptr<UserRole> role;

  template <class Action>
  void persist(Action &a)
  {
    dbo::hasOne(a, authInfo, "user");
    dbo::belongsTo(a, role, "user_role");
    dbo::field(a, first_name, "first_name");
    dbo::field(a, last_name, "last_name");
    dbo::field(a, phone, "phone");
    dbo::field(a, darkMode, "darkMode");
    dbo::field(a, joinDate, "joinDate");
  }
};
