#ifndef MGStringTools_h
#define MGStringTools_h

#include <string>
#include <vector>



class MGStringTools
{
  public:
    MGStringTools() {};
    virtual ~MGStringTools() {};
    
    std::vector<std::string> TokenizeString(const std::string& str, const std::string& delimiters);
  private:
    // Nothing at the moment
};

#endif
