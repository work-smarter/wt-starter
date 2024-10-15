#include "101-Stylus/Stylus.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

Stylus::Stylus(Session &session, Wt::WString app_name)
    : session_(session)
{
    auto transaction = Dbo::Transaction(session_);
    auto app = session_.find<TemplateApp>().where("app_name = ?").bind(app_name).resultValue();
    if (!app)
    {
        std::cerr << "\n No app found with the name:\n creating app record: " << app_name << "\n\n";
        auto app_ptr = std::make_unique<TemplateApp>();
        app_ptr->app_name = app_name;
        app = session_.add(std::move(app_ptr));
    }
    else
    {
        std::cerr << "\n App found with the name: " << app_name << "app id is: " << app.id() << "\n\n";
    }
    transaction.commit();
}

void Stylus::readOverideWtXmlFile(Wt::WString file_path)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file_path.toUTF8().c_str());
    std::cout << "\n\n file_path: " << file_path.toUTF8() << "\n\n";
    tinyxml2::XMLElement *messages = doc.FirstChildElement("messages");
    if (!messages)
    {
        std::cerr << "\n Error: No 'messages' element found in the xml file.\n";
        return;
    }
    auto transaction = Dbo::Transaction(session_);

    // create the templateFile reccord
    auto template_file = std::make_unique<TemplateFile>();
    template_file->path = file_path;
    auto template_file_ptr = session_.add(std::move(template_file));

    tinyxml2::XMLElement *message = messages->FirstChildElement("message");
    for (message; message; message = message->NextSiblingElement("message"))
    {
        std::string id = message->Attribute("id");
        // std::string value = message->GetText() ? message->GetText() : "";
        tinyxml2::XMLPrinter printer;
        message->Accept(&printer);
        Wt::WString value = printer.CStr();
        // Wt::WString value =
        std::cout << "\n id: " << id << " value: " << value;
        auto xml_template = std::make_unique<XmlTemplate>();
        xml_template->temp_id = id;
        xml_template->xml_temp = value;
        xml_template->template_files = template_file_ptr;
        session_.add(std::move(xml_template));
    }

    transaction.commit();
}

void Stylus::readXmlFile(Wt::WString file_path, Wt::WString app_name)
{
    auto transaction = Dbo::Transaction(session_);

    // find app id by app name
    auto app = session_.find<TemplateApp>().where("app_name = ?").bind(app_name).resultValue();
    if (!app)
    {
        std::cerr << "\n Error: No app found with the name: " << app_name << "\n";
        return;
    }

    tinyxml2::XMLDocument doc;
    doc.LoadFile(file_path.toUTF8().c_str());
    std::cout << "\n\n file_path: " << file_path.toUTF8() << "\n\n";
    tinyxml2::XMLElement *messages = doc.FirstChildElement("messages");
    if (!messages)
    {
        std::cerr << "\n Error: No 'messages' element found in the xml file.\n";
        return;
    }

    // create the templateFile reccord
    auto template_file = std::make_unique<AppTemplateFile>();
    template_file->path = file_path;
    template_file->template_app = app;
    auto template_file_ptr = session_.add(std::move(template_file));

    tinyxml2::XMLElement *message = messages->FirstChildElement("message");
    for (message; message; message = message->NextSiblingElement("message"))
    {
        std::string id = message->Attribute("id");
        tinyxml2::XMLPrinter printer;
        message->Accept(&printer);
        Wt::WString value = printer.CStr();
        std::cout << "\n id: " << id << " value: " << value;
        auto xml_template = std::make_unique<AppXmlTemplate>();
        xml_template->temp_id = id;
        xml_template->xml_temp = value;
        xml_template->app_template_files = template_file_ptr;
        session_.add(std::move(xml_template));
    }

    transaction.commit();
}
