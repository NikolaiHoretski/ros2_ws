#include <memory>

#include "rclcpp_components/register_node_macro.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace node_name {

class SimpleNodeListener : public rclcpp::Node {
public:
SimpleNodeListener(const rclcpp::NodeOptions & options) : Node("SimpleNodeListener", options) {
subscription_ = this->create_subscription<std_msgs::msg::String>(
    "chatter", 10,
    std::bind(&SimpleNodeListener::callback, this, std::placeholders::_1)
);
}


private:

void callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(this->get_logger(), "I heard: %s", msg->data.c_str());
}

rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    
};
}

RCLCPP_COMPONENTS_REGISTER_NODE(node_name::SimpleNodeListener)
