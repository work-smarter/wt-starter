#include "003-Auth/RegistrationView.h"
#include "002-Dbo/Session.h"

#include <Wt/WLineEdit.h>
#include <Wt/WLengthValidator.h>

RegistrationView::RegistrationView(Session &session,
                                   Wt::Auth::AuthWidget *authWidget)
    : Wt::Auth::RegistrationWidget(authWidget),
      session_(session)
{
  setTemplateText(tr("Wt.Auth.template.registration"));
  model_ = std::make_unique<UserFormModel>(session_);
  setStyleClass("h-screen w-screen px-6 py-12 flex-col flex lg:px-8 bg-white ");
  updateView(model_.get());

  bindEmpty("first-name-info");
  bindEmpty("last-name-info");
  bindEmpty("phone-info");
}

std::unique_ptr<Wt::WWidget> RegistrationView::createFormWidget(Wt::WFormModel::Field field)
{
  if (field == UserFormModel::FIRST_NAME)
  {

    auto input = std::make_unique<Wt::WLineEdit>();
    input->changed().connect([=]
                             {
                               updateModelField(model_.get(), UserFormModel::FIRST_NAME);
                                auto result = model_->validateField(UserFormModel::FIRST_NAME);
                               updateViewField(model_.get(), UserFormModel::FIRST_NAME); });
    return input;
  }
  else if (field == UserFormModel::LAST_NAME)
  {
    auto input = std::make_unique<Wt::WLineEdit>();
    input->changed().connect([=]
                             { 
                                updateModelField(model_.get(), UserFormModel::LAST_NAME);
                                auto result = model_->validateField(UserFormModel::LAST_NAME);
                                updateViewField(model_.get(), UserFormModel::LAST_NAME); });
    return input;
  }
  else if (field == UserFormModel::PHONE)
  {
    auto input = std::make_unique<Wt::WLineEdit>();
    input->changed().connect([=]
                             { 
                                updateModelField(model_.get(), UserFormModel::PHONE);
                                auto result = model_->validateField(UserFormModel::PHONE);
                                updateViewField(model_.get(), UserFormModel::PHONE); });
    input->setMaxLength(10);
    return input;
  }
  else
    return Wt::Auth::RegistrationWidget::createFormWidget(field);
}

bool RegistrationView::validate()
{
  bool result = Wt::Auth::RegistrationWidget::validate();

  updateModel(model_.get());
  if (!model_->validate())
    result = false;
  updateView(model_.get());

  return result;
}

void RegistrationView::registerUserDetails(Wt::Auth::User &user)
{
  model_->save(user);
}