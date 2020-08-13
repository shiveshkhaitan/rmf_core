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
#include <rmf_task_msgs/msg/clean.hpp>
#include <rmf_task_msgs/msg/station.hpp>
#include <rmf_task_msgs/msg/delivery.hpp>

#include "Task.hpp"

namespace rmf_tasks {

//==============================================================================
/// Implement this class to interpret and manage incoming tasks from RMF
class TaskFactory
{
public:

  using LoopMsg = rmf_task_msgs::msg::Loop;
  using CleanMsg = rmf_task_msgs::msg::Clean;
  using StationMsg = rmf_task_msgs::msg::Station;
  using DeliveryMsg = rmf_task_msgs::msg::Delivery;

  /// Creates a new instance of a loop task from an incoming message. The
  /// implementation should return a shared pointer to a Loop Task class that is
  /// derived from the pure abstract class Task. If this fleet does not support
  /// loop tasks, implement this function as a null op.
  ///
  /// \param[in] msg
  ///   Incoming loop task message.
  ///
  /// \return
  ///   Shared pointer to a derived Task that is implemented based on the
  ///   capabilities of the fleet and it's robots
  virtual std::shared_ptr<Task> make_loop_task(const LoopMsg& msg) = 0;

  /// Creates a new instance of a clean task from an incoming message. The
  /// implementation should return a shared pointer to a Clean Task class that 
  /// is derived from the pure abstract class Task. If this fleet does not
  /// support clean tasks, implement this function as a null op.
  ///
  /// \param[in] msg
  ///   Incoming clean task message.
  ///
  /// \return
  ///   Shared pointer to a derived Task that is implemented based on the
  ///   capabilities of the fleet and it's robots
  virtual std::shared_ptr<Task> make_clean_task(const CleanMsg& msg) = 0;

  /// Creates a new instance of a station task from an incoming message. The
  /// implementation should return a shared pointer to a Station Task class that 
  /// is derived from the pure abstract class Task. If this fleet does not
  /// support station tasks, implement this function as a null op.
  ///
  /// \param[in] msg
  ///   Incoming station task message.
  ///
  /// \return
  ///   Shared pointer to a derived Task that is implemented based on the
  ///   capabilities of the fleet and it's robots
  virtual std::shared_ptr<Task> make_station_task(const StationMsg& msg) = 0;

  /// Creates a new instance of a delivery task from an incoming message. The
  /// implementation should return a shared pointer to a Delivery Task class
  /// that is derived from the pure abstract class Task. If this fleet does not
  /// support delivery tasks, implement this function as a null op.
  ///
  /// \param[in] msg
  ///   Incoming delivery task message.
  ///
  /// \return
  ///   Shared pointer to a derived Task that is implemented based on the
  ///   capabilities of the fleet and it's robots
  virtual std::shared_ptr<Task> make_delivery_task(const DeliveryMsg& msg) = 0;
};

} // namespace rmf_tasks

#endif // INCLUDE__RMF_TASKS__TASKFACTORY_HPP
