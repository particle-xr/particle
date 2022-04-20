#include "particle/state_exporter.hpp"

#include <stdexcept>

using namespace particle::state;

template<class P>
void
RetentionPolicy<P>::operator()()
{
  throw std::runtime_error("not implemented");
}

namespace particle::state {
template class RetentionPolicy<Discard>;
template class RetentionPolicy<Overwrite>;
template class RetentionPolicy<Rotate>;
};
