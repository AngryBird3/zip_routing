#include "zip_system.h"

#include <random>

namespace zipline {
class ZipSystemFactory {
public:
  static std::unordered_map<ZipSystemId, ZipSystem> Create(int kNumZips, int capacity, int maxRange, Location location, unsigned seed = 42);
};
}