#pragma once
#include <Wt/WTemplate.h>
#include <Wt/WFileUpload.h>
// #include <Wt/WFileDropWidget.h>
#include <Wt/WImage.h>
#include "002-Dbo/Session.h"
#include <Wt/WProgressBar.h>

class UserPhotoUploder : public Wt::WTemplate
{
public:
    UserPhotoUploder(Session &session);
    // Wt::WFileDropWidget *file_upload_;
    Wt::WFileUpload *photo_uploader;
    Wt::WImage *image_;

private:
    Session &session_;
    void fileUploaded();
    void fileChanged();
    void fileToLarge();
};