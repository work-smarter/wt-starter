#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WDate.h>
#include <Wt/WDialog.h>

#include "002-Dbo/Tables/User.h"
// #include "UserAccount.h"

class CalendarCell : public Wt::WContainerWidget
{
public:
  CalendarCell();

  void update(const dbo::ptr<User> &user, const Wt::WDate &date);

  Wt::WDate date() { return date_; }
  dbo::ptr<User> user() { return user_; }

private:
  Wt::WDate date_;
  dbo::ptr<User> user_;
  std::unique_ptr<Wt::WDialog> dialog_;

  void showEntryDialog();
  void showAllEntriesDialog();
};