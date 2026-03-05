#include "zip_system.h"

#include <random>
#include <vector>

namespace zipline {
class ZipSystemFactory {
public:
  static std::vector<ZipSystem> Create(int kNumZips, std::size_t capacity, ,
    unsigned seed = 42);
};
}