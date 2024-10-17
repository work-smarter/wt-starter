#include "101-Stylus/Stylus.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/PanelDialogs/RightPanel.h"
#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/PanelDialogs/SettingsPanel.h"
#include "101-Stylus/PanelDialogs/QuickCommandsPanel.h"

#include <Wt/WApplication.h>

Stylus::Stylus(Session &session, Wt::WString app_name, Wt::WString templates_root_path)
    : session_(session),
      templates_root_path_(templates_root_path)
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

    left_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<LeftPanel>(this));
    right_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<RightPanel>(this));
    edditor_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<EdditorPanel>(this));
    settings_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<SettingsPanel>(this));
    quick_commands_panel_ = Wt::WApplication::instance()->root()->addChild(std::make_unique<QuickCommandsPanel>(this));

    left_panel_->setHidden(!settings_panel_->stylus_state_.left_active_);
    right_panel_->setHidden(!settings_panel_->stylus_state_.right_active_);
    edditor_panel_->setHidden(!settings_panel_->stylus_state_.edditor_active_);
    settings_panel_->setHidden(!settings_panel_->stylus_state_.settings_active_);
    quick_commands_panel_->setHidden(!settings_panel_->stylus_state_.quick_commands_active_);

    Wt::WApplication::instance()->globalKeyWentDown().connect([=](Wt::WKeyEvent e)
                                                              { std::cout << "\n\n process from stylus brain \n\n"; processKeyEvent(e); });
}

void Stylus::setXmlBrain(std::shared_ptr<XMLBrain> xml_brain)
{
    std::cout << "\n\n setXmlBrain \n\n";

    if (xml_brain_)
    {
        if (xml_brain_ != xml_brain)
        {
            if (xml_brain_->dbo_temp_data_.temp_type == xml_brain->dbo_temp_data_.temp_type)
            {
                if (xml_brain_->dbo_temp_data_.temp_file.toUTF8().compare(xml_brain->dbo_temp_data_.temp_file.toUTF8()))
                {
                    xml_brain_->selected_node_ = nullptr;
                    node_selected().emit();
                }
            }
        }
    }

    xml_brain_ = xml_brain;
    node_selected().emit();
}

void Stylus::readDefaultXmlFile(Wt::WString file_path)
{
    file_path = templates_root_path_ + file_path;
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file_path.toUTF8().c_str());
    std::cout << "\n\n file_path: " << file_path.toUTF8() << "\n\n";
    tinyxml2::XMLElement *messages = doc.FirstChildElement("messages");
    if (!messages)
    {
        std::cerr << "\n Error: No 'messages' element found in the xml file.\n";
        return;
    }
    Wt::WString file_name = file_path.toUTF8().substr(file_path.toUTF8().find_last_of("/") + 1, file_path.toUTF8().length());
    auto transaction = Dbo::Transaction(session_);

    // create the templateFile reccord
    auto template_file = std::make_unique<TemplateFile>();
    template_file->name = file_name;
    auto template_file_ptr = session_.add(std::move(template_file));

    tinyxml2::XMLElement *message = messages->FirstChildElement("message");
    for (message; message; message = message->NextSiblingElement("message"))
    {
        std::string id = message->Attribute("id");
        Wt::WString value = "";
        for (auto node = message->FirstChild(); node; node = node->NextSibling())
        {
            tinyxml2::XMLPrinter printer;
            node->Accept(&printer);
            value += printer.CStr();
        }
        std::cout << "\n id: " << id << " value: " << value;
        auto xml_template = std::make_unique<XmlTemplate>();
        xml_template->temp_id = id;
        xml_template->xml_temp = value;
        xml_template->template_files = template_file_ptr;
        session_.add(std::move(xml_template));
    }

    transaction.commit();
}

void Stylus::readAppXmlFile(Wt::WString app_name, Wt::WString file_path)
{
    file_path = templates_root_path_ + file_path;
    Wt::WString file_name = file_path.toUTF8().substr(file_path.toUTF8().find_last_of("/") + 1, file_path.toUTF8().length());

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
    template_file->name = file_name;
    template_file->template_app = app;
    auto template_file_ptr = session_.add(std::move(template_file));

    tinyxml2::XMLElement *message = messages->FirstChildElement("message");
    for (message; message; message = message->NextSiblingElement("message"))
    {
        std::string id = message->Attribute("id");
        Wt::WString value = "";
        for (auto node = message->FirstChild(); node; node = node->NextSibling())
        {
            tinyxml2::XMLPrinter printer;
            node->Accept(&printer);
            value += printer.CStr();
        }
        std::cout << "\n id: " << id << " value: " << value;
        auto xml_template = std::make_unique<AppXmlTemplate>();
        xml_template->temp_id = id;
        xml_template->xml_temp = value;
        xml_template->app_template_files = template_file_ptr;
        session_.add(std::move(xml_template));
    }

    transaction.commit();
}

void Stylus::writeAppFile(Wt::WString app_name, Wt::WString file_name, Wt::WString destination_file_path)
{
    auto file_path = templates_root_path_ + app_name + "/" + file_name;
    destination_file_path = templates_root_path_ + app_name + "/" + destination_file_path;
    auto transaction = Dbo::Transaction(session_);

    // find app id by app name
    auto app = session_.find<TemplateApp>().where("app_name = ?").bind(app_name).resultValue();
    if (!app)
    {
        std::cerr << "\n Error: No app found with the name: " << app_name << "\n";
        return;
    }

    // find the template file by app id and file path
    auto app_templates = session_.find<AppTemplateFile>().where("app_template_file.template_app_id = ?").bind(app);
    auto template_file = app_templates.where("name = ?").bind(file_name).resultValue();
    if (!template_file)
    {
        std::cerr << "\n Error: No template file found with the path: " << file_path << "\n";
        return;
    }

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode *messages = doc.NewElement("messages");
    doc.InsertFirstChild(messages);

    for (auto xml_template : template_file->app_xml_templates)
    {
        // std::cout << "\n " << xml_template->xml_temp.toUTF8().c_str() << "\n";
        auto message = messages->InsertEndChild(doc.NewElement("message"));
        message->ToElement()->SetAttribute("dbo_id", std::to_string(xml_template.id()).c_str());
        message->ToElement()->SetAttribute("id", xml_template->temp_id.toUTF8().c_str());
        tinyxml2::XMLDocument temp_doc;
        temp_doc.Parse(xml_template->xml_temp.toUTF8().c_str());
        auto child = temp_doc.FirstChild();
        for (child; child; child = child->NextSibling())
        {
            auto new_child = child->DeepClone(&doc);
            message->InsertEndChild(new_child);
        }
    }

    doc.SaveFile(destination_file_path.toUTF8().c_str());
    std::cout << "\n\n file saved to: " << destination_file_path.toUTF8().c_str() << "\n\n";
    transaction.commit();
}

void Stylus::writeDefaultFile(Wt::WString file_name, Wt::WString destination_file_path)
{
    auto file_path = templates_root_path_ + default_folder_name + "/" + file_name;
    destination_file_path = templates_root_path_ + default_folder_name + "/" + destination_file_path;
    auto transaction = Dbo::Transaction(session_);

    auto template_file = session_.find<TemplateFile>().where("name = ?").bind(file_name).resultValue();
    if (!template_file)
    {
        std::cerr << "\n Error: No template file found with the path: " << file_path << "\n";
        return;
    }

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLNode *messages = doc.NewElement("messages");
    doc.InsertFirstChild(messages);

    for (auto xml_template : template_file->xml_templates)
    {
        // std::cout << "\n " << xml_template->xml_temp.toUTF8().c_str() << "\n";
        auto message = messages->InsertEndChild(doc.NewElement("message"));
        message->ToElement()->SetAttribute("dbo_id", std::to_string(xml_template.id()).c_str());
        message->ToElement()->SetAttribute("id", xml_template->temp_id.toUTF8().c_str());
        tinyxml2::XMLDocument temp_doc;
        temp_doc.Parse(xml_template->xml_temp.toUTF8().c_str());
        auto child = temp_doc.FirstChild();
        if (child)
        {
            for (child; child; child = child->NextSibling())
            {
                auto new_child = child->DeepClone(&doc);
                message->InsertEndChild(new_child);
            }
        }
        else
        {
            auto text_node = doc.NewText(xml_template->xml_temp.toUTF8().c_str());
            message->InsertEndChild(text_node);
        }
    }

    doc.SaveFile(destination_file_path.toUTF8().c_str());
    std::cout << "\n\n file saved to: " << destination_file_path.toUTF8().c_str() << "\n\n";
    transaction.commit();
}

void Stylus::processKeyEvent(Wt::WKeyEvent e)
{
    std::cout << "\n\n processKeyEvent: \n\n";

    if (e.modifiers().test(Wt::KeyboardModifier::Alt))
    {
        std::cout << "\n\n Alt key is pressed \n\n";
        if (e.key() == Wt::Key::Key_1)
        {
            settings_panel_->toggleLeftDialogActive();
        }
        else if (e.key() == Wt::Key::Key_3)
        {
            settings_panel_->toggleRightDialogActive();
        }
        else if (e.key() == Wt::Key::Key_5)
        {
            settings_panel_->toggleQuickCommandsDialogActive();
        }
        else if (e.key() == Wt::Key::Key_7)
        {
            settings_panel_->toggleEdditorDialogActive();
        }
        else if (e.key() == Wt::Key::Key_9)
        {
            settings_panel_->toggleSettingsDialogActive();
        }
    }
}