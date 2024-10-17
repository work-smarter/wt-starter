#pragma once
#include "101-Stylus/XMLBrain.h"
#include "100-Utils/tinyxml2/tinyxml2.h"

#include <Wt/WContainerWidget.h>

class PWidget : public Wt::WContainerWidget
{
public:
    PWidget(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);
    std::shared_ptr<XMLBrain> xml_brain_;
    tinyxml2::XMLNode *node_;

private:
};
