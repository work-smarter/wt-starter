#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/Stylus.h"
#include "101-Stylus/PanelDialogs/LeftPanel.h"
#include "101-Stylus/Preview/PElement.h"
#include <Wt/WDialog.h>
#include <Wt/WApplication.h>
#include <Wt/WLabel.h>
#include <Wt/WLineEdit.h>

EdditorPanel::EdditorPanel(Stylus *stylus)
    : BaseDialogPanel(stylus)
{
    // contents()->addStyleClass("!text-black flex border-x border-solid border-gray-400");
    // titleBar()->addStyleClass("!text-black");
    // setOffsets(0, Wt::Side::Top | Wt::Side::Bottom | Wt::Side::Right);
    setOffsets(0, Wt::Side::Top | Wt::Side::Bottom);
    setOffsets(450, Wt::Side::Right);
    setOffsets(380, Wt::Side::Left);

    header_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    content_wrapper_ = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    files_menu_ = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    file_content_ = content_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    files_menu_->setStyleClass("flex flex-col items-start h-full p-2 overflow-y-auto min-w-fit");
    file_content_->setStyleClass("flex flex-col items-start grow h-full p-2 overflow-y-auto");

    header_wrapper_->setStyleClass("flex items-center border-solid border-b border-gray-600");
    button_btn_group_wrapper_ = header_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto utility_btns_wrapper = header_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto test_btns_wrapper = header_wrapper_->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto add_temps_to_dbo_btn = test_btns_wrapper->addWidget(std::make_unique<Wt::WPushButton>("Add Temps"));
    add_temps_to_dbo_btn->clicked().connect([=]()
                                            {
                                                stylus_->addFileToDbo("default", "overide-wt/test.xml");
                                                stylus_->addFileToDbo("default", "../base-templates/default/app.xml");
                                                stylus_->addFileToDbo("default", "../base-templates/default/strings.xml");
                                                stylus_->addFileToDbo("default", "../base-templates/default/auth.xml");
                                                stylus_->addFileToDbo("default", "../base-templates/default/auth_strings.xml");
                                                stylus_->addFileToDbo("default", "../base-templates/default/calendar.xml");

                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/stylus-flex-and-grid-svgs.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-accesibility.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-backgrounds.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-borders.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-effects.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-filters.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-flex-and-grid.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-interactivity.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-Layout.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-sizing.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-spacing.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-svg.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-tables.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-transform.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-transition-and-animation.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-typography.xml");
                                                stylus_->addFileToDbo("stylus", "../base-templates/stylus/tconf-variants.xml"); });
    auto get_temps_from_dbo_btn = test_btns_wrapper->addWidget(std::make_unique<Wt::WPushButton>("Get Temps"));
    get_temps_from_dbo_btn->clicked().connect([=]()
                                              {
                                                // stylus_->saveFileFromDbo("default", "test.xml");
                                                stylus_->saveFileFromDbo("default", "app.xml");
                                                stylus_->saveFileFromDbo("default", "auth_strings.xml");
                                                stylus_->saveFileFromDbo("default", "auth.xml");
                                                stylus_->saveFileFromDbo("default", "calendar.xml"); 
                                                stylus_->saveFileFromDbo("stylus", "stylus-flex-and-grid-svgs.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-accesibility.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-backgrounds.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-borders.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-effects.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-filters.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-flex-and-grid.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-interactivity.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-Layout.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-sizing.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-spacing.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-svg.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-tables.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-transform.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-transition-and-animation.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-typography.xml");
                                                stylus_->saveFileFromDbo("stylus", "tconf-variants.xml"); });
    button_btn_group_wrapper_->setStyleClass("flex");
    test_btns_wrapper->setStyleClass("flex");
    utility_btns_wrapper->setStyleClass("ml-auto mr-3");
    add_temps_to_dbo_btn->setStyleClass("btn-style-1 !p-0.5 mr-3");
    get_temps_from_dbo_btn->setStyleClass("btn-style-1 !p-0.5 mr-3");
    content_wrapper_->setStyleClass("flex items-start h-[calc(100%-31px)]");
    radio_checkbox_btn_styles_ = "[&>input]:hidden "
                                 "m-0.5 mb-1 "
                                 "[&>span]:bg-gray-200 "
                                 "[&>span]:text-bold "
                                 "[&>span]:text-gray-900 "
                                 "[&>span]:p-0.5 "
                                 "[&>span]:px-1 "
                                 "[&>span]:border-2 "
                                 "[&>span]:border-solid "
                                 "[&>span]:border-gray-600 "
                                 "[&>span]:rounded-md "
                                 "[&>input:checked~span]:bg-gray-900 "
                                 "[&>input:checked~span]:text-gray-200";
    createFoldersMenu();

    // add folder button
    auto add_folder_btn = utility_btns_wrapper->addWidget(std::make_unique<Wt::WPushButton>("+"));
    add_folder_btn->setStyleClass("btn-style-1 !p-0.5");

    add_folder_btn->clicked().connect([=]
                                      {
                                          auto add_folder_dialog = Wt::WApplication::instance()->root()->addChild(std::make_unique<Wt::WDialog>("Add Folder"));
                                          add_folder_dialog->setStyleClass("!border-0 shadow-lg rounded-xl overflow-x-visible");
                                          add_folder_dialog->titleBar()->children()[0]->removeFromParent();
                                          add_folder_dialog->titleBar()->hide();
                                          add_folder_dialog->titleBar()->setStyleClass("p-0 bg-gray-500 flex items-center overflow-x-visible h-[40px]");
                                          add_folder_dialog->contents()->setStyleClass("flex flex-col items-start p-2 h-full bg-gray-800 overflow-y-auto overflow-x-visible");

                                          int zIndex = this->zIndex() + 1;
                                          add_folder_dialog->setTabIndex(zIndex);
                                          add_folder_dialog->setModal(false);
                                          add_folder_dialog->setResizable(false);
                                          add_folder_dialog->setMovable(false);
                                          add_folder_dialog->rejectWhenEscapePressed();
                                          add_folder_dialog->show();

                                          auto label = add_folder_dialog->contents()->addWidget(std::make_unique<Wt::WLabel>("Folder name"));
                                          auto error_text = add_folder_dialog->contents()->addWidget(std::make_unique<Wt::WText>());
                                          auto input = add_folder_dialog->contents()->addWidget(std::make_unique<Wt::WLineEdit>());
                                          label->setStyleClass("text-gray-200");
                                          error_text->setStyleClass("text-red-500");
                                          input->setStyleClass("input-style-1");
                                          label->setBuddy(input);

                                          input->enterPressed().connect([=]()
                                                                        {
                                                                            auto transaction = Dbo::Transaction(stylus_->session_);
                                                                            auto folder_search_result = stylus_->session_.find<TemplateFolder>().where("folder_name = ?").bind(input->text()).resultValue();
                                                                            if (folder_search_result){
                                                                                error_text->setText("Folder with the same name already exists");
                                                                            }else {
                                                                                auto folder = std::make_unique<TemplateFolder>();
                                                                                folder->folder_name = input->text();
                                                                                stylus_->session_.add(std::move(folder));
                                                                                transaction.commit();
                                                                                createFoldersMenu();
                                                                                add_folder_dialog->accept();
                                                                            }
                                                                        }); });
}

void EdditorPanel::createFoldersMenu()
{
    display_set_group_ = std::make_shared<Wt::WButtonGroup>();
    button_btn_group_wrapper_->clear();

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::collection<dbo::ptr<TemplateFolder>> template_folders = stylus_->session_.find<TemplateFolder>();
    for (auto folder : template_folders)
    {
        auto folder_btn = button_btn_group_wrapper_->addWidget(std::make_unique<Wt::WRadioButton>(folder->folder_name));
        folder_btn->setStyleClass(radio_checkbox_btn_styles_);
        display_set_group_->addButton(folder_btn);
        folder_btn->checked().connect([=]
                                      { createFolderDisplay(folder.id()); });
    }

    transaction.commit();

    display_set_group_->setCheckedButton(0);
    display_set_group_->button(0)->setChecked(true);
    display_set_group_->button(0)->checked().emit();
}

void EdditorPanel::createFolderDisplay(int folder_id)
{
    files_menu_->clear();
    file_content_->clear();

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::ptr<TemplateFolder> template_folder = stylus_->session_.find<TemplateFolder>().where("id = ?").bind(std::to_string(folder_id)).resultValue();
    if (!template_folder)
    {
        std::cerr << "\n Error: No folder found with the id: " << folder_id << "\n";
        return;
    }

    dbo::collection<dbo::ptr<TemplateFile>> template_files = template_folder->template_files;
    for (auto file : template_files)
    {
        auto file_btn = files_menu_->addWidget(std::make_unique<Wt::WText>(file->file_name));
        file_btn->setStyleClass("cursor-pointer hover:bg-gray-300 p-1 bg-gray-1000 rounded-md w-full");
        file_btn->clicked().connect([=]
                                    { 
                                        createFileTemplates(file.id());
                                        stylus_->xml_brain_ = nullptr;
                                        stylus_->left_panel_->createTree(); });
    }
    transaction.commit();
}

void EdditorPanel::createFileTemplates(int file_id)
{
    auto transaction = Dbo::Transaction(stylus_->session_);

    auto file = stylus_->session_.find<TemplateFile>().where("id = ?").bind(std::to_string(file_id)).resultValue();

    if (!file)
    {
        std::cerr << "\n Error: No file found with the id: " << file_id << "\n";
        return;
    }

    file_content_->clear();
    for (auto xml_template : file->xml_templates)
    {
        auto temp_wrapper = file_content_->addWidget(std::make_unique<Wt::WContainerWidget>());
        auto temp = temp_wrapper->addWidget(std::make_unique<Wt::WTemplate>(xml_template->xml_temp));
        temp->addFunction("tr", &WTemplate::Functions::tr);
        temp_wrapper->setStyleClass("relative p-2 rounded-md m-2 border border-solid border-gray-500 bg-white min-w-fit");
        auto temp_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(std::to_string(xml_template.id())));
        temp_id_widget->setStyleClass("absolute -top-4 left-6 bg-gray-300 p-0.5 rounded-md text-nowrap");
        auto temp_dbo_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_template->temp_id));
        temp_dbo_id_widget->setStyleClass("absolute -top-4 left-0 bg-gray-300 p-0.5 px-1 rounded-md text-nowrap cursor-pointer");

        XmlDboRecord xml_temp_obj;
        xml_temp_obj.dbo_folder_id = file->template_folder.id();
        xml_temp_obj.dbo_file_id = file.id();
        xml_temp_obj.dbo_temp_id = xml_template.id();
        xml_temp_obj.file_name = file->file_name;
        xml_temp_obj.folder_name = file->template_folder->folder_name;
        xml_temp_obj.temp_id = xml_template->temp_id;
        xml_temp_obj.xml_temp = xml_template->xml_temp;

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
    }
    transaction.commit();
}
// for (auto xml_temp_obj : xml_temp_objects)
// {
// auto temp_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
// auto temp = temp_wrapper->addWidget(std::make_unique<Wt::WTemplate>(xml_temp_obj.xml_temp));
// temp->addFunction("tr", &WTemplate::Functions::tr);
// temp_wrapper->setStyleClass("relative p-2 rounded-md m-2 border border-solid border-gray-500 bg-white min-w-fit");
// auto temp_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.temp_id));
// temp_id_widget->setStyleClass("absolute -top-4 left-6 bg-gray-300 p-0.5 rounded-md text-nowrap");
// auto temp_dbo_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.dbo_temp_id + " "));
// temp_dbo_id_widget->setStyleClass("absolute -top-4 left-0 bg-gray-300 p-0.5 px-1 rounded-md text-nowrap cursor-pointer");

// temp->hide();
// std::shared_ptr<XMLBrain> xml_brain = std::make_shared<XMLBrain>(stylus_->session_, xml_temp_obj, stylus_);
// auto pElem = temp_wrapper->addWidget(std::make_unique<PElement>(xml_brain, xml_brain->message_node_));

// temp_dbo_id_widget->clicked().connect([=]
//                                       {
//     if (temp->isHidden())
//     {
//         temp->show();
//         pElem->hide();
//     }
//     else
//     {
//         temp->hide();
//         pElem->show();
//     } });
//     xml_brain->node_selected().connect([=]
//                                        {
//                     if(temp_wrapper == nullptr) return;
//                     std::cout << "\n\n node_selected \n\n";
//                     temp_wrapper->clear();
//                     std::cout << "\n\n node_selected \n\n";

//                     auto temp = temp_wrapper->addWidget(std::make_unique<Wt::WTemplate>(xml_temp_obj.xml_temp));
//                     temp->addFunction("tr", &WTemplate::Functions::tr);
//                     temp_wrapper->setStyleClass("relative p-2 rounded-md m-2 border border-solid border-gray-500 bg-white");
//                     auto temp_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.temp_id));
//                     temp_id_widget->setStyleClass("absolute -top-4 left-6 bg-gray-300 p-0.5 rounded-md text-nowrap");
//                     auto temp_dbo_id_widget = temp_wrapper->addWidget(std::make_unique<Wt::WText>(xml_temp_obj.dbo_temp_id + " "));
//                     temp_dbo_id_widget->setStyleClass("absolute -top-4 left-0 bg-gray-300 p-0.5 px-1 rounded-md text-nowrap cursor-pointer");

//                     temp->hide();
//                     auto pElem = temp_wrapper->addWidget(std::make_unique<PElement>(xml_brain, xml_brain->message_node_));

//                     temp_dbo_id_widget->clicked().connect([=]
//                                                             {
//                             if (temp->isHidden())
//                             {
//                                 temp->show();
//                                 pElem->hide();
//                             }
//                             else
//                             {
//                                 temp->hide();
//                                 pElem->show();
//                     } }); });
// }