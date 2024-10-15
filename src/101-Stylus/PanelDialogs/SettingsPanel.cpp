#include "101-Stylus/PanelDialogs/SettingsPanel.h"
#include "101-Stylus/Stylus.h"

SettingsPanel::SettingsPanel(Stylus *stylus)
    : BaseDialogPanel(stylus)
{
    // addStyleClass("!text-black");
    contents()->addStyleClass("flex flex-col rounded-b-md");
    titleBar()->addStyleClass("!text-black rounded-t-md");
    setOffsets(100, Wt::Side::Top | Wt::Side::Bottom);
    setOffsets(580, Wt::Side::Right | Wt::Side::Left);

    radio_checkbox_btn_styles_ = "[&>input]:hidden "
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

    //  = stylus_brain_->getXMLBrain("config");
    // readDataFromXml();
    // createRefreshSessionsWidget();

    auto left_right_panels_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto rest_of_panels_wrapper = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    left_right_panels_wrapper->setStyleClass("flex");
    rest_of_panels_wrapper->setStyleClass("flex");

    // createLeftPanelSettings(left_right_panels_wrapper);
    // createRightPanelSettings(left_right_panels_wrapper);
    // createFilesManagerPanelSettings(rest_of_panels_wrapper);
    // createQuickCommandsPanelSettings(rest_of_panels_wrapper);
}

// void SettingsPanel::createRefreshSessionsWidget()
// {
//     auto refresh_sessions_btn = titleBar()->addWidget(std::make_unique<Wt::WText>("refresh all sessions"));

//     refresh_sessions_btn->setStyleClass("text-white h-fit bg-blue-700 hover:bg-blue-800 focus:ring-4 focus:outline-none focus:ring-blue-300 font-medium rounded-lg text-sm p-1 text-center inline-flex items-center me-2 m-1 dark:bg-blue-600 dark:hover:bg-blue-700 dark:focus:ring-blue-800");

//     refresh_sessions_btn->clicked().connect([=]
//                                             { Wt::WServer::instance()->postAll([=]
//                                                                                {
//             Wt::WApplication::instance()->messageResourceBundle().keys("");
//             Wt::WApplication::instance()->refresh();
//             Wt::WApplication::instance()->triggerUpdate(); }); });
// }

// void SettingsPanel::createRightPanelSettings(Wt::WContainerWidget *wrapper)
// {
//     auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-fit h-fit bg-gray-800 rounded-md");
//     auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
//     auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     content->setStyleClass("p-2");
//     header->addWidget(std::make_unique<Wt::WText>("Right Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

//     right_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("toggle visibility"));
//     right_toggler_->setStyleClass(radio_checkbox_btn_styles_);
//     right_toggler_->setChecked(stylus_state_.right_active_);
//     right_toggler_->changed().connect([=]()
//                                       { toggleRightDialogActive(); });

//     std::shared_ptr<Wt::WButtonGroup> panel_mode_group = std::make_shared<Wt::WButtonGroup>();
//     auto widget_mode_btns_wrapper = content->addWidget(std::make_unique<Wt::WContainerWidget>());
//     auto normal_btn = widget_mode_btns_wrapper->addWidget(std::make_unique<Wt::WRadioButton>("Normal"));
//     auto extra_btn = widget_mode_btns_wrapper->addWidget(std::make_unique<Wt::WRadioButton>("Extra"));
//     auto both_btn = widget_mode_btns_wrapper->addWidget(std::make_unique<Wt::WRadioButton>("Both"));
//     panel_mode_group->addButton(normal_btn, BasePanelMode::NORMAL);
//     panel_mode_group->addButton(extra_btn, BasePanelMode::EXTRA);
//     panel_mode_group->addButton(both_btn, BasePanelMode::BOTH);
//     normal_btn->setStyleClass(radio_checkbox_btn_styles_);
//     extra_btn->setStyleClass(radio_checkbox_btn_styles_);
//     both_btn->setStyleClass(radio_checkbox_btn_styles_);

//     if (right_dialog_panels_mode_ == BasePanelMode::NORMAL)
//     {
//         panel_mode_group->setCheckedButton(normal_btn);
//         std::cout << "\n right panel mode is normal ------------------------ \n";
//     }
//     else if (right_dialog_panels_mode_ == BasePanelMode::EXTRA)
//     {
//         panel_mode_group->setCheckedButton(extra_btn);
//         // std::cout << "\n right panel mode is extra ------------------------ \n";
//     }
//     else if (right_dialog_panels_mode_ == BasePanelMode::BOTH)
//     {
//         panel_mode_group->setCheckedButton(both_btn);
//         std::cout << "\n right panel mode is both ------------------------ \n";
//     }

//     panel_mode_group->checkedChanged().connect([=](Wt::WRadioButton *btn)
//                                                {
//         std::string new_text = "";
//         switch(panel_mode_group->checkedId()){
//             case BasePanelMode::NORMAL:
//                 right_dialog_panels_mode_ = BasePanelMode::NORMAL;
//                 new_text = "NORMAL";
//                 break;
//             case BasePanelMode::EXTRA:
//                 right_dialog_panels_mode_ = BasePanelMode::EXTRA;
//                 new_text = "EXTRA";
//                 break;
//             case BasePanelMode::BOTH:
//                 right_dialog_panels_mode_ = BasePanelMode::BOTH;
//                 new_text = "BOTH";
//                 break;
//             default:
//             new_text = "BOTH";
//             std::cout << "\n\n\n cheaslkdjf something is not working right \n\n\n";
//                 break;
//         }
//         auto right_dialog_node = xml_brain_config_->message_node_->FirstChildElement("right-dialog");
//         if (right_dialog_node)
//         {
//             if (right_dialog_node->FirstChildElement("panels-mode")){
//                 auto text_node = right_dialog_node->FirstChildElement("panels-mode")->FirstChild();
//                 text_node->SetValue(new_text.c_str());
//                 xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//             }
//         }
//         stylus_brain_->m_right_panel_d_->setPanelsMode(right_dialog_panels_mode_); });
// }
// void SettingsPanel::createLeftPanelSettings(Wt::WContainerWidget *wrapper)
// {
//     auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-fit h-fit bg-gray-800 rounded-md");
//     auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
//     auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     content->setStyleClass("p-2");
//     header->addWidget(std::make_unique<Wt::WText>("Left Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

//     left_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("toggle visibility"));
//     left_toggler_->setStyleClass(radio_checkbox_btn_styles_);
//     left_toggler_->setChecked(stylus_state_.left_active_);
//     left_toggler_->changed().connect([=]()
//                                      { toggleLeftDialogActive(); });
// }
// void SettingsPanel::createFilesManagerPanelSettings(Wt::WContainerWidget *wrapper)
// {
//     auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-fit h-fit bg-gray-800 rounded-md");
//     auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
//     auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     content->setStyleClass("p-2");
//     header->addWidget(std::make_unique<Wt::WText>("Files Manager"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

//     files_manager_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("toggle visibility"));
//     files_manager_toggler_->setStyleClass(radio_checkbox_btn_styles_);
//     files_manager_toggler_->setChecked(stylus_state_.files_manager_active_);
//     files_manager_toggler_->changed().connect([=]()
//                                               { togglefilesManagerDialogActive(); });
// }
// void SettingsPanel::createQuickCommandsPanelSettings(Wt::WContainerWidget *wrapper)
// {
//     auto panel_wrapper = wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     panel_wrapper->setStyleClass("border-2 border-solid border-gray-700 m-4 w-fit h-fit bg-gray-800 rounded-md");
//     auto header = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     header->setStyleClass("flex items-center justify-between mb-2 border-b-2 border-solid border-gray-900");
//     auto content = panel_wrapper->addWidget(std::make_unique<Wt::WContainerWidget>());
//     content->setStyleClass("p-2");
//     header->addWidget(std::make_unique<Wt::WText>("Quick Commands Panel"))->setStyleClass("text-lg font-semibold text-gray-200 mr-6 ml-2 p-0.5");

//     quick_commands_toggler_ = header->addWidget(std::make_unique<Wt::WCheckBox>("toggle visibility"));
//     quick_commands_toggler_->setStyleClass(radio_checkbox_btn_styles_);
//     quick_commands_toggler_->setChecked(stylus_state_.quick_commands_active_);
//     quick_commands_toggler_->changed().connect([=]()
//                                                { toggleQuickCommandsDialogActive(); });
// }

// void SettingsPanel::readDataFromXml()
// {

//     auto stylus_active_node = xml_brain_config_->message_node_->FirstChildElement("stylus-active");
//     if (stylus_active_node)
//     {
//         if (stylus_active_node->FirstChildElement("active"))
//         {
//             std::string value = stylus_active_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.stylus_active_ = false;
//             else
//                 stylus_state_.stylus_active_ = true;
//         }
//     }
//     auto brain_dialog_node = xml_brain_config_->message_node_->FirstChildElement("brain-dialog");
//     if (brain_dialog_node)
//     {
//         if (brain_dialog_node->FirstChildElement("active"))
//         {
//             std::string value = brain_dialog_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.brain_active_ = false;
//             else
//                 stylus_state_.brain_active_ = true;
//         }
//     }
//     auto right_dialog_node = xml_brain_config_->message_node_->FirstChildElement("right-dialog");
//     if (right_dialog_node)
//     {
//         if (right_dialog_node->FirstChildElement("active"))
//         {
//             std::string value = right_dialog_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.right_active_ = false;
//             else
//                 stylus_state_.right_active_ = true;
//         }
//         if (right_dialog_node->FirstChildElement("panels-mode"))
//         {
//             std::string right_panel_mode_string = right_dialog_node->FirstChildElement("panels-mode")->GetText();
//             if (right_panel_mode_string.compare("NORMAL") == 0)
//             {
//                 right_dialog_panels_mode_ = BasePanelMode::NORMAL;
//             }
//             else if (right_panel_mode_string.compare("EXTRA") == 0)
//             {
//                 right_dialog_panels_mode_ = BasePanelMode::EXTRA;
//             }
//             else if (right_panel_mode_string.compare("BOTH") == 0)
//             {
//                 right_dialog_panels_mode_ = BasePanelMode::BOTH;
//             }
//             else
//             {
//                 std::cout << "\n\n\n something is wrong with the right panel mode \n\n\n";
//             }
//         }
//     }
//     auto element_control_dialog_node = xml_brain_config_->message_node_->FirstChildElement("element-control-dialog");
//     if (element_control_dialog_node)
//     {
//         if (element_control_dialog_node->FirstChildElement("active"))
//         {
//             std::string value = element_control_dialog_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.left_active_ = false;
//             else
//                 stylus_state_.left_active_ = true;
//         }
//     }
//     auto left_dialog_node = xml_brain_config_->message_node_->FirstChildElement("left-dialog");
//     if (left_dialog_node)
//     {
//         if (left_dialog_node->FirstChildElement("active"))
//         {
//             std::string value = left_dialog_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.left_active_ = false;
//             else
//                 stylus_state_.left_active_ = true;
//         }
//     }
//     auto quick_dialog_node = xml_brain_config_->message_node_->FirstChildElement("quick-commands-dialog");
//     if (quick_dialog_node)
//     {
//         if (quick_dialog_node->FirstChildElement("active"))
//         {
//             std::string value = quick_dialog_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.quick_commands_active_ = false;
//             else
//                 stylus_state_.quick_commands_active_ = true;
//         }
//     }
//     auto files_manager_dialog_node = xml_brain_config_->message_node_->FirstChildElement("files-manager-dialog");
//     if (files_manager_dialog_node)
//     {
//         if (files_manager_dialog_node->FirstChildElement("active"))
//         {
//             std::string value = files_manager_dialog_node->FirstChildElement("active")->GetText();
//             if (value == "false")
//                 stylus_state_.files_manager_active_ = false;
//             else
//                 stylus_state_.files_manager_active_ = true;
//         }
//         if (files_manager_dialog_node->FirstChildElement("files-menu-minimized"))
//         {
//             std::string value = files_manager_dialog_node->FirstChildElement("files-menu-minimized")->GetText();
//             if (value == "false")
//                 stylus_state_.files_manager_files_menu_active_ = false;
//             else
//                 stylus_state_.files_manager_files_menu_active_ = true;
//         }
//         if (files_manager_dialog_node->FirstChildElement("open-folders"))
//         {
//             auto open_folders_node = files_manager_dialog_node->FirstChildElement("open-folders");
//             auto folder_node = open_folders_node->FirstChildElement("folder");
//             while (folder_node)
//             {
//                 std::string folder_name = "";
//                 if (folder_node->FirstChildElement("name"))
//                 {
//                     folder_name = folder_node->FirstChildElement("name")->GetText();
//                 }
//                 if (folder_node->Attribute("open") && std::string(folder_node->Attribute("open")) == "true")
//                 {
//                     stylus_state_.open_folders_state_[folder_name] = true;
//                 }
//                 else
//                 {
//                     stylus_state_.open_folders_state_[folder_name] = false;
//                 }
//                 folder_node = folder_node->NextSiblingElement("folder");
//             }
//         }
//     }
// }

// void SettingsPanel::toggleStylusActive()
// {
//     auto stylus_active_node = xml_brain_config_->message_node_->FirstChildElement("stylus-active");
//     if (stylus_active_node)
//     {
//         if (!stylus_state_.stylus_active_)
//         {
//             stylus_active_node->FirstChildElement("active")->SetText("true");
//             stylus_state_.stylus_active_ = true;
//         }
//         else
//         {
//             stylus_active_node->FirstChildElement("active")->SetText("false");
//             stylus_state_.stylus_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     Wt::WApplication::instance()->messageResourceBundle().keys("");
//     Wt::WApplication::instance()->refresh();
// }

// void SettingsPanel::toggleSettingsPanelActive()
// {
//     std::cout << "\n\n toggle brain dialog \n\n";
//     auto brain_dialog_node = xml_brain_config_->message_node_->FirstChildElement("brain-dialog");
//     if (brain_dialog_node)
//     {
//         std::cout << "\n " << brain_dialog_node->GetText() << "\n";
//         if (std::string(brain_dialog_node->FirstChildElement("active")->GetText()) == "false")
//         {
//             brain_dialog_node->FirstChildElement("active")->SetText("true");
//             if (stylus_state_.stylus_active_)
//                 stylus_brain_->m_brain_d_->show();
//             stylus_state_.brain_active_ = true;
//         }
//         else
//         {
//             brain_dialog_node->FirstChildElement("active")->SetText("false");
//             stylus_brain_->m_brain_d_->hide();
//             stylus_state_.brain_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
// }
// void SettingsPanel::toggleRightDialogActive()
// {
//     std::cout << "\n\n toggle control dialog \n\n";
//     auto control_dialog_node = xml_brain_config_->message_node_->FirstChildElement("right-dialog");
//     if (control_dialog_node)
//     {
//         if (std::string(control_dialog_node->FirstChildElement("active")->GetText()) == "false")
//         {
//             control_dialog_node->FirstChildElement("active")->SetText("true");
//             if (stylus_state_.stylus_active_)
//                 stylus_brain_->m_right_panel_d_->show();
//             stylus_state_.right_active_ = true;
//         }
//         else
//         {
//             control_dialog_node->FirstChildElement("active")->SetText("false");
//             stylus_brain_->m_right_panel_d_->hide();
//             stylus_state_.right_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     right_toggler_->setChecked(stylus_state_.right_active_);
// }
// void SettingsPanel::toggleLeftDialogActive()
// {
//     std::cout << "\n\n toggle control dialog \n\n";
//     auto elem_control_dialog_node = xml_brain_config_->message_node_->FirstChildElement("left-dialog");
//     if (elem_control_dialog_node)
//     {
//         if (std::string(elem_control_dialog_node->FirstChildElement("active")->GetText()) == "false")
//         {
//             elem_control_dialog_node->FirstChildElement("active")->SetText("true");
//             if (stylus_state_.stylus_active_)
//                 stylus_brain_->m_left_panel_d_->show();
//             stylus_state_.left_active_ = true;
//         }
//         else
//         {
//             elem_control_dialog_node->FirstChildElement("active")->SetText("false");
//             stylus_brain_->m_left_panel_d_->hide();
//             stylus_state_.left_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     left_toggler_->setChecked(stylus_state_.left_active_);
// }
// void SettingsPanel::toggleQuickCommandsDialogActive()
// {
//     std::cout << "\n\n quick commands dialog \n\n";
//     auto quick_commands_dialog_node = xml_brain_config_->message_node_->FirstChildElement("quick-commands-dialog");
//     if (quick_commands_dialog_node)
//     {
//         if (std::string(quick_commands_dialog_node->FirstChildElement("active")->GetText()) == "true")
//         {
//             if (!stylus_brain_->m_quick_commands_d_->line_eddit_->hasFocus())
//             {
//                 stylus_brain_->m_quick_commands_d_->line_eddit_->setFocus(true);
//             }
//             else
//             {
//                 quick_commands_dialog_node->FirstChildElement("active")->SetText("false");
//                 stylus_brain_->m_quick_commands_d_->hide();
//                 stylus_state_.quick_commands_active_ = false;
//             }
//         }
//         else
//         {
//             quick_commands_dialog_node->FirstChildElement("active")->SetText("true");
//             if (stylus_state_.stylus_active_)
//             {
//                 stylus_brain_->m_quick_commands_d_->show();
//                 stylus_brain_->m_quick_commands_d_->line_eddit_->setFocus();
//             }
//             stylus_state_.quick_commands_active_ = true;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     quick_commands_toggler_->setChecked(stylus_state_.quick_commands_active_);
// }

// void SettingsPanel::togglefilesManagerDialogActive()
// {
//     std::cout << "\n\n toggle files manager dialog \n\n";
//     auto files_manager_dialog_node = xml_brain_config_->message_node_->FirstChildElement("files-manager-dialog");
//     if (files_manager_dialog_node)
//     {
//         if (std::string(files_manager_dialog_node->FirstChildElement("active")->GetText()) == "false")
//         {
//             files_manager_dialog_node->FirstChildElement("active")->SetText("true");
//             if (stylus_state_.stylus_active_)
//                 stylus_brain_->m_files_manager_d_->show();
//             stylus_state_.files_manager_active_ = true;
//         }
//         else
//         {
//             files_manager_dialog_node->FirstChildElement("active")->SetText("false");
//             stylus_brain_->m_files_manager_d_->hide();
//             stylus_state_.files_manager_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     files_manager_toggler_->setChecked(stylus_state_.files_manager_active_);
// }
// void SettingsPanel::togglefilesManagerLeftMenuActive()
// {
//     std::cout << "\n\n toggle files manager dialog \n\n";
//     auto files_manager_dialog_node = xml_brain_config_->message_node_->FirstChildElement("files-manager-dialog");
//     if (files_manager_dialog_node)
//     {
//         if (std::string(files_manager_dialog_node->FirstChildElement("files-menu-minimized")->GetText()) == "false")
//         {
//             std::cout << "\n\n files menu is minimized true \n\n";
//             files_manager_dialog_node->FirstChildElement("files-menu-minimized")->SetText("true");
//             stylus_state_.files_manager_files_menu_active_ = true;
//         }
//         else
//         {
//             std::cout << "\n\n files menu is not minimized false \n\n";
//             files_manager_dialog_node->FirstChildElement("files-menu-minimized")->SetText("false");
//             stylus_state_.files_manager_files_menu_active_ = false;
//         }
//         xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
//         xml_brain_config_->templateChanged_.emit();
//     }
//     // stylus_brain_->m_files_manager_d_->toggle_left_menu_btn_->setChecked(stylus_state_.files_manager_files_menu_active_);
//     // stylus_brain_->m_files_manager_d_->toggle_left_menu_btn_->changed().emit();
// }

// void SettingsPanel::setFileManagerFoldersTreeState()
// {
//     std::cout << "\n\n set file manager folders tree state \n\n";
//     auto files_manager_dialog_node = xml_brain_config_->message_node_->FirstChildElement("files-manager-dialog");
//     auto open_folders_node = files_manager_dialog_node->FirstChildElement("open-folders");
//     if (!open_folders_node)
//     {
//         open_folders_node = xml_brain_config_->file_->doc_->NewElement("open-folders");
//         files_manager_dialog_node->InsertEndChild(open_folders_node);
//     }

//     // remove all child nodes from open_folder_node
//     open_folders_node->DeleteChildren();

//     for (auto folder : stylus_state_.open_folders_state_)
//     {
//         std::cout << "\n folder name is " << folder.first << " and open state is " << folder.second << "\n";
//         auto folder_node = xml_brain_config_->file_->doc_->NewElement("folder");
//         auto name_node = xml_brain_config_->file_->doc_->NewElement("name");
//         name_node->SetText(folder.first.c_str());
//         folder_node->InsertEndChild(name_node);
//         open_folders_node->InsertEndChild(folder_node);
//         if (folder.second)
//         {
//             folder_node->SetAttribute("open", "true");
//         }
//         else
//         {
//             folder_node->SetAttribute("open", "false");
//         }
//     }
//     xml_brain_config_->file_->doc_->SaveFile(xml_brain_config_->file_->path_.c_str());
// }
