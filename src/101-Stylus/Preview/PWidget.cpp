#include "101-Stylus/Preview/PWidget.h"
#include "101-Stylus/Stylus.h"

PWidget::PWidget(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node)
    : xml_brain_(xml_brain),
      node_(node)
{
  clicked().preventPropagation();
  doubleClicked().preventPropagation();

  clicked().connect([=]
                    {
                        if(xml_brain_->stylus_->xml_brain_){
                            xml_brain_->stylus_->xml_brain_->selected_node_->node_selected().emit(false);
                        }
                        xml_brain_->selected_node_ = node;
                        xml_brain_->stylus_->setXmlBrain(xml_brain_); });
}