#include "101-Stylus/PanelDialogs/EdditorPanel.h"
#include "101-Stylus/Stylus.h"

EdditorPanel::EdditorPanel(Stylus *stylus)
    : BaseDialogPanel(stylus),
      display_set_group_(std::make_shared<Wt::WButtonGroup>())
{
    // contents()->addStyleClass("!text-black flex border-x border-solid border-gray-400");
    // titleBar()->addStyleClass("!text-black");
    setOffsets(0, Wt::Side::Top | Wt::Side::Bottom);
    setOffsets(450, Wt::Side::Right);
    setOffsets(380, Wt::Side::Left);
    auto header = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    auto content = contents()->addWidget(std::make_unique<Wt::WContainerWidget>());
    header->setStyleClass("flex items-start border-solid border-b border-gray-600");

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

    auto default_btn = header->addWidget(std::make_unique<Wt::WRadioButton>("Default"));
    default_btn->setStyleClass(radio_checkbox_btn_styles_);
    display_set_group_->addButton(default_btn);

    auto transaction = Dbo::Transaction(stylus_->session_);
    dbo::collection<dbo::ptr<TemplateApp>> apps = stylus_->session_.find<TemplateApp>();
    for (auto app : apps)
    {
        auto app_btn = header->addWidget(std::make_unique<Wt::WRadioButton>(app->app_name));
        app_btn->setStyleClass(radio_checkbox_btn_styles_);
        display_set_group_->addButton(app_btn);
    }

    display_set_group_->setCheckedButton(default_btn);
}
