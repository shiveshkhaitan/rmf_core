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

class Task::Implementation
{
public:

  Implementation(const std::string& task_name)
  : _task_name(task_name)
  {
    _submissions.clear();
  }

  std::unordered_map<std::string, Submission> _submissions;

  std::string _task_name;
};

//==============================================================================

Task::Task(const std::string& task_name)
: _pimpl(rmf_utils::make_impl<Implementation>(Implementation(task_name)))
{}

//==============================================================================

std::string Task::name() const
{
  return _pimpl->_task_name;
}

//==============================================================================

void Task::add_submission(const Submission& submission)
{
  _pimpl->_submissions[submission.robot_name] = submission;
}

//==============================================================================

std::vector<Task::Submission> Task::submissions() const
{
  std::vector<Submission> vect;
  for (auto it : _pimpl->_submissions)
  {
    vect.push_back(it.second);
  }
  return vect;
}

//==============================================================================

rmf_utils::optional<TaskScore> Task::score(const std::string& robot_name) const
{
  auto it = _pimpl->_submissions.find(robot_name);
  if (it == _pimpl->_submissions.end())
    return rmf_utils::nullopt;
  return it->second.score;
}

//==============================================================================

rmf_utils::optional<rmf_traffic::Trajectory> Task::trajectory(
      const std::string& robot_name) const
{
  auto it = _pimpl->_submissions.find(robot_name);
  if (it == _pimpl->_submissions.end())
    return rmf_utils::nullopt;
  return it->second.trajectory;
}

//==============================================================================

rmf_utils::optional<Task::Submission> Task::best_submission() const
{
  if (_pimpl->_submissions.empty())
    return rmf_utils::nullopt;

  std::string current_best_robot;
  TaskScore current_best_score = 0;
  for (const auto& it : _pimpl->_submissions)
  {
    if (it.second.score > current_best_score)
    {
      current_best_robot = it.first;
      current_best_score = it.second.score;
    }
  }
  
  auto best_it = _pimpl->_submissions.find(current_best_robot);
  assert(best_it != _pimpl->_submissions.end());
  return best_it->second;
}

//==============================================================================

} // namespace rmf_tasks
