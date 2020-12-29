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

#include <src/rmf_traffic/agv/planning/DifferentialDriveHeuristic.hpp>

#include "../../utils_Trajectory.hpp"

#include <rmf_utils/catch.hpp>


#include <iostream>



//==============================================================================
//SCENARIO("Differential Drive Heuristic -- Peak and Valley")
//{
//  rmf_traffic::agv::Graph graph;
//  const std::string test_map = "test_map";

//  // This event does not actually take up any time, but it will force a pause
//  // at every lane that contains it. As a result, the shorter path will
//  // (intentionally) be forced to waste time accelerating and decelerating. That
//  // slowdown will allow a longer path to require less time to reach the goal.
//  const auto bogus_event = rmf_traffic::agv::Graph::Lane::Event::make(
//        rmf_traffic::agv::Graph::Lane::Wait(std::chrono::seconds(1)));

//  const std::size_t N = 30;
//  const std::size_t start_index = 0;
//  const std::size_t goal_index = N;

//  for (std::size_t i=0; i <= N; ++i)
//  {
//    graph.add_waypoint(test_map, {i, 0});
//    if (i > 0)
//    {
//      graph.add_lane(i, {i-1, bogus_event});
//      graph.add_lane({i-1, bogus_event}, i);
//    }
//  }

//  const double peak = 3.0;
//  for (std::size_t i=1; i < N; ++i)
//  {
//    double offset;
//    if (i < N/2)
//      offset = 2.0*static_cast<double>(i)/static_cast<double>(N) * peak;
//    else
//      offset = 2.0*static_cast<double>(N-i)/static_cast<double>(N) * peak;

//    graph.add_waypoint(test_map, {i, offset});
//    if (i > 1)
//    {
//      graph.add_lane(i+N, i+N-1);
//      graph.add_lane(i+N-1, i+N);
//    }
//  }

//  const double incline = std::atan2(peak, N/2)*180.0/M_PI;
//  std::cout << "Incline Angle: " << incline << std::endl;
//  std::cout << "a - 180: " << incline - 180.0 << std::endl;

//  REQUIRE(graph.num_waypoints() == 2*N);

//  // Connect the peak path to the start
//  graph.add_lane(start_index, N+1);
//  graph.add_lane(N+1, start_index);

//  // Connect the peak path to the goal
//  graph.add_lane(goal_index, 2*N-1);
//  graph.add_lane(2*N-1, goal_index);

//  const double v_nom = 2.0;
//  const double a_nom = 0.3;
//  rmf_traffic::agv::VehicleTraits traits(
//    {v_nom, a_nom}, {1.0, 0.45}, create_test_profile(UnitCircle));
//  traits.get_differential()->set_reversible(true);

//  const auto supergraph = rmf_traffic::agv::planning::Supergraph::make(
//        rmf_traffic::agv::Graph::Implementation::get(graph),
//        traits, rmf_traffic::agv::Interpolate::Options());

//  // TODO(MXG): Make a cleaner way to instantiate these caches
//  using DifferentialDriveCache =
//    rmf_traffic::agv::planning::CacheManager<
//      rmf_traffic::agv::planning::Cache<
//        rmf_traffic::agv::planning::DifferentialDriveHeuristic>>;
//  auto diff_drive_cache = DifferentialDriveCache::make(
//    std::make_shared<
//      rmf_traffic::agv::planning::DifferentialDriveHeuristic>(
//          supergraph), [N = supergraph->original().lanes.size()]()
//  {
//    return rmf_traffic::agv::planning::DifferentialDriveHeuristic::Storage(
//      4093, rmf_traffic::agv::planning::DifferentialDriveMapTypes::KeyHash{N});
//  });

//  const auto keys = supergraph->keys_for(0, goal_index, std::nullopt);
//  std::cout << "Number of keys: " << keys.size() << std::endl;
//  for (const auto& key : keys)
//  {
//    std::cout << " ==================== " << std::endl;
//    auto solution = diff_drive_cache->get().get(key);
//    std::cout << " --------------------\n"
//              << "Solution for [" << key.start_lane << ", "
//              << key.start_orientation << ", "
//              << key.goal_lane << ", "
//              << key.goal_orientation << "]:";

//    double cost = 0.0;
//    while (solution)
//    {
//      cost += solution->info.cost_from_parent;
//      std::cout << " (" << cost << "; "
//                << solution->info.waypoint << ", "
//                << 180.0*solution->info.yaw/M_PI
//                << ") -->";
//      solution = solution->child;
//    }
//    std::cout << " (finished)" << std::endl;

//    const auto& lane = supergraph->original().lanes[key.goal_lane];
//    std::cout << "Lane " << key.goal_lane << ": " << lane.entry().waypoint_index()
//              << " -> " << lane.exit().waypoint_index() << std::endl;
//  }

//  const std::size_t second_goal_index = 45;
//  const auto second_keys = supergraph->keys_for(0, second_goal_index, std::nullopt);
//  std::cout << "Number of keys: " << second_keys.size() << std::endl;
//  for (const auto& key : second_keys)
//  {
//    std::cout << " ==================== " << std::endl;
//    auto solution = diff_drive_cache->get().get(key);
//    std::cout << " --------------------\n"
//              << "Solution for [" << key.start_lane << ", "
//              << key.start_orientation << ", "
//              << key.goal_lane << ", "
//              << key.goal_orientation << "]:";

//    double cost = 0.0;
//    while (solution)
//    {
//      cost += solution->info.cost_from_parent;
//      std::cout << " (" << cost << "; "
//                << solution->info.waypoint << ", "
//                << 180.0*solution->info.yaw/M_PI
//                << ") -->";
//      solution = solution->child;
//    }
//    std::cout << " (finished)" << std::endl;

//    const auto& lane = supergraph->original().lanes[key.goal_lane];
//    std::cout << "Lane " << key.goal_lane << ": " << lane.entry().waypoint_index()
//              << " -> " << lane.exit().waypoint_index() << std::endl;
//  }
//}

//==============================================================================
SCENARIO("Differential Drive Heuristic -- Any-Yaw Edge Case")
{
  rmf_traffic::agv::Graph graph;
  const std::string test_map_0 = "test_map_0";
  const std::string test_map_1 = "test_map_1";
  const std::string test_map_2 = "test_map_2";

  graph.add_waypoint(test_map_0, {0, 0}); // 0
  graph.add_waypoint(test_map_1, {0, 0}); // 1
  graph.add_waypoint(test_map_2, {0, 0}); // 2
  graph.add_waypoint(test_map_2, {0, 1}); // 3

  const auto bogus_event = rmf_traffic::agv::Graph::Lane::Event::make(
        rmf_traffic::agv::Graph::Lane::Wait(std::chrono::seconds(1)));

  graph.add_lane({0, bogus_event}, 1);
  graph.add_lane({1, bogus_event}, 2);
  graph.add_lane(2, 3);

  const std::size_t goal_index = 3;

  const double v_nom = 2.0;
  const double a_nom = 0.3;
  rmf_traffic::agv::VehicleTraits traits(
    {v_nom, a_nom}, {1.0, 0.45}, create_test_profile(UnitCircle));
  traits.get_differential()->set_reversible(true);

  const auto supergraph = rmf_traffic::agv::planning::Supergraph::make(
        rmf_traffic::agv::Graph::Implementation::get(graph),
        traits, rmf_traffic::agv::Interpolate::Options());

  // TODO(MXG): Make a cleaner way to instantiate these caches
  using DifferentialDriveCache =
    rmf_traffic::agv::planning::CacheManager<
      rmf_traffic::agv::planning::Cache<
        rmf_traffic::agv::planning::DifferentialDriveHeuristic>>;
  auto diff_drive_cache = DifferentialDriveCache::make(
    std::make_shared<
      rmf_traffic::agv::planning::DifferentialDriveHeuristic>(
          supergraph), [N = supergraph->original().lanes.size()]()
  {
    return rmf_traffic::agv::planning::DifferentialDriveHeuristic::Storage(
      4093, rmf_traffic::agv::planning::DifferentialDriveMapTypes::KeyHash{N});
  });

  const auto keys = supergraph->keys_for(0, goal_index, std::nullopt);
  std::cout << "Number of keys: " << keys.size() << std::endl;
  for (const auto& key : keys)
  {
    std::cout << " ==================== " << std::endl;
    auto solution = diff_drive_cache->get().get(key);
    std::cout << " --------------------\n"
              << "Solution for [" << key.start_lane << ", "
              << key.start_orientation << ", "
              << key.goal_lane << ", "
              << key.goal_orientation << "]:";

    if (!solution)
    {
      std::cout << " No solution found!" << std::endl;
    }

    double cost = 0.0;
    while (solution)
    {
      cost += solution->info.cost_from_parent;
      std::cout << " (" << cost << "; "
                << solution->info.waypoint << ", "
                << 180.0*solution->info.yaw.value_or(std::nan(""))/M_PI
                << ") -->";
      solution = solution->child;
    }
    std::cout << " (finished)" << std::endl;

    const auto& lane = supergraph->original().lanes[key.goal_lane];
    std::cout << "Lane " << key.goal_lane << ": " << lane.entry().waypoint_index()
              << " -> " << lane.exit().waypoint_index() << std::endl;
  }
}
