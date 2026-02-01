# Makefile for ESPHome Sauna Lights RF Controller
# Provides convenient shortcuts for common development tasks

.PHONY: help validate build compile flash ota ota-ip logs dashboard esphome-ui clean upgrade

# Configuration
CONFIG_FILE := sauna-lights.yaml
DEVICE_NAME := sauna-lights-356f

# Default target
help: ## Show this help message
	@echo "ESPHome Sauna Lights RF Controller - Development Commands"
	@echo ""
	@echo "Usage: make [target]"
	@echo ""
	@echo "Configuration & Build:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}'

validate: ## Validate ESPHome configuration without building
	@echo "🔍 Validating configuration..."
	esphome config $(CONFIG_FILE)

build: ## Compile firmware (same as compile)
	@echo "🔨 Building firmware..."
	esphome compile $(CONFIG_FILE)

compile: build ## Compile firmware (alias for build)

flash: ## Flash firmware via USB (first-time setup)
	@echo "📲 Flashing via USB..."
	@echo "⚠️  Connect ESP32-S3 via USB and put in flash mode if needed"
	esphome run $(CONFIG_FILE)

ota: ## Update firmware via OTA (automatic mDNS discovery)
	@echo "📡 Updating via OTA (mDNS: $(DEVICE_NAME).local)..."
	esphome upload $(CONFIG_FILE) --device $(DEVICE_NAME).local

logs: ## View device logs (real-time)
	@echo "📋 Streaming logs from device..."
	esphome logs $(CONFIG_FILE)

dashboard: ## Generate Home Assistant entity list
	@echo "📊 Generating Home Assistant entity list..."
	@echo ""
	@echo "=== SENSORS ==="
	@grep -E 'name: ".*"' $(CONFIG_FILE) | grep -E 'sensor:|text_sensor:' -A 1 | \
		grep 'name:' | sed 's/.*name: "\(.*\)".*/  - sensor.$(DEVICE_NAME)_\1/' | \
		tr '[:upper:]' '[:lower:]' | tr ' ' '_' || true
	@echo ""
	@echo "=== BUTTONS ==="
	@grep -E 'platform: template' -A 2 $(CONFIG_FILE) | grep 'name:' | \
		sed 's/.*name: "\(.*\)".*/  - button.$(DEVICE_NAME)_\1/' | \
		tr '[:upper:]' '[:lower:]' | tr ' ' '_' || true
	@echo ""
	@echo "=== SERVICES ==="
	@grep -E 'platform: template' -A 2 $(CONFIG_FILE) | grep 'name:' | \
		sed 's/.*name: "\(.*\)".*/  - esphome.$(DEVICE_NAME)_\1/' | \
		tr '[:upper:]' '[:lower:]' | tr ' ' '_' || true
	@echo ""

esphome-ui: ## Start ESPHome dashboard web UI
	@echo "🌐 Starting ESPHome dashboard..."
	@echo "🔗 Open http://localhost:6052 in your browser"
	esphome dashboard .

clean: ## Remove build artifacts
	@echo "🧹 Cleaning build artifacts..."
	rm -rf .esphome/
	@echo "✅ Clean complete"

upgrade: ## Update ESPHome to latest version
	@echo "⬆️  Updating ESPHome..."
	pip install -U esphome
	@echo "✅ ESPHome updated"
	@esphome version

# Development helpers
check-secrets: ## Verify secrets.yaml exists
	@if [ ! -f secrets.yaml ]; then \
		echo "❌ Error: secrets.yaml not found"; \
		echo "   Copy secrets.yaml.example to secrets.yaml and configure"; \
		exit 1; \
	fi
	@echo "✅ secrets.yaml exists"

check-consts: ## Verify consts.yaml exists
	@if [ ! -f consts.yaml ]; then \
		echo "❌ Error: consts.yaml not found"; \
		echo "   Copy consts.yaml.example to consts.yaml and configure"; \
		exit 1; \
	fi
	@echo "✅ consts.yaml exists"

check-config: check-secrets check-consts ## Verify all config files exist
	@echo "✅ All configuration files present"

# Quick workflows
quick-test: check-config validate ## Quick validation check
	@echo "✅ Configuration valid"

first-flash: check-config build flash ## Complete first-time setup workflow

quick-update: check-config build ota ## Quick build and OTA update

# Version info
version: ## Show ESPHome version
	@esphome version
