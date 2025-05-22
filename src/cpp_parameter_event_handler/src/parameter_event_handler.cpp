#include <memory>

#include "rclcpp/rclcpp.hpp"

class SampleNodeWithParameters : public rclcpp::Node
{
public:
  SampleNodeWithParameters()
  : Node("node_with_parameters")
  {
    this->declare_parameter("another_double_param", 0.0);

    param_subscriber_ = std::make_shared<rclcpp::ParameterEventHandler>(this);
   
    auto event_cb = [this](const rcl_interfaces::msg::ParameterEvent & parameter_event) {
      RCLCPP_INFO(
        this->get_logger(), "Received parameter event from node \"%s\"",
        parameter_event.node.c_str()
      );

      for(const auto& p : parameter_event.changed_parameters) {
        RCLCPP_INFO(
          this->get_logger(), "Inside event: \"%s\" changed to %s", p.name.c_str(),
          rclcpp::Parameter::from_parameter_msg(p).value_to_string().c_str()
        );
      };
    };

  event_cb_handler_= param_subscriber_->add_parameter_event_callback(event_cb);
    
  }

private:
  std::shared_ptr<rclcpp::ParameterEventHandler> param_subscriber_;
 std::shared_ptr<rclcpp::ParameterEventCallbackHandle> event_cb_handler_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SampleNodeWithParameters>());
  rclcpp::shutdown();

  return 0;
}