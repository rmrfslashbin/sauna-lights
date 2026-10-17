#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace pt2262 {

static const char *const TAG = "pt2262";

/// PT2262 Remote Control Transmitter Component
///
/// PWM with a constant ~1624us period: a short pulse is followed by a long
/// gap and a long pulse by a short gap. Each tri-state symbol is two pulses:
/// - '0' = LOW  (short/short pulse pair)
/// - '1' = HIGH (long/long pulse pair)
/// - 'X' = FLOAT (long/short pulse pair)
/// - 'Z' = 4th state (short/long pulse pair)
/// Frame: 24 data pulses, then a short sync pulse and a ~12ms sync gap.
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

  // Timing from RTL_433 captures of the original remote (docs/buttons/*.txt)
  static constexpr uint32_t PULSE_SHORT = 420;   // followed by GAP_LONG
  static constexpr uint32_t PULSE_LONG = 1216;   // followed by GAP_SHORT
  static constexpr uint32_t GAP_SHORT = 408;
  static constexpr uint32_t GAP_LONG = 1204;
  static constexpr uint32_t SYNC_GAP = 12032;    // after the trailing short pulse

  /// Send the two pulses of a tri-state symbol
  void send_symbol(char symbol);

  /// Send one PWM pulse and its complementary gap
  void send_short();
  void send_long();

  /// Transmit high for specified microseconds
  void tx_high(uint32_t us);

  /// Transmit low for specified microseconds
  void tx_low(uint32_t us);
};

}  // namespace pt2262
}  // namespace esphome
