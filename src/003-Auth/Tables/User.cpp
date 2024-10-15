#include "003-Auth/Tables/User.h"
#include "005-Calendar/Tables/CalendarEntry.h"

dbo::collection<dbo::ptr<CalendarEntry>> User::entriesInRange(const Wt::WDate &from,
                                                              const Wt::WDate &until) const
{
    return entries.find()
        .where("start >= ?")
        .bind(Wt::WDateTime(from))
        .where("start < ?")
        .bind(Wt::WDateTime(until));
}