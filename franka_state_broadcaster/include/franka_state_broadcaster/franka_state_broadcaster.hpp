#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "franka/robot_state.h"

#include "controller_interface/controller_interface.hpp"
#include "franka_semantic_components/franka_state.hpp"
#include "franka_state_broadcaster_parameters.hpp"
#include "rclcpp_lifecycle/lifecycle_publisher.hpp"
#include "rclcpp_lifecycle/node_interfaces/lifecycle_node_interface.hpp"
#include "realtime_tools/realtime_publisher.h"

namespace franka_state_broadcaster {
class FrankaStateBroadcaster : public controller_interface::ControllerInterface {
 public:
  controller_interface::InterfaceConfiguration command_interface_configuration() const override;

  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

  controller_interface::return_type update(const rclcpp::Time& time,
                                           const rclcpp::Duration& period) override;

  controller_interface::CallbackReturn on_init() override;

  controller_interface::CallbackReturn on_configure(
      const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_activate(
      const rclcpp_lifecycle::State& previous_state) override;

  controller_interface::CallbackReturn on_deactivate(
      const rclcpp_lifecycle::State& previous_state) override;

 protected:
  // Optional parameters
  std::shared_ptr<ParamListener> param_listener_;
  Params params_;

  std::shared_ptr<rclcpp::Publisher<franka_msgs::msg::FrankaState>> franka_state_publisher_;
  std::shared_ptr<realtime_tools::RealtimePublisher<franka_msgs::msg::FrankaState>>
      realtime_franka_state_publisher_;
  std::unique_ptr<franka_semantic_components::FrankaState> franka_state_;
};

}  // namespace franka_state_broadcaster
