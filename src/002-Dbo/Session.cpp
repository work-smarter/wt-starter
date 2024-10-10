#include "002-Dbo/Session.h"
#include "002-Dbo/Tables/User.h"
#include "002-Dbo/UserFormModel.h"

#include <Wt/Auth/Dbo/AuthInfo.h>

// #include <Wt/Dbo/backend/Sqlite3.h>
#include <Wt/Dbo/backend/Postgres.h>

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/PasswordService.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/GoogleService.h>
#include <Wt/Auth/FacebookService.h>

#include <iostream>

using namespace Wt;

namespace
{
  Wt::Auth::AuthService myAuthService;
  Wt::Auth::PasswordService myPasswordService(myAuthService);
  std::vector<std::unique_ptr<Wt::Auth::OAuthService>> myOAuthServices;
}

Session::Session(const std::string &sqliteDb)
{
  // auto connection = std::make_unique<Dbo::backend::Sqlite3>(sqliteDb);
  std::string postgres_conn_str = "host=postgres dbname=postgres user=postgres password=mysecretpassword";
  auto connection = std::make_unique<Dbo::backend::Postgres>(postgres_conn_str.c_str());
  setConnection(std::move(connection));

  mapClass<CalendarEntry>("calendar_entry");
  mapClass<UserRole>("user_role");
  mapClass<User>("user");
  mapClass<AuthInfo>("auth_info");
  mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  mapClass<AuthInfo::AuthTokenType>("auth_token");

  try
  {
    createTables();
    std::cerr << "Created database.\n";
  }
  catch (Wt::Dbo::Exception &e)
  {
    std::cerr << e.what() << '\n';
    std::cerr << "Using existing database\n";
  }

  users_ = std::make_unique<UserDatabase>(*this);
  configureAuth();

  dbo::Transaction t(*this);
  auto user_role = find<UserRole>().where("name = ?").bind("admin");
  if (!user_role.resultValue())
    createInitialData();
  t.commit();
}

void Session::createInitialData()
{
  // dbo::Transaction t(*this);

  // create user roles
  auto admin_role = add(std::make_unique<UserRole>());
  admin_role.modify()->name = "admin";

  auto user_role = add(std::make_unique<UserRole>());
  user_role.modify()->name = "user";

  // Create a new User in User table
  std::unique_ptr<User> new_user_ptr{new User()};
  new_user_ptr->first_name = "Alexandru";
  new_user_ptr->last_name = "Croitoriu";
  new_user_ptr->phone = "0771133255";
  new_user_ptr->dark_mode = false;
  new_user_ptr->role = admin_role;
  new_user_ptr->join_date = Wt::WDateTime::currentDateTime();

  dbo::ptr<User> dbo_user = this->add(std::move(new_user_ptr));

  auto new_user = users_->registerNew();
  // new_user.setEmail("admin@gmail.com");
  new_user.setIdentity(Wt::Auth::Identity::LoginName, "admin");
  myPasswordService.updatePassword(new_user, "asdfghj1");

  auto dbo_user_info = users_->find(new_user);
  dbo_user_info.modify()->setUser(dbo_user);

  // t.commit();
}

void Session::configureAuth()
{
  myAuthService.setAuthTokensEnabled(true, "logincookie");
  myAuthService.setEmailVerificationEnabled(false);
  myAuthService.setEmailVerificationRequired(false);
  // myAuthService.setAuthTokenValidity(300);
  myAuthService.setIdentityPolicy(Wt::Auth::IdentityPolicy::LoginName);
  // myAuthService.setIdentityPolicy(Wt::Auth::IdentityPolicy::LoginName);

  auto verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
  verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(7));
  myPasswordService.setVerifier(std::move(verifier));
  myPasswordService.setAttemptThrottlingEnabled(true);
  myPasswordService.setStrengthValidator(
      std::make_unique<Wt::Auth::PasswordStrengthValidator>());

  if (Wt::Auth::GoogleService::configured())
  {
    myOAuthServices.push_back(std::make_unique<Wt::Auth::GoogleService>(myAuthService));
  }

  if (Wt::Auth::FacebookService::configured())
  {
    myOAuthServices.push_back(std::make_unique<Wt::Auth::FacebookService>(myAuthService));
  }

  for (const auto &oAuthService : myOAuthServices)
  {
    oAuthService->generateRedirectEndpoint();
  }
}

dbo::ptr<User> Session::user()
{
  if (login_.loggedIn())
    return user(login_.user());
  else
    return dbo::ptr<User>();
}

dbo::ptr<User> Session::user(const Auth::User &authUser)
{
  dbo::ptr<AuthInfo> authInfo = users_->find(authUser);

  dbo::ptr<User> user = authInfo->user();

  if (!user)
  {
    user = add(std::make_unique<User>());
    authInfo.modify()->setUser(user);
  }

  return user;
}

Wt::Auth::AbstractUserDatabase &Session::users()
{
  return *users_;
}

const Wt::Auth::AuthService &Session::auth()
{
  return myAuthService;
}

const Wt::Auth::PasswordService &Session::passwordAuth()
{
  return myPasswordService;
}

std::vector<const Wt::Auth::OAuthService *> Session::oAuth()
{
  std::vector<const Auth::OAuthService *> result;
  result.reserve(myOAuthServices.size());
  for (const auto &auth : myOAuthServices)
  {
    result.push_back(auth.get());
  }
  return result;
}
