#pragma once
#include "101-Stylus/Preview/PWidget.h"
#include <Wt/WText.h>

class PTree : public PWidget
{
public:
    PTree(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);

    Wt::WContainerWidget *titleBar_;
    Wt::WContainerWidget *content_;

private:
};