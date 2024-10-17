#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/Stylus.h"
#include "101-Stylus/Preview/PElement.h"

EdditorPanel::EdditorPanel(Stylus *stylus)
    : BaseDialogPanel(stylus),
      display_set_group_(std::make_shared<Wt::WButtonGroup>())
{
    // contents()->addStyleClass("!text-black flex border-x border-solid border-gray-400");
    // titleBar()->addStyleClass("!text-black");
    setOffsets(0, Wt::Side::Top | Wt::Side::Bottom | Wt::Side::Left | Wt::Side::Right);
    // setOffsets(0, Wt::Side::Top | Wt::Side::Bottom);
    // setOffsets(450, Wt::Side::Right);
    // setOffsets(380, Wt::Side::Left);

    header_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    content_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    header_wrapper_->setStyleClass("flex items-start border-solid border-b border-gray-600");
    content_wrapper_->setStyleClass("flex items-start h-[calc(100%-31px)]");
    auto radio_checkbox_btn_styles_ = "[&>input]:hidden "
                                      "m-0.5 mb-1 "
                                      "[&>span]:bg-gray-900 "
                                      "[&>span]:text-bold "
                                      "[&>span]:text-gray-200 "
                                      "[&>span]:p-0.5 "
                                      "[&>span]:px-1 "
                                      "[&>span]:border-2 "
                                      "[&>span]:border-solid "
                                      "[&>span]:border-gray-600 "
                                      "[&>span]:rounded-md "
                                      "[&>input:checked~span]:bg-gray-300 "
                                      "[&>input:checked~span]:text-gray-900";

    auto default_btn = header_wrapper_->addWidget(std::make_unique<Wt::WRadioButton>("Default"));
    default_btn->setStyleClass(radio_checkbox_btn_styles_);
    display_set_group_->addButton(default_btn);
    default_btn->checked().connect([=]
                                   { createDefaultDisplay(); });

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::collection<dbo::ptr<TemplateApp>> apps = stylus_->session_.find<TemplateApp>();
    for (auto app : apps)
    {
        auto app_btn = header_wrapper_->addWidget(std::make_unique<Wt::WRadioButton>(app->app_name));
        app_btn->setStyleClass(radio_checkbox_btn_styles_);
        display_set_group_->addButton(app_btn);
        app_btn->checked().connect([=]
                                   { createAppDisplay(app->app_name); });
    }

    display_set_group_->setCheckedButton(default_btn);
    default_btn->checked().emit();

    transaction.commit();
}

void EdditorPanel::createDefaultDisplay()
{
    content_wrapper_->clear();

    auto files_menu = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto file_content = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    files_menu->setStyleClass("flex flex-col items-start h-full p-2 overflow-y-auto min-w-fit");
    file_content->setStyleClass("flex flex-col items-start grow h-full p-2 overflow-y-auto");

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::collection<dbo::ptr<TemplateFile>> files = stylus_->session_.find<TemplateFile>();
    for (auto file : files)
    {
        // remove the templates_root_path_
        auto file_btn = files_menu->addWidget(std::make_unique<Wt::WText>(file->name));
        std::vector<XmlDboRecord> xml_temp_objects;
        for (auto xml_template : file->xml_templates)
        {
            XmlDboRecord temp_obj;
            temp_obj.temp_type = XMLTempType::DEFAULT;
            temp_obj.temp_file = file->name;
            temp_obj.id = std::to_string(xml_template.id());
            temp_obj.temp_id = xml_template->temp_id;
            temp_obj.xml_temp = xml_template->xml_temp;
            xml_temp_objects.push_back(temp_obj);
        }
        file_btn->setStyleClass("cursor-pointer hover:bg-gray-900 p-1 bg-gray-1000 rounded-md w-full");
        file_btn->clicked().connect([=]
                                    {
                                        file_content->clear();
                                        createFileTemplates(xml_temp_objects, file_content); });
    }
    transaction.commit();
}

void EdditorPanel::createAppDisplay(Wt::WString app_name)
{
    content_wrapper_->clear();

    auto files_menu = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto file_content = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    files_menu->setStyleClass("flex flex-col items-start h-full p-2 overflow-y-auto min-w-fit");
    file_content->setStyleClass("flex flex-col items-start grow h-full p-2 overflow-y-auto");

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::ptr<TemplateApp> app = stylus_->session_.find<TemplateApp>().where("app_name = ?").bind(app_name).resultValue();
    if (!app)
    {
        std::cerr << "\n Error: No app found with the name: " << app_name << "\n";
        return;
    }

    dbo::collection<dbo::ptr<AppTemplateFile>> app_files = app->xml_template_files;
    for (auto app_file : app_files)
    {
        // remove the templates_root_path_
        auto file_btn = files_menu->addWidget(std::make_unique<Wt::WText>(app_file->name));
        std::vector<XmlDboRecord> xml_temp_objects;
        for (auto xml_template : app_file->app_xml_templates)
        {
            XmlDboRecord temp_obj;
            temp_obj.temp_type = XMLTempType::APP;
            temp_obj.temp_file = app_file->name;
            temp_obj.app_name = app_name;
            temp_obj.id = std::to_string(xml_template.id());
            temp_obj.temp_id = xml_template->temp_id;
            temp_obj.xml_temp = xml_template->xml_temp;
            xml_temp_objects.push_back(temp_obj);
        }
        file_btn->setStyleClass("cursor-pointer hover:bg-gray-900 p-1 bg-gray-1000 rounded-md w-full");
        file_btn->clicked().connect([=]
                                    {
                                        file_content->clear();
                                        createFileTemplates(xml_temp_objects, file_content); });
    }
}

void EdditorPanel::createFileTemplates(std::vector<XmlDboRecord> xml_temp_objects, Wt::WContainerWidget *wrapper)
{
    for (auto xml_temp_obj : xml_temp_objects)
    {
        auto temp_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
        auto temp = temp_wrapper->addWidget(std::make_unique<Wt::WTemplate>(xml_temp_obj.xml_temp));
        temp->addFunction("tr", &WTemplate::Functions::tr);
        temp_wrapper->setStyleClass("relative p-2 rounded-md m-2 border border-solid border-gray-500 bg-white min-w-fit");
        auto temp_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.temp_id));
        temp_id_widget->setStyleClass("absolute -top-4 left-6 bg-gray-300 p-0.5 rounded-md text-nowrap");
        auto temp_dbo_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.id + " "));
        temp_dbo_id_widget->setStyleClass("absolute -top-4 left-0 bg-gray-300 p-0.5 px-1 rounded-md text-nowrap cursor-pointer");

        temp->hide();
        std::shared_ptr<XMLBrain> xml_brain = std::make_shared<XMLBrain>(stylus_->session_, xml_temp_obj, stylus_);
        auto pElem = temp_wrapper->addWidget(std::make_unique<PElement>(xml_brain, xml_brain->message_node_));

        temp_dbo_id_widget->clicked().connect([=]
                                              {
                                        if (temp->isHidden())
                                        {
                                            temp->show();
                                            pElem->hide();
                                        }
                                        else
                                        {
                                            temp->hide();
                                            pElem->show();
                                        } });
        xml_brain->stylus_->node_selected().connect([=]
                                                    {
                                                        if (xml_brain != stylus_->xml_brain_)
                                                            return;

                                                        temp_wrapper->clear();
                                                        auto temp = temp_wrapper->addWidget(std::make_unique<Wt::WTemplate>(xml_temp_obj.xml_temp));
                                                        temp->addFunction("tr", &WTemplate::Functions::tr);
                                                        temp_wrapper->setStyleClass("relative p-2 rounded-md m-2 border border-solid border-gray-500 bg-white");
                                                        auto temp_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.temp_id));
                                                        temp_id_widget->setStyleClass("absolute -top-4 left-6 bg-gray-300 p-0.5 rounded-md text-nowrap");
                                                        auto temp_dbo_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.id + " "));
                                                        temp_dbo_id_widget->setStyleClass("absolute -top-4 left-0 bg-gray-300 p-0.5 px-1 rounded-md text-nowrap cursor-pointer");

                                                        temp->hide();
                                                        auto pElem = temp_wrapper->addWidget(std::make_unique<PElement>(xml_brain, xml_brain->message_node_));

                                                        temp_dbo_id_widget->clicked().connect([=]
                                                                                              {
                                        if (temp->isHidden())
                                        {
                                            temp->show();
                                            pElem->hide();
                                        }
                                        else
                                        {
                                            temp->hide();
                                            pElem->show();
                                        } }); });
    }
}
