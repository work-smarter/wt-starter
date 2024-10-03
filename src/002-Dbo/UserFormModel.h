#pragma once
#include <Wt/WFormModel.h>

class Session;

class UserFormModel : public Wt::WFormModel
{
public:
    static const Field USER_NAME;
    static const Field FIRST_NAME;
    static const Field LAST_NAME;
    static const Field PHONE;
    static const Field JOIN_DATE;
    // static const Field PHOTO;

    UserFormModel(Session &session);

    void save(const Wt::Auth::User &user);
    void saveUserName(const Wt::Auth::User &user, const std::string &user_name);
    void saveFirstName(const Wt::Auth::User &user, const std::string &first_name);
    void saveLastName(const Wt::Auth::User &user, const std::string &last_name);
    void savePhone(const Wt::Auth::User &user, const std::string &phone);
    void savePhoto(const Wt::Auth::User &user, const std::string &photo_path);

private:
    Session &session_;
};