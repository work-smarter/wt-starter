#pragma once
#include <Wt/WTemplateFormView.h>
#include "002-Dbo/UserFormModel.h"

class Session;

class UserFormView : public Wt::WTemplateFormView
{
public:
    UserFormView(Session &session);

private:
    Session &session_;
    // bool validate();
    std::unique_ptr<UserFormModel> model_;
};