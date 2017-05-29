#!/bin/bash

BOARD="arduino:avr:nano:cpu=atmega328"
PORT="$(ls /dev/ttyUSB* | head -n1)"
ACTION="--upload"
ARDUINO="/home/cmooney/arduino-1.8.2/arduino"
INO_LOCATION="/home/cmooney/beacon/beacon.ino"

JAVA_TOOL_OPTIONS='-Djava.awt.headless=true' "${ARDUINO}" "${ACTION}" "${INO_LOCATION}" --board "${BOARD}" --port "${PORT}"
