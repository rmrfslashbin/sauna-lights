#pragma once

#include "esphome/core/automation.h"
#include "pt2262.h"

namespace esphome {
namespace pt2262 {

template<typename... Ts> class PT2262SendAction : public Action<Ts...> {
 public:
  PT2262SendAction(PT2262Component *parent) : parent_(parent) {}

  TEMPLATABLE_VALUE(std::string, code)

  void play(Ts... x) override {
    auto code = this->code_.value(x...);
    this->parent_->send_tristate(code);
  }

 protected:
  PT2262Component *parent_;
};

}  // namespace pt2262
}  // namespace esphome
