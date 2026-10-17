# ESPHome secrets template — committed; holds 1Password references, not values.
# Generate secrets.yaml (gitignored) with: make secrets
#   (runs: op inject -i secrets.yaml.tpl -o secrets.yaml)

# WiFi (shared item, also used by other devices; referenced by item ID)
wifi_ssid: "{{ op://Secret Keys/3e7ptma7shahmvgmitc6tzmcgu/SSID }}"
wifi_password: "{{ op://Secret Keys/3e7ptma7shahmvgmitc6tzmcgu/password }}"

# Fallback access point (when WiFi fails)
ap_password: "{{ op://Secret Keys/sauna-lights ESPHome/ap_password }}"

# API encryption key: encrypts the Home Assistant connection AND authenticates
# OTA uploads (ota: encryption inherits it). Losing it means USB reflash.
api_encryption_key: "{{ op://Secret Keys/sauna-lights ESPHome/api_encryption_key }}"
