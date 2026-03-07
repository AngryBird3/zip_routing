// Copyright 2021 Zipline International Inc. All rights reserved.

#pragma once

#include "common_types.h"


#include <filesystem>
#include <string>
#include <unordered_map>

namespace zipline
{
class Hospital
{
   public:
    Hospital(const std::string &name, int north, int east) : name_(name), north_(north), east_(east) {}

    Hospital(const Hospital&) = default;
    Hospital& operator=(const Hospital&) = default;

    static std::unordered_map<std::string, Hospital> LoadHospitals(const std::filesystem::path &filename);

    std::string name() const
    {
        return name_;
    }

    int north() const
    {
        return north_;
    }

    int east() const
    {
        return east_;
    }

    Location GetLocation() const { return {north_, east_}; }

   private:
    std::string name_;
    int north_;
    int east_;
};

}  // namespace zipline
