#pragma once
#include <Wt/WTemplate.h>
#include <Wt/WFileUpload.h>
// #include <Wt/WFileDropWidget.h>
#include <Wt/WImage.h>
#include "002-Dbo/Session.h"
#include <Wt/WProgressBar.h>

class PhotoUpload : public Wt::WTemplate
{
public:
    PhotoUpload(std::string photo_url, Session &session);
    // Wt::WFileDropWidget *file_upload_;
    Wt::WFileUpload *file_upload_;
    Wt::WImage *image_;

private:
    Session &session_;
    void fileUploaded();
    void fileChanged();
    void fileToLarge();
};