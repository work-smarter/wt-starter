#include "002-Dbo/UserPhotoUploder.h"
#include "100-Utils/AwsConnect.h"

UserPhotoUploder::UserPhotoUploder(Session &session)
    : Wt::WTemplate(Wt::WString::tr("starter.photo.upload")),
      session_(session)
{
    auto photo_url = session_.user()->photo.toUTF8();
    // addFunction("id", &WTemplate::Functions::id);
    bindEmpty("file-info-1");
    bindEmpty("file-info-2");
    bindEmpty("file-info-3");
    bindEmpty("file-info-4");

    photo_uploader = bindWidget("file-upload", std::make_unique<Wt::WFileUpload>());
    photo_uploader->setMultiple(false);

    auto progress_bar = bindWidget("progress-bar", std::make_unique<Wt::WProgressBar>());
    photo_uploader->setProgressBar(progress_bar);

    if (photo_url.empty())
    {
        std::cout << "\n photo_url is empty" << photo_url << " \n";
        photo_url = "static/util/user-icon.png";
    }
    else
        std::cout << "\n photo_url is not empty" << photo_url << " \n";
    image_ = bindWidget("image", std::make_unique<Wt::WImage>(Wt::WLink(photo_url), "user image"));
    image_->setStyleClass("");

    photo_uploader->setDisplayWidget(image_);
    photo_uploader->changed().connect(this, &UserPhotoUploder::fileChanged);
    photo_uploader->uploaded().connect(this, &UserPhotoUploder::fileUploaded);
    photo_uploader->fileTooLarge().connect(this, &UserPhotoUploder::fileToLarge);
}

void UserPhotoUploder::fileUploaded()
{
    bindString("file-info-1", "file uploaded");
    std::cout << "\n file uploaded \n";
    std::cout << "\n spoolFileName: " << photo_uploader->spoolFileName() << "\n";
    std::cout << "\n clientFileName: " << photo_uploader->clientFileName() << "\n";
    AwsConnect aws;
    auto result_url = aws.sendFile(photo_uploader->spoolFileName(), "starterApp/" + std::to_string(session_.user().id()) + "/profile.jpg");
    image_->setImageLink(Wt::WLink(result_url));

    auto t = Dbo::Transaction(session_);
    session_.user().modify()->photo = result_url;
    t.commit();
    // std::cout << "\n " << photo_uploader->spoolFileName() << "\n";
}

void UserPhotoUploder::fileChanged()
{
    bindString("file-info-2", "file changed");
    std::cout << "\n file changed \n";
    photo_uploader->upload();
    std::cout << "\n " << photo_uploader->spoolFileName() << "\n";
}

void UserPhotoUploder::fileToLarge()
{
    bindString("file-info-4", "file to large");
    std::cout << "\n file to large \n";
    // photo_uploader->show();
}