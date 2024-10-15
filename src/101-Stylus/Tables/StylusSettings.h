#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class StylusSettings
{
public:
  bool settings_panel_active;
  bool left_panel_active;
  bool right_panel_active;
  bool edditor_panel_active;
  bool quick_commands_panel_active;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, settings_panel_active, "settings_panel_active");
    dbo::field(a, left_panel_active, "left_panel_active");
    dbo::field(a, right_panel_active, "right_panel_active");
    dbo::field(a, edditor_panel_active, "edditor_panel_active");
    dbo::field(a, quick_commands_panel_active, "quick_commands_panel_active");
  }
};
