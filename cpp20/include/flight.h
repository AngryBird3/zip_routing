// Copyright 2021 Zipline International Inc. All rights reserved.

#pragma once

#include <vector>

#include "order.h"
#include "util.h"

namespace zipline
{

/**
 * Represents a flight: launch time, orders, and ETA. Flight owns ETA.
 */
class Flight
{
   public:
    Flight(Timestamp launch_time, const std::vector<Order> &orders) : launch_time_(launch_time), orders_(orders)
    {
    }

    Timestamp launchTime() const { return launch_time_; }

    const std::vector<Order> &Orders() const { return orders_; }

    void setEta(Timestamp eta) { eta_ = eta; }
    Timestamp eta() const { return eta_; }

   private:
    Timestamp launch_time_{};
    std::vector<Order> orders_{};
    Timestamp eta_{};
};
}  // namespace zipline
