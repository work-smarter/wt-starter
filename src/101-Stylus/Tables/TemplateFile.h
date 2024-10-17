#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class XmlTemplate;

class AppXmlTemplate;
class TemplateApp;

class TemplateFile
{
public:
  Wt::WString name;
  dbo::collection<dbo::ptr<XmlTemplate>> xml_templates;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, name, "name");
    dbo::hasMany(a, xml_templates, dbo::ManyToOne, "template_file"); // one-to-many relationship
  }
};

class AppTemplateFile
{
public:
  Wt::WString name;
  dbo::collection<dbo::ptr<AppXmlTemplate>> app_xml_templates;
  dbo::ptr<TemplateApp> template_app;

  template <class Action>
  void persist(Action &a)
  {
    dbo::field(a, name, "name");
    dbo::hasMany(a, app_xml_templates, dbo::ManyToOne, "app_template_file"); // one-to-many relationship
    dbo::belongsTo(a, template_app, "template_app");                         // many-to-one relationship
  }
};
