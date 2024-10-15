#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class AppTemplateFile;

class TemplateApp
{
public:
  Wt::WString app_name;
  dbo::collection<dbo::ptr<AppTemplateFile>> xml_template_files;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, app_name, "app_name");
    dbo::hasMany(a, xml_template_files, dbo::ManyToOne, "template_app"); // one-to-many relationship
  }
};
