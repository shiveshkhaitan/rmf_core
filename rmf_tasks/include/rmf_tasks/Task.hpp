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
#include <memory>
#include <functional>

#include <Eigen/Geometry>

#include <rmf_traffic/Time.hpp>
#include <rmf_traffic/Trajectory.hpp>

namespace rmf_tasks {

//==============================================================================
/// Inherit from this class for each of the different tasks that the robot fleet
/// can perform, using fleet-specific methods, and overriding these base methods
/// if necessary.
class Task
{
public:

  /// Score of this particular task being performed by a particular robot.
  using Score = unsigned int;

  /// Prediction made for any particular robot to complete this task.
  /// Prediction objects should only be created using helper functions
  /// implemented for each type of tasks.
  class Prediction
  {
  public:

    /// Creates an empty Prediction.
    Prediction();

    /// Get the name or ID of the task that this Prediction applies to.
    const std::string& get_task_name() const;

    /// Set the name of the task to this Prediction.
    Prediction& set_task_name(const std::string& name);

    /// Get the name of the robot that this Prediction is executed on.
    const std::string& get_robot_name() const;

    /// Set the name of the robot for this Prediction.
    Prediction& set_robot_name(const std::string& name);

    /// Get the score of this Prediction.
    Score get_score() const;

    /// Sets the score for this Prediction.
    Prediction& set_score(Score score);

    /// Get the trajectory generated to perform this Prediction.
    const rmf_traffic::Trajectory& get_trajectory() const;

    /// Sets the trajectory for this Prediction.
    Prediction& set_trajectory(const rmf_traffic::Trajectory& trajectory);

    /// Get the final position of the robot when this task is completed.
    const Eigen::Vector3d& get_final_position() const;

    /// Get the duration required for this robot to complete this task using
    /// this prediction.
    rmf_traffic::Duration duration() const;

    class Implementation;
  private:
    rmf_utils::impl_ptr<Implementation> _pimpl;
  };

  /// Get the name of this task.
  const std::string& get_name() const;

  /// Implement this function to generate predictions to complete this task for
  /// using a particular.
  ///
  /// \param[in] robot_name
  ///   Name of the assigned robot.
  ///
  /// \param[in] position
  ///   Current position of the robot.
  ///
  /// \param[in] map_name
  ///   Current map name of the robot.
  ///
  /// \return
  ///   Shared pointer to the generated Prediction for this Task. If no
  ///   prediction could be generated, this will return a nullptr.
  virtual std::shared_ptr<Prediction> predict(
      const std::string& robot_name,
      Eigen::Vector3d position,
      const std::string& map_name) = 0;

  /// Helper function that retrieves the best prediction from the provided
  /// vector of predictions. This will be determined based on the best score out
  /// of all the predictions.
  ///
  /// \param[in] predictions
  ///   Vector of previously generated predictions, for this particular task.
  ///
  /// \return
  ///   Prediction with the best score. If no predictions were provided, a
  ///   nullptr will be returned.
  virtual std::shared_ptr<Prediction> best_prediction(
      const std::vector<std::shared_ptr<Prediction>>& predictions) const;

  /// Default destructor.
  ~Task() = default;

  class Implementation;

private:

  rmf_utils::impl_ptr<Implementation> _pimpl;

protected:

  /// Protected constructor that should be called only by the constructor
  /// initialization of a derived Task class.
  ///
  /// \param[in] task_name
  ///   The name given to this particular task.
  Task(const std::string& task_name);
};

} // namespace rmf_tasks

#endif // INCLUDE__RMF_TASKS__TASKS__TASK_HPP
