#include "002-Dbo/Tables/User.h"
#include "002-Dbo/Tables/CalendarEntry.h"

dbo::collection<dbo::ptr<CalendarEntry>> User::entriesInRange(const Wt::WDate &from,
                                                              const Wt::WDate &until) const
{
    return entries.find()
        .where("start >= ?")
        .bind(Wt::WDateTime(from))
        .where("start < ?")
        .bind(Wt::WDateTime(until));
}