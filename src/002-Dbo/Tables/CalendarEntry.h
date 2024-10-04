#pragma once
#include <Wt/WDateTime.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

using namespace Wt;

class User;

namespace dbo = Dbo;

class CalendarEntry
{
public:
  dbo::ptr<User> user;

  WDateTime start;
  WDateTime stop;
  WString summary;
  WString text;

  template <class Action>
  void persist(Action &a)
  {
    dbo::belongsTo(a, user, "user");

    dbo::field(a, start, "start");
    dbo::field(a, stop, "stop");
    dbo::field(a, summary, "summary");
    dbo::field(a, text, "text");
  }
};
