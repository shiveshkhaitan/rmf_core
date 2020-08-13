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

#include <string>
#include <vector>
#include <functional>

#include <rmf_utils/optional.hpp>
#include <rmf_traffic/Trajectory.hpp>

#include "TaskFactoryPrediction.hpp"

namespace rmf_tasks {

//==============================================================================
/// Inherit from this class for each of the different tasks that the robot fleet
/// can perform, using fleet-specific methods, and overriding these base methods
/// if necessary.
class Task
{
public:

  /// Submissions to be used in Task for keeping track of possible assignments
  struct Submission
  {
    /// Name or ID of the robot.
    std::string robot_name;

    /// Trajectory to be performed by this robot to complete the task
    rmf_traffic::Trajectory trajectory;

    /// Task score that is assigned to the robot.
    TaskScore score;
  };

  /// Returns the name given to this task during initialization.
  ///
  /// \return
  ///   Name of the task.
  virtual std::string name() const;

  /// Adds a Submission to this task.
  ///
  /// \param[in]
  ///   Submission for a particular robot to complete this task.
  virtual void add_submission(const Submission& submission);

  /// Retrieves all the submissions that have been added to this task so far.
  ///
  /// \return
  ///   Vector of submissions up till now.
  virtual std::vector<Submission> submissions() const;

  /// Retrieves the submitted task score of a particular robot, identified
  /// by its name or ID.
  ///
  /// \param[in] robot_name
  ///   Name or ID of the desired robot.
  ///
  /// \return
  ///   Task score of the desired robot. If a submission for this robot is not
  ///   available, a nullopt will be returned.
  virtual rmf_utils::optional<TaskScore> score(const std::string& robot_name)
    const;

  /// Retrieves the submitted trajectory of a particular robot, identified by
  /// its name or ID.
  ///
  /// \param[in] robot_name
  ///   Name or ID of the desired robot.
  ///
  /// \return
  ///   Trajectory of the desired robot. If a submission for this robot is not
  ///   available, a nullopt will be returned.
  virtual rmf_utils::optional<rmf_traffic::Trajectory> trajectory(
      const std::string& robot_name) const;

  /// Retrieves the best submission so far. This will be determined based
  /// on the best score out of all the submissions.
  ///
  /// \return
  ///   Submission with the best score. If no submissions are available yet, 
  ///   this will return a nullopt.
  virtual rmf_utils::optional<Submission> best_submission() const;

  /// Default destructor.
  ~Task() = default;

  class Implementation;
private:
  rmf_utils::impl_ptr<Implementation> _pimpl;

  /// Private constructor that should be called only by the constructor
  /// initialization of a derived Task class.
  ///
  /// \param[in] task_name
  ///   The name given to this particular task.
  Task(const std::string& task_name);
};

} // namespace rmf_tasks

#endif // INCLUDE__RMF_TASKS__TASKS__TASK_HPP
