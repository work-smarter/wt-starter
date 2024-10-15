#pragma once
#include <Wt/WTemplate.h>
#include <Wt/WFileUpload.h>
// #include <Wt/WFileDropWidget.h>
#include <Wt/WImage.h>
#include "002-Dbo/Session.h"
#include <Wt/WProgressBar.h>
#include <Wt/WPushButton.h>

class UserPhotoUploder : public Wt::WTemplate
{
public:
    UserPhotoUploder(Session &session);
    // Wt::WFileDropWidget *file_upload_;
    Wt::WFileUpload *photo_uploader;
    Wt::WImage *image_;
    Wt::WPushButton *upload_btn;

private:
    Session &session_;
    void fileUploaded();
    void fileChanged();
    void fileToLarge();
};