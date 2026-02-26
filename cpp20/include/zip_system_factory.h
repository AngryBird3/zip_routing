#include "zip_system.h"

#include <random>
#include <vector>

namespace zipline {
class zip_system_factory {
  static std::vector<ZipSystem> Create(int kNumZips, std::size_t capacity, const std::vector<Location>& locations, unsigned seed = 42);
};
}