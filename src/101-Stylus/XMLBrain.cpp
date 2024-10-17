#include "101-Stylus/XMLBrain.h"

#include "002-Dbo/Session.h"

XMLBrain::XMLBrain(Session &session, XmlDboRecord dbo_temp_data, Stylus *stylus)
    : session_(session),
      dbo_temp_data_(dbo_temp_data),
      stylus_(stylus)
{
    xml_doc_ = new tinyxml2::XMLDocument();
    message_node_ = xml_doc_->NewElement("message");
    // message_node_->SetAttribute("dbo_id", dbo_temp_data_.id.toUTF8().c_str());
    // message_node_->SetAttribute("id", dbo_temp_data_.temp_id.toUTF8().c_str());
    xml_doc_->InsertFirstChild(message_node_);

    tinyxml2::XMLDocument temp_doc;
    temp_doc.Parse(dbo_temp_data_.xml_temp.toUTF8().c_str());
    auto child = temp_doc.FirstChild();
    if (child)
    {
        for (child; child; child = child->NextSibling())
        {
            auto new_child = child->DeepClone(xml_doc_);
            message_node_->InsertEndChild(new_child);
        }
    }
    else
    {
        // document dose not have any elements so we need to add the text content of the template to the message node
        auto text_node = xml_doc_->NewText(dbo_temp_data_.xml_temp.toUTF8().c_str());
        message_node_->InsertEndChild(text_node);
    }
}

void XMLBrain::saveXmlToDbo()
{
    auto transaction = Dbo::Transaction(session_);
    dbo::ptr<XmlTemplate> xml_template = session_.find<XmlTemplate>().where("id = ?").bind(dbo_temp_data_.id).resultValue();

    if (!xml_template)
    {
        std::cout << "\n\n no xml template found with the temp_id: " << dbo_temp_data_.temp_id << "\n\n";
    }
    else
    {
        Wt::WString value = "";
        for (auto node = message_node_->FirstChild(); node; node = node->NextSibling())
        {
            tinyxml2::XMLPrinter printer;
            node->Accept(&printer);
            value += printer.CStr();
        }

        dbo_temp_data_.xml_temp = value;

        xml_template.modify()->temp_id = dbo_temp_data_.temp_id;
        xml_template.modify()->xml_temp = dbo_temp_data_.xml_temp;
    }

    transaction.commit();
}
