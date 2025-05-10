#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

class AddressBookSubscriber : public rclcpp::Node {

public:
AddressBookSubscriber() : Node("address_book_subscriber") {
    
    auto subscriber_msg = [this](const more_interfaces::msg::AddressBook::SharedPtr msg) -> void {
        
    std::cout << "I head\nFirst:" << msg->first_name << 
    " Last:" << msg->last_name << " Phone number:" << msg->phone_number <<
    " Phone type:" << static_cast<int>(msg->phone_type) << std::endl;
 
    };

    address_book_subscriber_ = this->create_subscription<more_interfaces::msg::AddressBook>(
        "address_book", 10, subscriber_msg);
}


private:
rclcpp::Subscription<more_interfaces::msg::AddressBook>::SharedPtr address_book_subscriber_;
    
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddressBookSubscriber>());
    rclcpp::shutdown();

    return 0;
}