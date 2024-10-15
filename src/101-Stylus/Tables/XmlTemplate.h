#pragma once
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace dbo = Wt::Dbo;

class TemplateFile;
class AppTemplateFile;

class XmlTemplate
{
public:
    Wt::WString temp_id;
    Wt::WString xml_temp;
    dbo::ptr<TemplateFile> template_files;

    template <class Action>
    void persist(Action &a)
    {
        dbo::field(a, temp_id, "temp_id");
        dbo::field(a, xml_temp, "xml_temp");
        dbo::belongsTo(a, template_files, "template_file"); // many-to-one relationship
    }
};

class AppXmlTemplate
{
public:
    Wt::WString temp_id;
    Wt::WString xml_temp;
    dbo::ptr<AppTemplateFile> app_template_files;

    template <class Action>
    void persist(Action &a)
    {
        dbo::field(a, temp_id, "temp_id");
        dbo::field(a, xml_temp, "xml_temp");
        dbo::belongsTo(a, app_template_files, "app_template_file"); // many-to-one relationship
    }
};
