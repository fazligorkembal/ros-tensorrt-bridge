class Tracker
{
public:
  Tracker() = default;
  ~Tracker() = default;

  void setTracker(const std::string &name, const std::string &value)
  {
    tracker_[name] = value;
  }

  std::string getTracker(const std::string &name)
  {
    return tracker_[name];
  }
}