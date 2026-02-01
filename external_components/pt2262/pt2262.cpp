#include "pt2262.h"

namespace esphome {
namespace pt2262 {

void PT2262Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up PT2262 transmitter on GPIO%d", this->pin_->get_pin());
  this->pin_->setup();
  this->pin_->digital_write(false);
}

void PT2262Component::dump_config() {
  ESP_LOGCONFIG(TAG, "PT2262 Transmitter:");
  LOG_PIN("  Pin: ", this->pin_);
  ESP_LOGCONFIG(TAG, "  Repeat: %d times", this->repeat_times_);
  ESP_LOGCONFIG(TAG, "  Timing: short=%dus, long=%dus", PULSE_SHORT, PULSE_LONG);
}

void PT2262Component::send_tristate(const std::string &code) {
  ESP_LOGD(TAG, "Sending tri-state code: %s", code.c_str());

  // Send the code multiple times (match original remote behavior)
  for (uint8_t i = 0; i < this->repeat_times_; i++) {
    {
      // Disable interrupts for accurate timing - PER TRANSMISSION to avoid watchdog
      InterruptLock lock;

      // Sync pulse
      this->send_sync();

      // Send each tri-state symbol as a pulse pair
      for (char symbol : code) {
        this->send_symbol(symbol);
      }

      // Trailing pulse
      this->tx_high(PULSE_SHORT);
      this->tx_low(GAP_LONG);
    }

    // Small fixed delay between transmissions (match original remote timing)
    // No yield() - transmissions should be back-to-back for reliable reception
    if (i < this->repeat_times_ - 1) {
      delayMicroseconds(100);  // Minimal gap, just enough to release InterruptLock
    }
  }

  // Ensure pin is low after transmission
  this->pin_->digital_write(false);
}

void PT2262Component::send_sync() {
  // PT2262 sync: short pulse followed by very long gap
  this->tx_high(SYNC_PULSE);
  this->tx_low(SYNC_GAP);
}

void PT2262Component::send_symbol(char symbol) {
  // PT2262 4-state tri-state encoding
  // Each symbol is encoded as TWO pulses (a pulse pair)
  // Pattern: pulse1 + SHORT gap, pulse2 + LONG gap
  switch (symbol) {
    case '0':  // LOW state: short/short (CORRECTED - was backwards!)
      this->tx_high(PULSE_SHORT);
      this->tx_low(GAP_SHORT);   // SHORT gap between pulses in pair
      this->tx_high(PULSE_SHORT);
      this->tx_low(GAP_LONG);    // LONG gap after symbol complete
      break;

    case '1':  // HIGH state: long/long (CORRECTED - was backwards!)
      this->tx_high(PULSE_LONG);
      this->tx_low(GAP_SHORT);   // SHORT gap between pulses in pair
      this->tx_high(PULSE_LONG);
      this->tx_low(GAP_LONG);    // LONG gap after symbol complete
      break;

    case 'X':  // FLOAT state: long/short
    case 'F':  // Alternative notation for FLOAT
      this->tx_high(PULSE_LONG);
      this->tx_low(GAP_SHORT);   // SHORT gap between pulses in pair
      this->tx_high(PULSE_SHORT);
      this->tx_low(GAP_LONG);    // LONG gap after symbol complete
      break;

    case 'Z':  // 4th state: short/long
      this->tx_high(PULSE_SHORT);
      this->tx_low(GAP_SHORT);   // SHORT gap between pulses in pair
      this->tx_high(PULSE_LONG);
      this->tx_low(GAP_LONG);    // LONG gap after symbol complete
      break;

    default:
      ESP_LOGW(TAG, "Invalid tri-state character: %c", symbol);
      break;
  }
}

void PT2262Component::tx_high(uint32_t us) {
  this->pin_->digital_write(true);
  delayMicroseconds(us);
}

void PT2262Component::tx_low(uint32_t us) {
  this->pin_->digital_write(false);
  delayMicroseconds(us);
}

}  // namespace pt2262
}  // namespace esphome
