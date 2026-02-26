#include "zip_system_factory.h"

namespace zipline {

std::vector<ZipSystem> zip_system_factory::Create(
      int kNumZips,
      std::size_t capacity,
      const std::vector<Location>& locations,
      unsigned seed
  ) {
  std::mt19937 rng(seed);
  std::uniform_int_distribution<int> priority_dist(0, 1);

  std::vector<ZipSystem> systems;
  systems.reserve(kNumZips);

  for (int i = 0; i < kNumZips; ++i) {
    ZipSystem::Priority priority =
        priority_dist(rng) == 1
            ? ZipSystem::Priority::EMERGENCY
            : ZipSystem::Priority::OTHER;

    systems.emplace_back(
        i,
        capacity,
        locations[i % locations.size()],
        priority
    );
  }

  return systems;
}
}