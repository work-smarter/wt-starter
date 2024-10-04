#pragma once

#include <Wt/WDialog.h>
#include <Wt/WString.h>

#include "005-Calendar/CalendarCell.h"


class AllEntriesDialog : public Wt::WDialog
{
public:
  AllEntriesDialog(const Wt::WString &title, CalendarCell *cell);

private:
  void closeDialog();
};