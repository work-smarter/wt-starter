#include "002-Dbo/UserFormModel.h"
#include "002-Dbo/User.h"
#include "002-Dbo/Session.h"
#include "002-Dbo/Validators.h"

#include <Wt/WValidator.h>
#include <Wt/WRegExpValidator.h>

const WFormModel::Field
    UserFormModel::USER_NAME = "user-name",
    UserFormModel::FIRST_NAME = "first-name",
    UserFormModel::LAST_NAME = "last-name",
    UserFormModel::PHONE = "phone",
    UserFormModel::PHOTO = "photo";

UserFormModel::UserFormModel(Session &session)
    : WFormModel(),
      session_(session)
{
  addField(USER_NAME, WString::tr("Wt.Auth.user-name-info"));
  addField(FIRST_NAME, WString::tr("Wt.Auth.first-name-info"));
  addField(LAST_NAME, WString::tr("Wt.Auth.first-name-info"));
  addField(PHONE, WString::tr("Wt.Auth.phone-info"));
  addField(PHOTO, WString::tr("App.photo-info"));

  setValidator(USER_NAME, createNameValidator());
  setValidator(FIRST_NAME, createNameValidator());
  setValidator(LAST_NAME, createNameValidator());
  setValidator(PHONE, createPhoneValidator());
}

void UserFormModel::save(const Auth::User &user)
{
  Dbo::ptr<User> dbo_user = session_.user(user);
  dbo_user.modify()->first_name = valueText(FIRST_NAME).toUTF8();
  dbo_user.modify()->last_name = valueText(LAST_NAME).toUTF8();
  dbo_user.modify()->phone = valueText(PHONE).toUTF8();
  // dbo_user.modify()->join_date = Wt::WDateTime::currentDateTime();
  dbo_user.modify()->dark_mode = false;
  dbo_user.modify()->role = session_.find<UserRole>().where("name = ?").bind("user").resultValue();
}

void UserFormModel::saveUserName(const Auth::User &user, const std::string &user_name)
{
  std::cout << "\n ------------------ UserFormModel::saveUserName: " << user_name << std::endl;
  Dbo::Transaction t(session_);

  Dbo::ptr<User> dbo_user = session_.user(user);
  auto user_identity = dbo_user->auth_info->authIdentities().front();
  user_identity.modify()->setIdentity(user_name);
  t.commit();
}

void UserFormModel::saveFirstName(const Auth::User &user, const std::string &first_name)
{
  std::cout << "\n ------------------ UserFormModel::saveFirstName: " << first_name << std::endl;
  Dbo::Transaction t(session_);

  Dbo::ptr<User> dbo_user = session_.user(user);
  dbo_user.modify()->first_name = first_name;

  t.commit();
}

void UserFormModel::saveLastName(const Auth::User &user, const std::string &last_name)
{
  std::cout << "\n ------------------ UserFormModel::saveLastName: " << last_name << std::endl;
  Dbo::Transaction t(session_);

  Dbo::ptr<User> dbo_user = session_.user(user);
  dbo_user.modify()->last_name = last_name;

  t.commit();
}

void UserFormModel::savePhone(const Auth::User &user, const std::string &phone)
{
  std::cout << "\n ------------------ UserFormModel::savePhone: " << phone << std::endl;
  Dbo::Transaction t(session_);

  Dbo::ptr<User> dbo_user = session_.user(user);
  dbo_user.modify()->phone = phone;

  t.commit();
}

void UserFormModel::savePhoto(const Auth::User &user, const std::string &photo_path)
{
  std::cout << "\n ------------------ UserFormModel::savePhoto: " << photo_path << std::endl;
  Dbo::Transaction t(session_);

  Dbo::ptr<User> dbo_user = session_.user(user);
  dbo_user.modify()->photo = photo_path;

  t.commit();
}