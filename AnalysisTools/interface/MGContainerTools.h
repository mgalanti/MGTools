#ifndef MGContainerTools_h
#define MGContainerTools_h

#include <cstdarg>



class MGContainerTools
{
  public:
    template <class T>
    const std::vector<T> Join(const std::vector<T> v1, const std::vector<T> v2);
    
    template <class T>
    const std::vector<T> JoinMany(const std::vector<std::vector<T> > vv);
    
  private:
  
};

#include "MGTools/AnalysisTools/interface/MGContainerTools.hpp"

#endif // MGContainerTools_h
