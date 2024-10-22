#include "101-Stylus/Preview/PElement.h"
#include <Wt/WText.h>
#include "101-Stylus/Stylus.h"

PElement::PElement(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node)
    : PWidget(xml_brain, node)
{
    // setStyleClass("p-4 bg-red-200");
    if (xml_brain_->selected_node_ == node)
    {
        setStyleClass("?");
    }
    mouseWentOver().preventPropagation();
    mouseWentOver().connect([=]
                            { toggleStyleClass("??", true); });
    mouseWentOut().preventPropagation();
    mouseWentOut().connect([=]
                           { toggleStyleClass("??", false); });

    node_->node_selected().connect([=](bool selected)
                                   { toggleStyleClass("?", selected); });

    if (node->ToElement() == xml_brain_->message_node_)
    {
        // std::cout << "\n\n message node found with id " << xml_brain_->dbo_temp_data_.temp_id << "\n";
        // setStyleClass("p-4 bg-green-200");
    }
    else
    {
        if (node->ToElement())
        {
            if (node->ToElement()->Attribute("class"))
            {
                addStyleClass(node->ToElement()->Attribute("class"));
            }
        }
        else if (node->ToText())
        {
            auto text_value = node->ToText()->Value();

            auto text_wid_wrapper = addWidget(std::make_unique<Wt::WContainerWidget>());
            auto text = text_wid_wrapper->addWidget(std::make_unique<Wt::WText>(text_value));
            auto text_input = text_wid_wrapper->addWidget(std::make_unique<Wt::WTextArea>(text_value));

            text_input->hide();
            text->doubleClicked().connect([=]
                                          {
                                              text->hide();
                                              text_input->show(); 
                                              text_input->setFocus(); });

            text_input->enterPressed().connect([=]
                                               {
                                                    text->setText(text_input->text());
                                                    text_input->hide();
                                                    text->show();
                                                    node->ToText()->SetValue(text_input->text().toUTF8().c_str());
                                                    xml_brain_->saveXmlToDbo(); });

            text_input->setMinimumSize(Wt::WLength(300, Wt::LengthUnit::Pixel), Wt::WLength::Auto);
            text_input->escapePressed().connect([=]
                                                {
                                                    text_input->hide();
                                                    text->show(); });
        }
    }

    if (node->FirstChild())
    {
        for (auto child = node->FirstChild(); child; child = child->NextSibling())
        {
            auto child_PElement = addWidget(std::make_unique<PElement>(xml_brain_, child));
        }
    }
}