
#include "common_utils.h"
#include <string>

bool string_is_number(const std::string& s){
  for (const char& c : s) {
    if (! (c >= '0' && c <= '9')) return false;
  }
  return true;
}

template<>
uint16_t swipe_bytes<uint16_t>(uint16_t n) {
  return  ((n<<8)&0xff00) | // move byte 1 to byte 2
          ((n>>8)&0x00ff);  // move byte 2 to byte 1
}
template<>
uint32_t swipe_bytes<uint32_t>(uint32_t n) {
  return  ((n>>24)&0xff) | // move byte 3 to byte 0
          ((n<<8)&0xff0000) | // move byte 1 to byte 2
          ((n>>8)&0xff00) | // move byte 2 to byte 1
          ((n<<24)&0xff000000); // byte 0 to byte 3;
}
