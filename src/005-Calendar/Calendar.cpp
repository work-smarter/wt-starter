
#include "005-Calendar/Calendar.h"
#include "005-Calendar/CalendarCell.h"
#include "005-Calendar/Tables/CalendarEntry.h"

Calendar::Calendar(dbo::ptr<User> user)
    : WCalendar(),
      user_(user)
{
    setStyleClass(styleClass() + " calendar");

    setSelectionMode(Wt::SelectionMode::None);
}

Wt::WWidget *Calendar::renderCell(Wt::WWidget *widget, const Wt::WDate &date)
{
    if (!widget)
        widget = new CalendarCell();

    CalendarCell *cc = (CalendarCell *)widget;
    cc->update(user_, date);

    return cc;
}
