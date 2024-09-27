#include "003-Auth/PasswordPromptDialog.h"

PasswordPromptDialog::PasswordPromptDialog(Wt::Auth::Login &login, const std::shared_ptr<Wt::Auth::AuthModel> &model)
    : Wt::Auth::PasswordPromptDialog(login, model)
{
    // setStyleClass("bg-red-400");
    setStyleClass("h-screen w-screen px-6 py-12 flex-col flex lg:px-8 bg-white ");
}