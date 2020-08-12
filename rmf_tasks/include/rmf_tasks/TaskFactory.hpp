/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#ifndef INCLUDE__RMF_TASKS__TASKFACTORY_HPP
#define INCLUDE__RMF_TASKS__TASKFACTORY_HPP

#include <memory>

#include <rmf_task_msgs/msg/loop.hpp>
#include <rmf_task_msgs/msg/station.hpp>
#include <rmf_task_msgs/msg/delivery.hpp>

#include "tasks/Loop.hpp"
#include "tasks/Station.hpp"
#include "tasks/Delivery.hpp"

namespace rmf_tasks {

//==============================================================================
/// Implement this class to interpret and manage incoming tasks from RMF
class TaskFactory
{
public:

  using LoopMsg = rmf_task_msgs::msg::Loop;
  using StationMsg = rmf_task_msgs::msg::Station;
  using DeliveryMsg = rmf_task_msgs::msg::Delivery;

  /// Creates a new instance of a loop task from an incoming message. 
  virtual std::shared_ptr<Loop> make_loop_task(const LoopMsg& msg) = 0;

  virtual std::shared_ptr<Station> make_station_task(const StationMsg& msg) = 0;

  virtual std::shared_ptr<Delivery> make_delivery_task(const DeliveryMsg& msg)
      = 0;

};

} // namespace rmf_tasks

#endif // INCLUDE__RMF_TASKS__TASKFACTORY_HPP
