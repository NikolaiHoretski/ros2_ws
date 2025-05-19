#include <memory>
#include "rclcpp/rclcpp.hpp"

class SimpleNode : public rclcpp::Node {

    public:
    SimpleNode(const std::string & node_name) : Node(node_name), count_(0) {

        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&SimpleNode::timer_callback, this)
        );
    }

    private:

    void timer_callback() {
        count_++;
        RCLCPP_INFO(this->get_logger(),
         "Node name: %s - %d", 
         this->get_name(), 
         count_);
    }
    int count_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleNode>("Simple_Node");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}