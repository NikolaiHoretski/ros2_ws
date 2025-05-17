#include "rclcpp/rclcpp.hpp"
#include "rclcpp_components/register_node_macro.hpp"


namespace palomino {
    class VincentDriver : public rclcpp::Node {

        public:
        VincentDriver(const rclcpp::NodeOptions & options) : Node("vincent_driver", options) {
            
              RCLCPP_INFO(this->get_logger(), "Vincent Driner component started");
        }


    };
}

RCLCPP_COMPONENTS_REGISTER_NODE(palomino::VincentDriver)