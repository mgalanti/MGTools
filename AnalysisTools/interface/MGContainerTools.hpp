#include "cstdarg"

template <class T>
const std::vector<T> MGContainerTools::Join(const std::vector<T> v1, const std::vector<T> v2)
{
  // Algorithm from StackOverflow (https://stackoverflow.com/questions/3177241)
  std::vector<T> vRes;
  vRes.reserve(v1.size() + v2.size()); // preallocate memory
  vRes.insert(vRes.end(), v1.begin(), v1.end());
  vRes.insert(vRes.end(), v2.begin(), v2.end());
  return vRes;
}



template <class T>
const std::vector<T> MGContainerTools::JoinMany(const std::vector<std::vector<T> > vv)
{
  if(vv.size() < 2)
  {
    std::cout << "MGContainerTools::JoinMany(): E R R O R ! You should pass at least two elements to this function!\n";
    exit(1);
  }
  std::vector<T> vRes = vv[0];
  for(auto itvv = vv.begin()+1; itvv != vv.end(); itvv++)
  {
    vRes = Join(vRes, *itvv);
  }
  return vRes;
}
