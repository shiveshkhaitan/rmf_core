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

#include <queue>
#include <unordered_map>

#include <rmf_tasks/Task.hpp>

namespace rmf_tasks {

//==============================================================================

class Task::Prediction::Implementation
{
public:

  Implementation(
      const std::string& task_name,
      const std::string& robot_name,
      Score score,
      const rmf_traffic::Trajectory trajectory)
  : _task_name(task_name),
    _robot_name(robot_name),
    _score(score),
    _trajectory(trajectory)
  {}

  std::string _task_name;

  std::string _robot_name;

  Score _score;

  rmf_traffic::Trajectory _trajectory;
};

//==============================================================================

Task::Prediction::Prediction()
{}

//==============================================================================

const std::string& Task::Prediction::get_task_name() const
{
  return _pimpl->_task_name;
}

//==============================================================================

Task::Prediction& Task::Prediction::set_task_name(
    const std::string& name)
{
  _pimpl->_task_name = name;
}

//==============================================================================

const std::string& Task::Prediction::get_robot_name() const
{
  return _pimpl->_robot_name;
}

//==============================================================================

Task::Prediction& Task::Prediction::set_robot_name(
    const std::string& name)
{
  _pimpl->_robot_name = name;
}

//==============================================================================

Task::Score Task::Prediction::get_score() const
{
  return _pimpl->_score;
}

//==============================================================================

Task::Prediction& Task::Prediction::set_score(Task::Score score)
{
  _pimpl->_score = score;
}

//==============================================================================

const rmf_traffic::Trajectory& Task::Prediction::get_trajectory() const
{
  return _pimpl->_trajectory;
}

//==============================================================================

Task::Prediction& Task::Prediction::set_trajectory(
    const rmf_traffic::Trajectory& trajectory)
{
  _pimpl->_trajectory = trajectory;
}

//==============================================================================

const Eigen::Vector3d& Task::Prediction::get_final_position() const
{
  const auto& final_waypoint = _pimpl->_trajectory.back();
  return final_waypoint.position();
}

//==============================================================================

rmf_traffic::Duration Task::Prediction::duration() const
{
  return _pimpl->_trajectory.duration();
}

//==============================================================================

class Task::Implementation
{
public:

  Implementation(const std::string& task_name)
  : _task_name(task_name)
  {}

  std::string _task_name;
};

//==============================================================================

const std::string& Task::get_name() const
{
  return _pimpl->_task_name;
}

//==============================================================================

std::shared_ptr<Task::Prediction> Task::best_prediction(
    const std::vector<std::shared_ptr<Prediction>>& predictions) const
{
  if (predictions.empty())
    return nullptr;

  std::size_t best_prediction_index;
  Score best_score = 0;

  for (std::size_t i = 0; i < predictions.size(); ++i)
  {
    const Score current_index_score = predictions[i]->get_score();
    if (current_index_score > best_score)
    {
      best_prediction_index = i;
      best_score = current_index_score;
    }
  }
  
  return predictions[best_prediction_index];
}

//==============================================================================

Task::Task(const std::string& task_name)
: _pimpl(rmf_utils::make_impl<Implementation>(Implementation(task_name)))
{}

//==============================================================================

} // namespace rmf_tasks
