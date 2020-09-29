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

#ifndef INCLUDE__RMF_TASKS__TASK_HPP
#define INCLUDE__RMF_TASKS__TASK_HPP

#include <memory>
#include <vector>

#include <rmf_utils/impl_ptr.hpp>
#include <rmf_traffic/Time.hpp>

namespace rmf_tasks {

class Task
{
public:

  class ActivePhase
  {
  public:

    /// Estimate how much time remains in this phase.
    virtual rmf_traffic::Duration estimate_remaining_time() const = 0;

    /// Activate or deacivate the emergency alarm behavior.
    virtual void emergency_alarm(bool on) = 0;

    /// This this phase to cancel.
    virtual void cancel() = 0;

    /// Human-readable description of the phase.
    virtual const std::string& description() const = 0;

    /// Virtual destructor
    virtual ~ActivePhase() = default;
  };

  class PendingPhase
  {
  public:

    /// Begin this phase.
    virtual std::shared_ptr<ActivePhase> begin() = 0;

    /// Estimate how much time this phase will require.
    virtual rmf_traffic::Duration estimate_phase_duration() const = 0;

    /// Human-readable description of the phase
    virtual const std::string& description() const = 0;

    /// Virtual destructor
    virtual ~PendingPhase() = default;
  };

  using PendingPhases = std::vector<std::unique_ptr<PendingPhase>>;

  static std::shared_ptr<Task> make(std::string id, PendingPhases phases);

  /// Begins this task.
  void begin();

  /// Get the current phase of the task.
  const std::shared_ptr<ActivePhase>& current_phase();

  /// const-qualified current_phase
  std::shared_ptr<const ActivePhase> current_phase() const;

  /// Get the phases of the task that are pending.
  const PendingPhases& pending_phases() const;

  /// Cancel this task.
  void cancel();

  const std::string& id() const;

  class Implementation;
private:
  Task(std::string id, PendingPhases phases);
  rmf_utils::impl_ptr<Implementation> _pimpl;
};

} // namespace rmf_tasks

#endif // INCLUDE__RMF_TASKS__TASK_HPP
