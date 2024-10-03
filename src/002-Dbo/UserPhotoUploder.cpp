#include "002-Dbo/UserPhotoUploder.h"
#include "100-Utils/AwsConnect.h"

UserPhotoUploder::UserPhotoUploder(Session &session)
    : Wt::WTemplate(Wt::WString::tr("starter.photo.upload")),
      session_(session)
{
    auto photo_url = session_.user()->photo_url.toUTF8();
    // addFunction("id", &WTemplate::Functions::id);
    bindEmpty("file-info-1");
    bindEmpty("file-info-2");
    bindEmpty("file-info-3");

    photo_uploader = bindWidget("file-upload", std::make_unique<Wt::WFileUpload>());
    photo_uploader->setMultiple(false);

    photo_uploader->setProgressBar(bindWidget("progress-bar", std::make_unique<Wt::WProgressBar>()));
    photo_uploader->progressBar()->hide();

    upload_btn = bindWidget("upload-btn", std::make_unique<Wt::WPushButton>(Wt::WString::tr("starter.svg.edit"), Wt::TextFormat::XHTML));

    if (photo_url.empty())
    {
        std::cout << "\n photo_url is empty" << photo_url << " \n";
        photo_url = "static/util/user-icon.png";
    }
    else
        std::cout << "\n photo_url is not empty" << photo_url << " \n";
    image_ = bindWidget("image", std::make_unique<Wt::WImage>(Wt::WLink(photo_url), "user image"));
    image_->setStyleClass("");

    // photo_uploader->setDisplayWidget(image_);
    photo_uploader->setDisplayWidget(upload_btn);
    photo_uploader->changed().connect(this, &UserPhotoUploder::fileChanged);
    photo_uploader->uploaded().connect(this, &UserPhotoUploder::fileUploaded);
    photo_uploader->fileTooLarge().connect(this, &UserPhotoUploder::fileToLarge);
}

void UserPhotoUploder::fileUploaded()
{
    // bindString("file-info-1", "file uploaded");
    std::cout << "\n file uploaded \n";
    std::cout << "\n spoolFileName: " << photo_uploader->spoolFileName() << "\n";
    std::cout << "\n clientFileName: " << photo_uploader->clientFileName() << "\n";
    std::string random_image_name = photo_uploader->spoolFileName().substr(photo_uploader->spoolFileName().find_last_of("/") + 1);
    std::string file_termination = photo_uploader->clientFileName().toUTF8().substr(photo_uploader->clientFileName().toUTF8().find_last_of("."));
    AwsConnect aws;
    auto result_url = aws.sendFile(photo_uploader->spoolFileName(), "starterApp/user-" + std::to_string(session_.user().id()) + "/" + random_image_name + file_termination);

    // set the photo_url to the user and delete the previous photo from aws
    auto t = Dbo::Transaction(session_);
    if (session_.user()->photo_url.toUTF8().compare(""))
    {
        auto photo_key = session_.user()->photo_url.toUTF8().substr(session_.user()->photo_url.toUTF8().find("starterApp"));
        aws.deleteFile(photo_key);
    }
    session_.user().modify()->photo_url = result_url;
    t.commit();

    photo_uploader->progressBar()->hide();
    image_->setImageLink(Wt::WLink(result_url));
    image_->refresh();
    // std::cout << "\n " << photo_uploader->spoolFileName() << "\n";
}

void UserPhotoUploder::fileChanged()
{
    // bindString("file-info-2", "file changed");
    std::cout << "\n file changed \n";
    photo_uploader->progressBar()->show();
    photo_uploader->upload();

    std::cout << "\n " << photo_uploader->spoolFileName() << "\n";
}

void UserPhotoUploder::fileToLarge()
{
    // bindString("file-info-3", "file to large");
    std::cout << "\n file to large \n";
    // photo_uploader->show();
}