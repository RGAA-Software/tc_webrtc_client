// Copyright (c) Microsoft Corporation

#ifndef THIRD_PARTY_WIN_VIRTUAL_DISPLAY_DRIVER_INDIRECTMONITOR_H_
#define THIRD_PARTY_WIN_VIRTUAL_DISPLAY_DRIVER_INDIRECTMONITOR_H_

// Make sure we don't get min/max macros
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>

#include <vector>

#include "Edid.h"
#include "public/properties.h"

namespace display::test {
// Represents a virtual monitor, encapsulates an EDID and modes.
struct IndirectMonitor {
  static constexpr size_t kModeListLength = 1;
  // Internal ID for identifying this monitor.
  unsigned short id = 0;
  // Modified EDID from Dell S2719DGF
  std::array<unsigned char, Edid::kBlockSize> pEdidBlock = {
      0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xC4, 0x0E, 0xE6, 0xD0,
      0x55, 0x5A, 0x4A, 0x30, 0x24, 0x1D, 0x01, 0x04, 0xA5, 0x3C, 0x22, 0x78,
      0xFB, 0x6C, 0xE5, 0xA5, 0x55, 0x50, 0xA0, 0x23, 0x0B, 0x50, 0x54, 0x00,
      0x02, 0x00, 0xD1, 0xC0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
      0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x58, 0xE3, 0x00, 0xA0, 0xA0, 0xA0,
      0x29, 0x50, 0x30, 0x20, 0x35, 0x00, 0x55, 0x50, 0x21, 0x00, 0x00, 0x1A,
      0x00, 0x00, 0x00, 0xFF, 0x00, 0x37, 0x4A, 0x51, 0x58, 0x42, 0x59, 0x32,
      0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x53,
      0x32, 0x37, 0x31, 0x39, 0x44, 0x47, 0x46, 0x0A, 0x20, 0x20, 0x20, 0x20,
      0x00, 0x00, 0x00, 0xFD, 0x00, 0x28, 0x9B, 0xFA, 0xFA, 0x40, 0x01, 0x0A,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x2C};
  std::vector<MonitorConfig> pConfigList;
};
}  // namespace display::test

#endif  // THIRD_PARTY_WIN_VIRTUAL_DISPLAY_DRIVER_INDIRECTMONITOR_H_