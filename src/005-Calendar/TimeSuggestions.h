#pragma once
#include <Wt/WSuggestionPopup.h>


class TimeSuggestions : public Wt::WSuggestionPopup
{
 public:
  TimeSuggestions();

 private:
  void addSuggestion(const Wt::WString& suggestion);
};
