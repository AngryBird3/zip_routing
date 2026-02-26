#pragma once
#include "zip_system.h"
#include "utils.h"

class cost_model
{
public:
  virtual Cost TravelCost(const ZipSystem& zip, const Location& from, const Location& to);
};