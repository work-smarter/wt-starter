#pragma once
#include "100-Utils/tinyxml2/tinyxml2.h"
#include <Wt/WString.h>
#include <boost/regex.hpp>

class Session;
class Stylus;

enum TempVarImplementationType
{
    TEMPLATE = 10,
    TEXT = 11,
    INPUT = 12,
    TEXTAREA = 13,
    BUTTON = 14,
    CHECKBOX = 15,
    RADIO = 16,
};

struct TempVarData
{
    std::string name_ = "";
    std::string style_classes_ = "";
    std::string implementation_ = "";
    TempVarImplementationType implementation_type_ = TempVarImplementationType::TEXT;
    std::string implementation_text_ = "";
};

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
    Wt::WString temp_file;
    Wt::WString folder_name;
    Wt::WString xml_temp;
    XMLTempType temp_type;
};

TempVarData tempText(tinyxml2::XMLNode *node);
std::vector<TempVarData> tempTexts(std::string text);

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