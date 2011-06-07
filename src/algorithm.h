
#ifndef ALGORITHM_H_INCLUDED_
#define ALGORITHM_H_INCLUDED_

#include <map>

namespace algorithm
{

template<typename T, typename R>
std::map<R, typename T::value_type>
index_by(const T& t, R T::value_type::*ptr_to_mem)
{
    std::map<R, typename T::value_type> idx;
    for ( typename T::const_iterator i = t.begin(), end = t.end();
          i != end;
          ++i ) {
        idx[((*i).*ptr_to_mem)] = *i;
    }
    return  idx;
}

} // namespace algorithm

#endif // ALGORITHM_H_INCLUDED_
