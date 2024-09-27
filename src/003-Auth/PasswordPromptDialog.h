#pragma once
#include <Wt/Auth/PasswordPromptDialog.h>

class PasswordPromptDialog : public Wt::Auth::PasswordPromptDialog
{
public:
    PasswordPromptDialog(Wt::Auth::Login &login, const std::shared_ptr<Wt::Auth::AuthModel> &model);

private:
};