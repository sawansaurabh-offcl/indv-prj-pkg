//backup of original node tested with custom message and basic publishing

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "interfaces_indv_prj_pkg/msg/thruster_forces.hpp"

using namespace std::chrono_literals;

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<interfaces_indv_prj_pkg::msg::ThrusterForces>("thruster_forces_to_unity", 10);  // CHANGE
    timer_ = this->create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = interfaces_indv_prj_pkg::msg::ThrusterForces();
    // message.num = this->count_++;                      
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<interfaces_indv_prj_pkg::msg::ThrusterForces>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}