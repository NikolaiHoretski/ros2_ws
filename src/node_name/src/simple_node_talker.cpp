#include <memory>

#include "rclcpp_components/register_node_macro.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace node_name {

class SimpleNodeTalker : public rclcpp::Node {

    public:
    SimpleNodeTalker(const rclcpp::NodeOptions & options) : Node("SimpleNodeTalker", options), count_(0) {

        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ =this->create_wall_timer(std::chrono::seconds(1),
                                        std::bind(&SimpleNodeTalker::timer_callback, this)
        );
    }

    private:
    void timer_callback() {
        auto msg = std_msgs::msg::String();
        msg.data = this->get_name() + std::to_string(this->count_++);   
        RCLCPP_INFO(this->get_logger(), "Node name: '%s'", msg.data.c_str());
        publisher_->publish(msg);
    }
    int count_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};
}

RCLCPP_COMPONENTS_REGISTER_NODE(node_name::SimpleNodeTalker)