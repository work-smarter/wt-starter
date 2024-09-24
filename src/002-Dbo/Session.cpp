#include "002-Dbo/Session.h"
#include "002-Dbo/User.h"
#include <Wt/Auth/Dbo/AuthInfo.h>

#include <Wt/Dbo/backend/Sqlite3.h>
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
  auto connection = std::make_unique<Dbo::backend::Sqlite3>(sqliteDb);
  setConnection(std::move(connection));

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
  auto userRole = add(std::make_unique<UserRole>());
  userRole.modify()->name = "admin";

  userRole = add(std::make_unique<UserRole>());
  userRole.modify()->name = "user";

  // Create a new User in User table
  std::unique_ptr<User> newUserPtr{new User()};
  newUserPtr->first_name = "Alexandru";
  newUserPtr->last_name = "Croitoriu";
  newUserPtr->phone = "+40771133255";
  newUserPtr->darkMode = false;
  newUserPtr->joinDate = Wt::WDateTime::currentDateTime().toTimePoint();

  dbo::ptr<User> userPtr = this->add(std::move(newUserPtr));

  auto newUser = users_->registerNew();
  users_->setIdentity(newUser, Wt::Auth::Identity::LoginName, "admin@gmail.com");
  newUser.setEmail("admin@gmail.com");

  myPasswordService.updatePassword(newUser, "asdfghj1");

  // t.commit();
}

void Session::configureAuth()
{
  myAuthService.setAuthTokensEnabled(true, "logincookie");
  myAuthService.setEmailVerificationEnabled(false);
  myAuthService.setEmailVerificationRequired(false);
  // myAuthService.setAuthTokenValidity(300);
  myAuthService.setIdentityPolicy(Wt::Auth::IdentityPolicy::EmailAddress);
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
