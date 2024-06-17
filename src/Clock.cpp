#include <chrono>
#include "Clock.h"

long long Clock::getSystemNanos() {
  auto now = std::chrono::system_clock::now().time_since_epoch();
  auto now_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now);
  return now_ns.count();
}

void Clock::start() {
  startTime = getSystemNanos();
}

void Clock::stop() {
  nanos += getSystemNanos() - startTime;
}

double Clock::getSeconds() {
  return nanos * 0.000'000'001;
}
