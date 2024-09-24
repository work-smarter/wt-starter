#include "003-Auth/RegistrationView.h"
#include "002-Dbo/UserDetailsModel.h"
#include <Wt/WLineEdit.h>

#include <Wt/WLengthValidator.h>

RegistrationView::RegistrationView(Session &session,
                                   Wt::Auth::AuthWidget *authWidget)
    : Wt::Auth::RegistrationWidget(authWidget),
      session_(session)
{
  setTemplateText(tr("Wt.Auth.template.registration"));
  detailsModel_ = std::make_unique<UserDetailsModel>(session_);
  setStyleClass("h-screen w-screen px-6 py-12 flex-col flex lg:px-8 bg-white ");
  updateView(detailsModel_.get());

  bindEmpty("first-name-info");
  bindEmpty("last-name-info");
  bindEmpty("phone-info");
}

std::unique_ptr<Wt::WWidget> RegistrationView::createFormWidget(Wt::WFormModel::Field field)
{
  if (field == UserDetailsModel::first_name ||
      field == UserDetailsModel::last_name ||
      field == UserDetailsModel::phone)
  {

    auto input = std::make_unique<Wt::WLineEdit>();
    input->changed().connect([=]
                             { validate(); });
    return input;
  }
  else
    return Wt::Auth::RegistrationWidget::createFormWidget(field);
}

bool RegistrationView::validate()
{
  bool result = Wt::Auth::RegistrationWidget::validate();

  updateModel(detailsModel_.get());
  if (!detailsModel_->validate())
    result = false;
  updateView(detailsModel_.get());

  return result;
}

void RegistrationView::registerUserDetails(Wt::Auth::User &user)
{
  detailsModel_->save(user);
}