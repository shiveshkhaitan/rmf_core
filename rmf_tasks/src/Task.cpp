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

#include <rmf_tasks/Task.hpp>

namespace rmf_tasks {

//==============================================================================

class Task::Implementation
{
public:

  class SubmissionComparator
  {
  public:
    bool operator()(const Submission& first, const Submission& second)
    {
      if (first.score >= second.score)
        return true;
      return false;
    }
  };

  Implementation(const std::string& task_name)
  : _task_name(task_name)
  {}

  std::priority_queue<
    Task::Submission,
    std::vector<Task::Submission>,
    SubmissionComparator> _pq;

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
{}

//==============================================================================

std::vector<Task::Submission> Task::submissions() const
{
  std::vector<Submission> results;
  // TODO
  return results;
}

//==============================================================================

rmf_utils::optional<TaskScore> Task::score(const std::string& robot_name) const
{
  // TODO
  return rmf_utils::nullopt;
}

//==============================================================================

rmf_utils::optional<rmf_traffic::Trajectory> Task::trajectory(
      const std::string& robot_name) const
{
  // TODO
  return rmf_utils::nullopt;
}

//==============================================================================

rmf_utils::optional<Task::Submission> Task::best_submission() const
{
  // TODO
  return rmf_utils::nullopt;
}

//==============================================================================

} // namespace rmf_tasks
