#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pt2262 {

static const char *const TAG = "pt2262";

/// PT2262 Remote Control Transmitter Component
///
/// Supports proper 4-state tri-state encoding:
/// - '0' = LOW  (short/short pulse pair)
/// - '1' = HIGH (long/long pulse pair)
/// - 'X' = FLOAT (long/short pulse pair)
/// - 'Z' = 4th state (short/long pulse pair)
class PT2262Component : public Component {
 public:
  void set_pin(InternalGPIOPin *pin) { pin_ = pin; }
  void set_repeat_times(uint8_t times) { repeat_times_ = times; }

  void setup() override;
  void dump_config() override;

  /// Send a PT2262 tri-state code
  /// @param code Tri-state code string (e.g., "0X00Z1XZ00ZZ")
  void send_tristate(const std::string &code);

 protected:
  InternalGPIOPin *pin_;
  uint8_t repeat_times_{4};  // Match original remote

  // Timing parameters (from original remote analysis)
  static constexpr uint32_t PULSE_SHORT = 432;   // microseconds
  static constexpr uint32_t PULSE_LONG = 1232;   // microseconds
  static constexpr uint32_t GAP_SHORT = 392;     // microseconds
  static constexpr uint32_t GAP_LONG = 1192;     // microseconds
  static constexpr uint32_t SYNC_PULSE = 432;    // short pulse before sync gap
  static constexpr uint32_t SYNC_GAP = 12020;    // microseconds (very long gap)

  /// Send a single pulse pair for a tri-state symbol
  void send_symbol(char symbol);

  /// Send sync pulse
  void send_sync();

  /// Transmit high for specified microseconds
  void tx_high(uint32_t us);

  /// Transmit low for specified microseconds
  void tx_low(uint32_t us);
};

}  // namespace pt2262
}  // namespace esphome
