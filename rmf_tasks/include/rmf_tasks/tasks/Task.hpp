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

#ifndef INCLUDE__RMF_TASKS__TASKS__TASK_HPP
#define INCLUDE__RMF_TASKS__TASKS__TASK_HPP

#include <rmf_utils/optional.hpp>
#include <rmf_traffic/Trajectory.hpp>

#include "../TaskFactoryPrediction.hpp"

namespace rmf_tasks {

class Task
{
public:

  virtual void set_score(TaskScore score) = 0;

  virtual rmf_utils::optional<TaskScore> score() = 0;

  virtual void set_trajectory(const rmf_traffic::Trajectory& trajectory) = 0;

  virtual rmf_utils::optional<rmf_traffic::Trajectory> trajectory() = 0;

};

} // namespace rmf_tasks

#endif // INCLUDE__RMF_TASKS__TASKS__TASK_HPP
