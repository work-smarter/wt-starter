#include "005-Calendar/EntryDialog.h"
#include "005-Calendar/TimeSuggestions.h"
#include "005-Calendar/Tables/CalendarEntry.h"
#include "001-App/App.h"

#include <Wt/WTemplate.h>
#include <Wt/WPushButton.h>
#include <Wt/WRegExpValidator.h>

#include <Wt/Dbo/WtSqlTraits.h>

Wt::WString EntryDialog::timeFormat = Wt::WString("HH:mm");

EntryDialog::EntryDialog(const Wt::WString &title, CalendarCell *cell)
    : Wt::WDialog(title)
{
  cell_ = cell;

  Wt::WTemplate *t = contents()->addWidget(std::make_unique<Wt::WTemplate>());
  t->setTemplateText(tr("calendar.entry"));

  auto summaryPtr = std::make_unique<Wt::WLineEdit>();
  summary_ = t->bindWidget("summary", std::move(summaryPtr));
  summary_->setValidator(std::make_shared<Wt::WValidator>());

  auto timeValidator =
      std::make_shared<Wt::WRegExpValidator>("^([0-1][0-9]|[2][0-3]):([0-5][0-9])$");
  auto startPtr = std::make_unique<Wt::WLineEdit>();
  start_ = t->bindWidget("start", std::move(startPtr));
  start_->setTextSize(5);
  start_->setValidator(timeValidator);

  auto stopPtr = std::make_unique<Wt::WLineEdit>();
  stop_ = t->bindWidget("stop", std::move(stopPtr));
  stop_->setTextSize(5);
  stop_->setValidator(timeValidator);

  auto descriptionPtr = std::make_unique<WTextArea>();
  description_ = t->bindWidget("description", std::move(descriptionPtr));

  TimeSuggestions *suggestions = contents()->addChild(std::make_unique<TimeSuggestions>());
  suggestions->forEdit(start_);
  suggestions->forEdit(stop_);

  auto okPtr = std::make_unique<Wt::WPushButton>(tr("calendar.entry.ok"));
  auto ok = t->bindWidget("ok", std::move(okPtr));
  ok->clicked().connect(this, &EntryDialog::ok);

  auto cancelPtr = std::make_unique<Wt::WPushButton>(tr("calendar.entry.cancel"));
  auto cancel = t->bindWidget("cancel", std::move(cancelPtr));
  cancel->clicked().connect(this, &EntryDialog::cancel);
  rejectWhenEscapePressed();
}

Wt::WDateTime EntryDialog::timeStamp(const Wt::WString &time, const Wt::WDate &day)
{
  Wt::WString timeStamp = day.toString("dd/MM/yyyy ");
  timeStamp += time;
  return Wt::WDateTime::fromString(timeStamp, "dd/MM/yyyy " + timeFormat);
}

Wt::WString EntryDialog::description()
{
  return description_->text();
}

void EntryDialog::ok()
{
  std::cout << "\n\nEntryDialog::ok()\n\n";
  Session &session = App::app()->session_;
  dbo::Transaction transaction(session);

  // dbo::ptr<CalendarEntry> e = session.add(std::make_unique<CalendarEntry>());

  dbo::ptr<CalendarEntry> e =
      App::app()->session_.add(
          std::make_unique<CalendarEntry>());
  e.modify()->start = timeStamp(start_->text(), cell_->date());
  e.modify()->stop = timeStamp(stop_->text(), cell_->date());
  e.modify()->summary = summary_->text().toUTF8();
  e.modify()->text = description().toUTF8();
  e.modify()->user = cell_->user();

  cell_->update(cell_->user(), cell_->date());

  transaction.commit();
  hide();
  std::cout << "\n\nEntryDialog::ok()\n\n";
}

void EntryDialog::cancel()
{
  hide();
}
