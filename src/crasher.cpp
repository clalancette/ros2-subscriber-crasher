#include <cstdio>
#include <functional>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/imu.hpp>

class Crasher final : public rclcpp::Node
{
public:
  Crasher() : rclcpp::Node("crasher")
  {
    fprintf(stderr, "Crasher constructor\n");
    imu_sub_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "imu", rclcpp::QoS(10), std::bind(&Crasher::imuCb, this, std::placeholders::_1));
    start_time_ = this->now();
  }

  ~Crasher()
  {
    fprintf(stderr, "Crasher destructor\n");
  }

private:
  void imuCb(const sensor_msgs::msg::Imu::SharedPtr msg)
  {
    (void)msg;

    fprintf(stderr, "imuCb %u\n", count_);

    count_++;

    rclcpp::Time now = this->now();

    if (now.seconds() - start_time_.seconds() > 5) {
      int *p = NULL;
      *p = 4;
    }
  }

  // The subscription for the command velocity input
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
  rclcpp::Time start_time_;
  uint32_t count_{0};
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);

  // Force flush of the stdout buffer, which ensures a sync of all prints
  // even from a launch file.
  setvbuf(stdout, nullptr, _IONBF, BUFSIZ);

  auto crash = std::make_shared<Crasher>();

  rclcpp::spin(crash);

  rclcpp::shutdown();

  return 0;
}
