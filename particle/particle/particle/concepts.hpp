#include <type_traits>

namespace particle::detail {

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

}
