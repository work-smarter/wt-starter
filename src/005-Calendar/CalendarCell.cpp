#include "005-Calendar/CalendarCell.h"
#include "005-Calendar/EntryDialog.h"
#include "005-Calendar/AllEntriesDialog.h"
#include "001-App/App.h"
#include "005-Calendar/Tables/CalendarEntry.h"

#include <Wt/WDate.h>
#include <Wt/WText.h>

#include <string>

CalendarCell::CalendarCell()
    : WContainerWidget()
{
  resize(100, 120);

  // setStyleClass("w-[100px] h-[120px]");
  setToolTip(tr("calendar.cell.tooltip"));

  // clicked().connect(this, &CalendarCell::showEntryDialog);
  // extraPtr->clicked().connect(this, &CalendarCell::showAllEntriesDialog);
  clicked().connect(this, &CalendarCell::showAllEntriesDialog);
}

void CalendarCell::update(const dbo::ptr<User> &user, const Wt::WDate &date)
{
  date_ = date;
  user_ = user;

  clear();

  dbo::Session &session = App::app()->session_;
  dbo::Transaction transaction(session);

  WString day;
  day += std::to_string(date.day());
  if (date.day() == 1)
    day += " " + WDate::longMonthName(date.month());
  auto header = std::make_unique<WText>(day);
  header->setStyleClass("cell-header");
  addWidget(std::move(header));

  typedef dbo::collection<dbo::ptr<CalendarEntry>> Entries;
  Entries entries = user->entriesInRange(date, date.addDays(1));

  const unsigned maxEntries = 4;
  unsigned counter = 0;
  for (Entries::const_iterator i = entries.begin();
       i != entries.end(); ++i, ++counter)
  {
    if (counter == maxEntries)
    {
      auto extra =
          std::make_unique<WText>(tr("calendar.cell.extra")
                                      .arg((int)(entries.size() - maxEntries)));
      auto extraPtr = addWidget(std::move(extra));
      extraPtr->setStyleClass("cell-extra");

      extraPtr->clicked().preventPropagation();
      extraPtr->clicked().connect(this, &CalendarCell::showAllEntriesDialog);
      break;
    }

    WString format = EntryDialog::timeFormat;
    addWidget(std::make_unique<WText>((*i)->start.toString(format) +
                                      "-" +
                                      (*i)->stop.toString(format) +
                                      ": " + (*i)->summary));
  }

  transaction.commit();
}

void CalendarCell::showEntryDialog()
{
  WString title =
      tr("calendar.entry.title").arg(date_.toString("ddd, d MMM yyyy"));

  dialog_ = std::make_unique<EntryDialog>(title, this);
  dialog_->show();
}

void CalendarCell::showAllEntriesDialog()
{
  WString title =
      tr("calendar.cell.all-entries.title")
          .arg(date_.toString("ddd, d MMM yyyy"));

  dialog_ = std::make_unique<AllEntriesDialog>(title, this);
  dialog_->show();
}
