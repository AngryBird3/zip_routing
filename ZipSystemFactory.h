#pragma once
#include "zip_system.h"
#include <vector>
#include <random>

namespace zipline {
class ZipSystemFactory {
public:
  static std::vector<zip_system>
  Create(
      int kNumZips,
      std::size_t capacity,
      const std::vector<Location>& locations,
      unsigned seed = 42
  ) {
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> priority_dist(0, 1);

    std::vector<zip_system> systems;
    systems.reserve(kNumZips);

    for (int i = 0; i < kNumZips; ++i) {
      Priority p =
          priority_dist(rng) == 1
              ? Priority::EMERGENCY
              : Priority::OTHER;

      systems.emplace_back(
          i,
          capacity,
          locations[i % locations.size()],
          p
      );
    }

    return systems;
  }
};
}