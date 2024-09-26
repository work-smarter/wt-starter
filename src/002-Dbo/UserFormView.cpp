#include "002-Dbo/UserFormView.h"
#include "002-Dbo/Session.h"

#include <Wt/Auth/Dbo/AuthInfo.h>

#include <Wt/Auth/GoogleService.h>
// #include <Wt/Auth/FacebookService.h>

#include <Wt/WLineEdit.h>
#include <Wt/WText.h>

UserFormView::UserFormView(Session &session)
    : WTemplateFormView(tr("starter.user.settings.form")),
      session_(session)
{
    model_ = std::make_unique<UserFormModel>(session_);

    addFunction("id", &WTemplate::Functions::id);

    setFormWidget(UserFormModel::USER_NAME, std::make_unique<Wt::WLineEdit>());
    bindString("user-name-info", Wt::WString::tr("Wt.Auth.user-name-info"));
    auto user_name_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::USER_NAME));
    user_name_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.user-name"));
    user_name_input->changed().connect([=]
                                       {
                                           updateModelField(model_.get(), UserFormModel::USER_NAME);

                                           std::string user_name = model_->valueText(UserFormModel::USER_NAME).toUTF8();

                                           Dbo::Transaction t(session_);
                                           // check if there are any other users with the same user_name
                                           auto user = session_.users().findWithIdentity(Wt::Auth::Identity::LoginName, user_name);
                                           std::cout << "\n\n current user id :[" << session_.user().id() << "]\n\n";
                                           std::cout << "\n\n user id :[" << user.id() << "]\n\n";
                                           std::string user_id = std::to_string(session_.user().id());
                                            if (user.id().compare("") == 0)
                                            {
                                                std::cout << "\n\n user name saved to the dbo \n\n";
                                                model_->saveUserName(session_.login().user(), user_name_input->text().toUTF8());
                                            }else if (user.id().compare(user_id) == 0)
                                            {
                                                std::cout << "\n\n same user name so dont save \n\n";
                                                model_->setValidation(UserFormModel::USER_NAME, Wt::WValidator::Result(Wt::WValidator::State::Valid, Wt::WString::tr("Wt.Auth.user-name-valid")));
                                            }else{
                                                std::cout << "\n\n user name exists \n\n";
                                                model_->setValidation(UserFormModel::USER_NAME, Wt::WValidator::Result(Wt::WValidator::State::Invalid, Wt::WString::tr("Wt.Auth.user-name-exists")));
                                            }

                                            t.commit(); 
                                            updateView(model_.get()); });

    setFormWidget(UserFormModel::FIRST_NAME, std::make_unique<Wt::WLineEdit>());
    bindString("first-name-info", Wt::WString::tr("Wt.Auth.first-name-info"));
    auto first_name_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::FIRST_NAME));
    first_name_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.first-name"));
    first_name_input->changed().connect([=]
                                        { validate(); });

    setFormWidget(UserFormModel::LAST_NAME, std::make_unique<Wt::WLineEdit>());
    bindString("last-name-info", Wt::WString::tr("Wt.Auth.last-name-info"));
    auto last_name_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::LAST_NAME));
    last_name_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.last-name"));
    last_name_input->changed().connect([=]
                                       { validate(); });

    setFormWidget(UserFormModel::PHONE, std::make_unique<Wt::WLineEdit>());
    bindString("phone-info", Wt::WString::tr("Wt.Auth.phone-info"));
    auto phone_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::PHONE));
    phone_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.phone"));
    phone_input->changed().connect([=]
                                   { validate(); });
    phone_input->setMaxLength(10);

    dbo::Transaction t(session_);
    user_name_input->setText(session_.user()->auth_info->authIdentities().front()->identity());
    t.commit();
    first_name_input->setText(session_.user()->first_name);
    last_name_input->setText(session_.user()->last_name);
    phone_input->setText(session_.user()->phone);

    updateModel(model_.get());
    updateView(model_.get());
}

bool UserFormView::validate()
{
    bool result = model_->validate();

    updateModel(model_.get());
    if (!model_->validate())
        result = false;
    updateView(model_.get());
    return result;
}