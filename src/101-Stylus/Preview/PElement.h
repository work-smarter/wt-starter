#pragma once
#include "101-Stylus/Preview/PWidget.h"
#include <Wt/WLineEdit.h>
#include <Wt/WTextArea.h>

class PElement : public PWidget
{
public:
    PElement(std::shared_ptr<XMLBrain> xml_brain, tinyxml2::XMLNode *node);

private:
};