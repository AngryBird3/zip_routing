#include "zip_system_factory.h"

namespace zipline {

std::unordered_map<ZipSystemId, ZipSystem> ZipSystemFactory::Create(
      int numZips,
      int capacity,
      int maxRange,
      Location position,
      int speed,
      unsigned seed
  ) {
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> priority_dist(0, 1);

  std::unordered_map<ZipSystemId, ZipSystem> systems;
  systems.reserve(numZips);

  for (int i = 0; i < numZips; ++i) {
    ZipSystem::Priority priority =
        priority_dist(rng) == 1
            ? ZipSystem::Priority::EMERGENCY
            : ZipSystem::Priority::OTHER;
    systems.emplace(i, ZipSystem(
        i,
        capacity,
        maxRange,
        position,
        speed,
        priority
    ));
  }

  return systems;
}
}