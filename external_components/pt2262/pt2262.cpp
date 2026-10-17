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
  ESP_LOGCONFIG(TAG, "  Timing: short=%" PRIu32 "us, long=%" PRIu32 "us", PULSE_SHORT, PULSE_LONG);
}

void PT2262Component::send_tristate(const std::string &code) {
  ESP_LOGD(TAG, "Sending tri-state code: %s", code.c_str());

  // Each frame is the data followed by a short sync pulse and a long sync gap,
  // repeated back to back like the original remote. The receiver acts only
  // after consecutive identical frames.
  for (uint8_t i = 0; i < this->repeat_times_; i++) {
    {
      // Interrupts off for accurate pulse timing; released for the sync gap
      InterruptLock lock;
      for (char symbol : code) {
        this->send_symbol(symbol);
      }
      this->tx_high(PULSE_SHORT);
      this->pin_->digital_write(false);
    }
    // Sync gap timing is not critical, so it runs with interrupts enabled
    delayMicroseconds(SYNC_GAP);
  }
}

void PT2262Component::send_short() {
  this->tx_high(PULSE_SHORT);
  this->tx_low(GAP_LONG);
}

void PT2262Component::send_long() {
  this->tx_high(PULSE_LONG);
  this->tx_low(GAP_SHORT);
}

void PT2262Component::send_symbol(char symbol) {
  switch (symbol) {
    case '0':  // LOW: short/short
      this->send_short();
      this->send_short();
      break;

    case '1':  // HIGH: long/long
      this->send_long();
      this->send_long();
      break;

    case 'X':  // FLOAT: long/short
    case 'F':  // Alternative notation for FLOAT
      this->send_long();
      this->send_short();
      break;

    case 'Z':  // 4th state: short/long
      this->send_short();
      this->send_long();
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
