#include "003-Auth/AuthWidget.h"
#include "003-Auth/RegistrationView.h"
#include "002-Dbo/Session.h"
#include "003-Auth/UserFormModel.h"
#include "003-Auth/PasswordPromptDialog.h"
// #include "App/1-AuthApp.h"

AuthWidget::AuthWidget(Session &session)
    : Auth::AuthWidget(Session::auth(), session.users(), session.login()),
      // model_(std::make_shared<Wt::Auth::AuthModel>(Session::auth(), session.users())),
      session_(session)
{
  setStyleClass("w-screen h-screen");
}

std::unique_ptr<Wt::WWidget> AuthWidget::createRegistrationView(const Wt::Auth::Identity &id)
{
  auto registrationView = std::make_unique<RegistrationView>(session_, this);
  std::unique_ptr<Auth::RegistrationModel> model = createRegistrationModel();
  if (id.isValid())
    model->registerIdentified(id);

  registrationView->setModel(std::move(model));
  return std::move(registrationView);
}

// void AuthWidget::createLoggedInView(){
//   setTemplateText(Wt::WString::tr("Wt.Auth.template.logged-in-test"));
//   bindString("user-name", login().user().identity(Wt::Auth::Identity::LoginName));

//   WPushButton *logout = bindWidget("logout",std::make_unique<WPushButton>(tr("Wt.Auth.logout")));
//   logout->clicked().connect(this, [=](){
//     login().logout();
//   });
// }

// std::unique_ptr<Wt::WDialog> AuthWidget::createPasswordPromptDialog(Wt::Auth::Login &login)
// {
//   return std::make_unique<PasswordPromptDialog>(login, model_);
// }
