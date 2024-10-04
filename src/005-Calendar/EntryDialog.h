#pragma once
#include <Wt/WDialog.h>
#include <Wt/WDate.h>
#include <Wt/WDateTime.h>
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>

#include "005-Calendar/CalendarCell.h"

class EntryDialog : public Wt::WDialog
{
public:
  EntryDialog(const Wt::WString &title, CalendarCell *cell);

private:
  Wt::WDateTime timeStamp(const Wt::WString &time, const Wt::WDate &day);
  Wt::WString description();
  void ok();
  void cancel();

public:
  static Wt::WString timeFormat;

private:
  CalendarCell *cell_;

  Wt::WLineEdit *summary_;
  Wt::WLineEdit *start_;
  Wt::WLineEdit *stop_;
  Wt::WTextArea *description_;
};
