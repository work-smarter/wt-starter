#include "100-Utils/PhotoUpload.h"
#include "100-Utils/AwsConnect.h"

PhotoUpload::PhotoUpload(std::string photo_url, Session &session)
    : Wt::WTemplate(Wt::WString::tr("starter.photo.upload")),
      session_(session)
{
    // addFunction("id", &WTemplate::Functions::id);
    bindEmpty("file-info-1");
    bindEmpty("file-info-2");
    bindEmpty("file-info-3");
    bindEmpty("file-info-4");

    file_upload_ = bindWidget("file-upload", std::make_unique<Wt::WFileUpload>());
    file_upload_->setMultiple(false);

    auto progress_bar = bindWidget("progress-bar", std::make_unique<Wt::WProgressBar>());
    file_upload_->setProgressBar(progress_bar);

    if (photo_url.empty())
    {
        std::cout << "\n photo_url is empty" << photo_url << " \n";
        photo_url = "static/util/user-icon.png";
    }
    else
        std::cout << "\n photo_url is not empty" << photo_url << " \n";
    image_ = bindWidget("image", std::make_unique<Wt::WImage>(Wt::WLink(photo_url), "user image"));
    image_->setStyleClass("bg-center bg-cover");

    file_upload_->setDisplayWidget(image_);
    file_upload_->changed().connect(this, &PhotoUpload::fileChanged);
    file_upload_->uploaded().connect(this, &PhotoUpload::fileUploaded);
    // file_upload_->dataReceived().connect(this, &PhotoUpload::fileRecived);
    file_upload_->fileTooLarge().connect(this, &PhotoUpload::fileToLarge);
}

void PhotoUpload::fileUploaded()
{
    bindString("file-info-1", "file uploaded");
    std::cout << "\n file uploaded \n";
    std::cout << "\n spoolFileName: " << file_upload_->spoolFileName() << "\n";
    std::cout << "\n clientFileName: " << file_upload_->clientFileName() << "\n";
    AwsConnect aws;
    auto result_url = aws.sendFile(file_upload_->spoolFileName(), "starterApp/" + std::to_string(session_.user().id()) + "/profile.jpg");
    image_->setImageLink(Wt::WLink(result_url));

    auto t = Dbo::Transaction(session_);
    session_.user().modify()->photo = result_url;
    t.commit();
    // std::cout << "\n " << file_upload_->spoolFileName() << "\n";
}

void PhotoUpload::fileChanged()
{
    bindString("file-info-2", "file changed");
    std::cout << "\n file changed \n";
    file_upload_->upload();
    std::cout << "\n " << file_upload_->spoolFileName() << "\n";
}

void PhotoUpload::fileToLarge()
{
    bindString("file-info-4", "file to large");
    std::cout << "\n file to large \n";
    // file_upload_->show();
}