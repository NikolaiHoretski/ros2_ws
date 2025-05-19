#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class SimpleNode : public rclcpp::Node {

    public:
    SimpleNode(const std::string & node_name) : Node(node_name), count_(0) {

        publisher_ = this->create_publisher<std_msgs::msg::String>("chatter", 10);
        timer_ =this->create_wall_timer(std::chrono::seconds(1),
                                        std::bind(&SimpleNode::timer_callback, this)
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

int main(int argc, char * argv[]) {

    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimpleNode>("Simple_Node");
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}