#include "002-Dbo/UserFormView.h"
#include "002-Dbo/Session.h"
#include "002-Dbo/UserPhotoUploder.h"
#include "100-Utils/AwsConnect.h"
// #include <Wt/Auth/Dbo/AuthInfo.h>

// #include <Wt/Auth/GoogleService.h>
// #include <Wt/Auth/FacebookService.h>
#include <Wt/Auth/Identity.h>

#include <Wt/WLineEdit.h>
#include <Wt/WFileUpload.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WLink.h>

UserFormView::UserFormView(Session &session)
    : WTemplateFormView(tr("starter.user.settings.form")),
      session_(session)
{
    model_ = std::make_unique<UserFormModel>(session_);

    addFunction("id", &WTemplate::Functions::id);

    auto user_name_save_btn = bindWidget("user-name-save-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-ok")));
    auto user_name_cancel_btn = bindWidget("user-name-cancel-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-x")));
    user_name_save_btn->setEnabled(false);
    user_name_cancel_btn->setEnabled(false);
    setFormWidget(UserFormModel::USER_NAME, std::make_unique<Wt::WLineEdit>());
    bindString("user-name-info", Wt::WString::tr("Wt.Auth.user-name-info"));
    auto user_name_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::USER_NAME));
    user_name_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.user-name"));
    user_name_input->enterPressed().connect([=]
                                            { if(user_name_save_btn->isEnabled()) user_name_save_btn->clicked().emit(Wt::WMouseEvent()); });
    user_name_input->textInput().connect([=]
                                         {
                                            updateModelField(model_.get(), UserFormModel::USER_NAME);

                                            std::string user_name = model_->valueText(UserFormModel::USER_NAME).toUTF8();
                                            auto validation_result = model_->validateField(UserFormModel::USER_NAME);

                                            Dbo::Transaction t(session_);
                                            // check if there are any other users with the same user_name
                                            auto user = session_.users().findWithIdentity(Wt::Auth::Identity::LoginName, user_name);
                                            std::string user_id = std::to_string(session_.user().id());
                                            if (user.id().compare("") == 0 && validation_result == true)
                                            {
                                                model_->setValidation(UserFormModel::USER_NAME, Wt::WValidator::Result(Wt::WValidator::State::Valid, Wt::WString::tr("Wt.Auth.user-name-info")));
                                            }
                                            else if (user.id().compare(user_id) == 0 && validation_result == true)
                                            {
                                                model_->setValidation(UserFormModel::USER_NAME, Wt::WValidator::Result(Wt::WValidator::State::Valid, Wt::WString::tr("Wt.Auth.user-name-info")));
                                            }   
                                            else if(validation_result == true)
                                            {
                                                model_->setValidation(UserFormModel::USER_NAME, Wt::WValidator::Result(Wt::WValidator::State::Invalid, Wt::WString::tr("Wt.Auth.user-name-exists")));
                                            }
                                            
                                            updateModelField(model_.get(), UserFormModel::USER_NAME);
                                            auto validation_state = model_->validation(UserFormModel::USER_NAME).state();
                                            if(validation_state == Wt::WValidator::State::Invalid) {
                                                user_name_save_btn->setEnabled(false);
                                                user_name_cancel_btn->setEnabled(true);
                                            } else if(user_name_input->text().toUTF8().compare(session_.login().user().identity(Wt::Auth::Identity::LoginName).toUTF8()) != 0 && validation_state == Wt::WValidator::State::Valid) {
                                                user_name_save_btn->setEnabled(true);
                                                user_name_cancel_btn->setEnabled(true);
                                            } else {
                                                user_name_save_btn->setEnabled(false);
                                                user_name_cancel_btn->setEnabled(false);
                                            }
                                            t.commit();
                                           
                                           updateView(model_.get()); });

    user_name_save_btn->clicked().connect(this, [=]
                                          { model_->saveUserName(session_.login().user(), user_name_input->text().toUTF8());
                                            user_name_save_btn->setEnabled(false);
                                            user_name_cancel_btn->setEnabled(false); });
    user_name_cancel_btn->clicked().connect(this, [=]
                                            { user_name_input->setText(session_.login().user().identity(Wt::Auth::Identity::LoginName));
                                            user_name_save_btn->setEnabled(false);
                                            user_name_cancel_btn->setEnabled(false);
                                            updateModelField(model_.get(), UserFormModel::USER_NAME);
                                            model_->validateField(UserFormModel::USER_NAME);
                                            updateViewField(model_.get(), UserFormModel::USER_NAME); });

    auto first_name_save_btn = bindWidget("first-name-save-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-ok")));
    auto first_name_cancel_btn = bindWidget("first-name-cancel-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-x")));
    first_name_save_btn->setEnabled(false);
    first_name_cancel_btn->setEnabled(false);
    setFormWidget(UserFormModel::FIRST_NAME, std::make_unique<Wt::WLineEdit>());
    bindString("first-name-info", Wt::WString::tr("Wt.Auth.first-name-info"));
    auto first_name_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::FIRST_NAME));
    first_name_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.first-name"));
    first_name_input->enterPressed().connect([=]
                                             { if(first_name_save_btn->isEnabled()) first_name_save_btn->clicked().emit(Wt::WMouseEvent()); });
    first_name_input->textInput().connect([=]
                                          {
                                        updateModelField(model_.get(), UserFormModel::FIRST_NAME);
                                        auto result = model_->validateField(UserFormModel::FIRST_NAME);
                                        if (!result)
                                        {
                                            model_->setValidation(UserFormModel::FIRST_NAME, Wt::WValidator::Result(Wt::WValidator::State::Invalid, Wt::WString::tr("App-first-name-error")));
                                        }
                                        updateView(model_.get());
                                        auto t = Dbo::Transaction(session_);
                                        if (result && first_name_input->text().toUTF8().compare(session_.user()->first_name.toUTF8()) != 0)
                                        {
                                            first_name_save_btn->setEnabled(true);
                                            first_name_cancel_btn->setEnabled(true);
                                        }
                                        else if (!result && first_name_input->text().toUTF8().compare(session_.user()->first_name.toUTF8()) != 0)
                                        {
                                            first_name_save_btn->setEnabled(false);
                                            first_name_cancel_btn->setEnabled(true);
                                        } else {
                                            first_name_save_btn->setEnabled(false);
                                            first_name_cancel_btn->setEnabled(false);
                                        } 
                                        t.commit(); });
    first_name_save_btn->clicked().connect(this, [=]
                                           { model_->saveFirstName(session_.login().user(), first_name_input->text().toUTF8()); 
                                            first_name_save_btn->setEnabled(false);
                                            first_name_cancel_btn->setEnabled(false); });
    first_name_cancel_btn->clicked().connect(this, [=]
                                             { first_name_input->setText(session_.user()->first_name);
                                            first_name_save_btn->setEnabled(false);
                                            first_name_cancel_btn->setEnabled(false); 
                                            updateModelField(model_.get(), UserFormModel::FIRST_NAME);
                                            model_->validateField(UserFormModel::FIRST_NAME);
                                            updateViewField(model_.get(), UserFormModel::FIRST_NAME); });

    auto last_name_save_btn = bindWidget("last-name-save-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-ok")));
    auto last_name_cancel_btn = bindWidget("last-name-cancel-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-x")));
    last_name_save_btn->setEnabled(false);
    last_name_cancel_btn->setEnabled(false);
    setFormWidget(UserFormModel::LAST_NAME, std::make_unique<Wt::WLineEdit>());
    bindString("last-name-info", Wt::WString::tr("Wt.Auth.last-name-info"));
    auto last_name_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::LAST_NAME));
    last_name_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.last-name"));
    last_name_input->enterPressed().connect([=]
                                            { if(last_name_save_btn->isEnabled()) last_name_save_btn->clicked().emit(Wt::WMouseEvent()); });
    last_name_input->textInput().connect([=]
                                         { 
                                            updateModelField(model_.get(), UserFormModel::LAST_NAME);
                                            auto result = model_->validateField(UserFormModel::LAST_NAME);
                                            if(!result) {
                                                model_->setValidation(UserFormModel::LAST_NAME, Wt::WValidator::Result(Wt::WValidator::State::Invalid, Wt::WString::tr("App-last-name-error")));
                                            }
                                            updateView(model_.get()); 
                                            auto t = Dbo::Transaction(session_);
                                            if(result && last_name_input->text().toUTF8().compare(session_.user()->last_name.toUTF8()) != 0) {
                                                last_name_save_btn->setEnabled(true);
                                                last_name_cancel_btn->setEnabled(true);
                                            } else if(!result && last_name_input->text().toUTF8().compare(session_.user()->last_name.toUTF8()) != 0) {
                                                last_name_save_btn->setEnabled(false);
                                                last_name_cancel_btn->setEnabled(true);
                                            } else {
                                                last_name_save_btn->setEnabled(false);
                                                last_name_cancel_btn->setEnabled(false);
                                            } 
                                            t.commit(); });
    last_name_save_btn->clicked().connect(this, [=]
                                          { model_->saveLastName(session_.login().user(), last_name_input->text().toUTF8()); 
                                                last_name_save_btn->setEnabled(false);
                                                last_name_cancel_btn->setEnabled(false); });
    last_name_cancel_btn->clicked().connect(this, [=]
                                            { last_name_input->setText(session_.user()->last_name);
                                            last_name_save_btn->setEnabled(false);
                                            last_name_cancel_btn->setEnabled(false);
                                            updateModelField(model_.get(), UserFormModel::LAST_NAME);
                                            model_->validateField(UserFormModel::LAST_NAME);
                                            updateViewField(model_.get(), UserFormModel::LAST_NAME); });

    auto phone_save_btn = bindWidget("phone-save-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-ok")));
    auto phone_cancel_btn = bindWidget("phone-cancel-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("App.Button-check-x")));
    phone_save_btn->setEnabled(false);
    phone_cancel_btn->setEnabled(false);
    setFormWidget(UserFormModel::PHONE, std::make_unique<Wt::WLineEdit>());
    bindString("phone-info", Wt::WString::tr("Wt.Auth.phone-info"));
    auto phone_input = dynamic_cast<Wt::WLineEdit *>(resolveWidget(UserFormModel::PHONE));
    phone_input->setPlaceholderText(Wt::WString::tr("Wt.Auth.phone"));
    phone_input->enterPressed().connect([=]
                                        { if(phone_save_btn->isEnabled()) phone_save_btn->clicked().emit(Wt::WMouseEvent()); });
    phone_input->textInput().connect([=]
                                     { 
                                        updateModelField(model_.get(), UserFormModel::PHONE);
                                        auto result = model_->validateField(UserFormModel::PHONE);
                                        if(!result) {
                                            model_->setValidation(UserFormModel::PHONE, Wt::WValidator::Result(Wt::WValidator::State::Invalid, Wt::WString::tr("App-phone-validation-error")));
                                        }
                                        updateView(model_.get());
                                        auto t = Dbo::Transaction(session_);
                                        if(result && phone_input->text().toUTF8().compare(session_.user()->phone.toUTF8()) != 0) {
                                            phone_save_btn->setEnabled(true);
                                            phone_cancel_btn->setEnabled(true);
                                        } else if(!result && phone_input->text().toUTF8().compare(session_.user()->phone.toUTF8()) != 0) {
                                            phone_save_btn->setEnabled(false);
                                            phone_cancel_btn->setEnabled(true);
                                        } else {
                                            phone_save_btn->setEnabled(false);
                                            phone_cancel_btn->setEnabled(false);
                                        } 
                                        t.commit(); });
    phone_save_btn->clicked().connect(this, [=]
                                      { model_->savePhone(session_.login().user(), phone_input->text().toUTF8()); 
                                        phone_save_btn->setEnabled(false);
                                        phone_cancel_btn->setEnabled(false); });
    phone_cancel_btn->clicked().connect(this, [=]
                                        { phone_input->setText(session_.user()->phone);
                                        phone_save_btn->setEnabled(false);
                                        phone_cancel_btn->setEnabled(false); 
                                        updateModelField(model_.get(), UserFormModel::PHONE);
                                        model_->validateField(UserFormModel::PHONE);
                                        updateViewField(model_.get(), UserFormModel::PHONE); });
    phone_input->setMaxLength(10);

    auto file_upload = bindWidget("file-upload", std::make_unique<UserPhotoUploder>(session_));

    dbo::Transaction t(session_);

    user_name_input->setText(session_.user()->auth_info->authIdentities().front()->identity());
    t.commit();
    first_name_input->setText(session_.user()->first_name);
    last_name_input->setText(session_.user()->last_name);
    phone_input->setText(session_.user()->phone);

    updateModel(model_.get());
    updateView(model_.get());
}

// bool UserFormView::validate()
// {
//     bool result = model_->validate();

//     updateModel(model_.get());
//     if (!model_->validate())
//         result = false;
//     updateView(model_.get());
//     return result;
// }