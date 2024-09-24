#pragma once
#include <Wt/WFormModel.h>

class Session;

class UserDetailsModel : public Wt::WFormModel
{
public:
    static const Field first_name;
    static const Field last_name;
    static const Field phone;

    UserDetailsModel(Session &session);

    void save(const Wt::Auth::User &user);
    void saveFirstName(const Wt::Auth::User &user, const std::string &first_name);
    void saveLastName(const Wt::Auth::User &user, const std::string &last_name);
    void savePhone(const Wt::Auth::User &user, const std::string &phone);

private:
    Session &session_;
};