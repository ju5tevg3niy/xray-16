#!/usr/bin/env bash

set -ex

ninja -C meson-build-debug
ninja -C meson-build-release
