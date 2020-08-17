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

#include <iostream>

#include <rmf_tasks/Task.hpp>
#include <rmf_tasks/TaskFactory.hpp>

namespace rmf_tasks {

class Clean : public Task
{

public:

  Clean(const std::string& cleaning_zone)
  : Task("cleaning_task"),
    _cleaning_zone(cleaning_zone)
  {}

  std::shared_ptr<Prediction> predict(
      const std::string& robot_name,
      Eigen::Vector3d position,
      const std::string& map_name)
  {
    std::shared_ptr<Prediction> new_prediction(new Prediction());
    return new_prediction;
  }

private:

  std::string _cleaning_zone;

};

}

int main(int argc, char** argv)
{
  std::cout << "all done" << std::endl;
  return 0;
}
