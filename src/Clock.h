#pragma once

class Clock {

public:
  void start();
  void stop();
  double getSeconds();

private:
  long long startTime;
  long long nanos = 0;
  long long getSystemNanos();
};
