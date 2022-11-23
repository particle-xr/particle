#include <iosfwd>
#include <string>

namespace particle {
namespace detail {
class version
{
public:
  using type = version;

  version();

  const int major;
  const int minor;
  const int patch;

  const std::string full_version_string() const;

  friend std::ostream& operator<<(std::ostream&, const type&);

private:
  const std::string full_;
};
}

const detail::version&
version();

}
