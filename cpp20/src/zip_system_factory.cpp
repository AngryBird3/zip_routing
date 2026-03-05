#include "zip_system_factory.h"

namespace zipline {

std::vector<ZipSystem> zip_system_factory::Create(
      int numZips,
      std::size_t capacity,
      int maxRange,
      unsigned seed
  ) {
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> priority_dist(0, 1);

  std::vector<ZipSystem> systems;
  systems.reserve(numZips);

  for (int i = 0; i < numZips; ++i) {
    ZipSystem::Priority priority =
        priority_dist(rng) == 1
            ? ZipSystem::Priority::EMERGENCY
            : ZipSystem::Priority::OTHER;

    systems.emplace_back(
        i,
        capacity,
        maxRange,
        priority
    );
  }

  return systems;
}
}