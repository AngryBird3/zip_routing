#include "zip_system.h"

#include <random>

namespace zipline {
class ZipSystemFactory {
public:
  static std::unordered_map<ZipSystemId, ZipSystem> Create(int numZips, int capacity, int maxRange, Location position, int speed, unsigned seed = 42);
};
}