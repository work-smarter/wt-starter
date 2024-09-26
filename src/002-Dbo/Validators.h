#pragma once

#include <Wt/WRegExpValidator.h>

std::shared_ptr<Wt::WRegExpValidator> createNameValidator()
{
    auto validator = std::make_shared<Wt::WRegExpValidator>("^[a-zA-Z]{3,50}$");
    // validator->setMandatory(true);
    validator->setInvalidNoMatchText("Must contain between 3 and 50 characters and no spaces");
    validator->setInvalidBlankText("Cannot be empty");
    return validator;
}

std::shared_ptr<Wt::WRegExpValidator> createPhoneValidator()
{
    auto validator = std::make_shared<Wt::WRegExpValidator>("^\\d{10}$");
    // validator->setMandatory(true);
    validator->setInvalidNoMatchText("10 digits, only numbers");
    validator->setInvalidBlankText("Cannot be empty");
    return validator;
}