#pragma once
#include <Wt/Auth/AuthWidget.h>
#include <Wt/WWidget.h>
#include <Wt/WPushButton.h>

class Session;

class AuthWidget : public Wt::Auth::AuthWidget
{
public:
  AuthWidget(Session& session);

  /* custom registration view */
  virtual std::unique_ptr<Wt::WWidget> createRegistrationView(const Wt::Auth::Identity& id) override;

  /* custom logged in view commented out because it has no use at the moment */ 
  // virtual void createLoggedInView() override;

private:
  Session& session_;

};