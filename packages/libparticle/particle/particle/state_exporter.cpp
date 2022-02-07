#include "particle/state_exporter.hpp"

using namespace particle;

template<class P>
void
RetentionPolicy<P>::operator()()
{
  //
}

namespace particle {
template class RetentionPolicy<RetentionPolicy_Discard>;
template class RetentionPolicy<RetentionPolicy_Overwrite>;
template class RetentionPolicy<RetentionPolicy_Rotate>;
};
