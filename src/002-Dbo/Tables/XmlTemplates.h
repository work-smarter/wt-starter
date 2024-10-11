#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class TemplateFile;

class Template
{
public:
  Wt::WString xml_temp;
  dbo::ptr<TemplateFile> template_files;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, xml_temp, "xml_temp");
    dbo::belongsTo(a, template_files, "template_file");
  }
};

class TemplateFile
{
public:
  Wt::WString path;
  dbo::collection<dbo::ptr<Template>> templates;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, path, "path");
    dbo::hasMany(a, templates, dbo::ManyToOne, "template_file");
  }
};
