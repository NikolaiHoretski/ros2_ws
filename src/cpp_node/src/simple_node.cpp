#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

void node_info(std::shared_ptr<rclcpp::node_interfaces::NodeBaseInterface> base_interface,
                std::shared_ptr<rclcpp::node_interfaces::NodeLoggingInterface> logging_interface) {

RCLCPP_INFO(logging_interface->get_logger(), "Node name: %s", base_interface->get_name());

}

class SimpleNode : public rclcpp::Node {

    public:
    SimpleNode(const std::string & node_name) : Node(node_name) {}

};

class LifecycleTalker : public rclcpp_lifecycle::LifecycleNode {
    public:
    explicit LifecycleTalker(const std::string & node_name, bool intra_procces_comms = false)
    : rclcpp_lifecycle::LifecycleNode(node_name, 
    rclcpp::NodeOptions().use_intra_process_comms(intra_procces_comms)) {}
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::executors::SingleThreadedExecutor exe;
    auto node = std::make_shared<SimpleNode>("Simple_Node");
    auto ls_node = std::make_shared<LifecycleTalker>("Simple_Lifecycle_Node");
    node_info(node->get_node_base_interface(), node->get_node_logging_interface());
    node_info(ls_node->get_node_base_interface(), ls_node->get_node_logging_interface());
}



