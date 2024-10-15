#include "005-Calendar/AllEntriesDialog.h"
#include "001-App/App.h"
#include "005-Calendar/EntryDialog.h"
// #include "Entry.h"
#include "005-Calendar/Tables/CalendarEntry.h"

#include <Wt/WTemplate.h>
#include <Wt/WString.h>
#include <Wt/WText.h>
#include <Wt/WPushButton.h>

AllEntriesDialog::AllEntriesDialog(const Wt::WString &title, CalendarCell *cell)
    : Wt::WDialog(title)
{
  Wt::WTemplate *t = contents()->addWidget(std::make_unique<WTemplate>(
      tr("calendar.all-entries")));
  auto wc = std::make_unique<WContainerWidget>();
  auto container = t->bindWidget("entries", std::move(wc));

  dbo::Session &session = App::app()->session_;
  dbo::Transaction transaction(session);

  typedef dbo::collection<dbo::ptr<CalendarEntry>> Entries;

  Entries entries =
      cell->user()->entriesInRange(cell->date(), cell->date().addDays(1));

  Wt::WString format = EntryDialog::timeFormat;
  for (auto &entry : entries)
  {
    container->addWidget(std::make_unique<WText>(entry->start.toString(format) +
                                                 "-" +
                                                 entry->stop.toString(format) +
                                                 ": " + entry->summary));
  }

  transaction.commit();

  auto button = std::make_unique<WPushButton>(tr("calendar.cell.all-entries.close"));
  auto buttonPtr = t->bindWidget("close", std::move(button));
  buttonPtr->clicked().connect(this, &AllEntriesDialog::closeDialog);
}

void AllEntriesDialog::closeDialog()
{
  hide();
}
