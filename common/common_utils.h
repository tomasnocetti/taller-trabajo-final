#ifndef UTILS_H
#define UTILS_H

#include <string>

bool string_is_number(const std::string& s);

template<class T>
T swipe_bytes(T n);

/**
 * @brief Host machine to big endian.
 */
template<class T>
T to_big_end(const T n) {
  int i  = 1;
  if (*(char*) &i != 0x01) {
    return  n;
  }
  return swipe_bytes<T>(n);
}

/**
 * @brief Big endian to host machine.
 */
template<class T>
T from_big_end(const T n) {
  return to_big_end(n);
}

#endif
