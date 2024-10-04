#pragma once
#include <Wt/Dbo/Dbo.h>
#include <Wt/WCalendar.h>
#include <Wt/WDate.h>
#include <Wt/WDialog.h>
#include "002-Dbo/Tables/User.h"

class Calendar : public Wt::WCalendar
{
public:
    Calendar(dbo::ptr<User> user);

protected:
    virtual Wt::WWidget *renderCell(Wt::WWidget *widget, const Wt::WDate &date) override;

private:
    dbo::ptr<User> user_;
};
