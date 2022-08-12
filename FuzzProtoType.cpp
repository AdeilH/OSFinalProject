#include "FuzzProtoType.hpp"

const int  Fuzz::RandomGenerators::generate_int(const int range) {
  
  srand((unsigned)time(0));
  return rand() % range;
}

const double  Fuzz::RandomGenerators::generate_double(const double range) {
  srand((unsigned)time(0));
  return static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / range));
}

// https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
const std::string  Fuzz::RandomGenerators::generate_string(const int len) {
  static const char alphanum[] = "0123456789"
                                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                 "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  tmp_s.reserve(len);

  for (int i = 0; i < len; ++i) {
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return tmp_s;
}