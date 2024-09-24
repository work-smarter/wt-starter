#include "002-Dbo/UserDetailsModel.h"
#include "002-Dbo/User.h"
#include "002-Dbo/Session.h"

#include <Wt/WValidator.h>

const WFormModel::Field
    UserDetailsModel::first_name = "first-name",
    UserDetailsModel::last_name = "last-name",
    UserDetailsModel::phone = "phone";

UserDetailsModel::UserDetailsModel(Session &session)
    : WFormModel(),
      session_(session)
{
  addField(first_name, WString::tr("first-name"));
  addField(last_name, WString::tr("last-name"));
  addField(phone, WString::tr("phone"));

  // const std::shared_ptr<Wt::WValidator> validator = std::make_shared<WValidator>(true);

  // setValidator(first_name, validator);
  // setValidator(last_name, validator);
  // setValidator(phone, validator);
}

void UserDetailsModel::save(const Auth::User &authUser)
{
  Dbo::ptr<User> user = session_.user(authUser);
  user.modify()->first_name = valueText(first_name).toUTF8();
  user.modify()->last_name = valueText(last_name).toUTF8();
  user.modify()->phone = valueText(phone).toUTF8();
}

void UserDetailsModel::saveFirstName(const Auth::User &authUser, const std::string &first_name)
{
  Dbo::ptr<User> user = session_.user(authUser);
  user.modify()->first_name = first_name;
}

void UserDetailsModel::saveLastName(const Auth::User &authUser, const std::string &last_name)
{
  Dbo::ptr<User> user = session_.user(authUser);
  user.modify()->last_name = last_name;
}

void UserDetailsModel::savePhone(const Auth::User &authUser, const std::string &phone)
{
  Dbo::ptr<User> user = session_.user(authUser);
  user.modify()->phone = phone;
}
