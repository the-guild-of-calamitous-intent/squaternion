
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <array>

bool is_ascii(const char c) {
  if (c >= 33 && c <= 126) return true;
  return false;
}

bool get_serial(const char* cmd, std::string &result) {
  std::array<char, 128> buffer{0};
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    return false;
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    for (int i=0; i < buffer.size(); ++i) {
      char c = buffer[i];
      if (c == '\0') break;
      if (is_ascii(c)) result += c;
    }
  }

  return true;
}