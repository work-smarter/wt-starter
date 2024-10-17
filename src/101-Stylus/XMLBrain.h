#pragma once
#include "100-Utils/tinyxml2/tinyxml2.h"
#include <Wt/WString.h>

class Session;
class Stylus;

enum XMLTempType
{
    DEFAULT = 10,
    APP = 11,
    STYLUS = 12,
};

struct XmlDboRecord
{
    Wt::WString id;
    Wt::WString temp_id;
    Wt::WString xml_temp;
    XMLTempType temp_type;
};

class XMLBrain
{
public:
    XMLBrain(Session &session, XmlDboRecord dbo_temp_data, Stylus *stylus);
    tinyxml2::XMLDocument *xml_doc_;
    tinyxml2::XMLNode *message_node_;
    tinyxml2::XMLNode *selected_node_;

    void saveXmlToDbo();

    XmlDboRecord dbo_temp_data_;

    Stylus *stylus_;

private:
    Session &session_;
};