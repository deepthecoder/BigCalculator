#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <bits/stdc++.h>

namespace ds
{
  class BigInt
  {
  public:
    std::vector<int> digits;

  public:
    BigInt(const std::string &val);
    BigInt(const BigInt &other) {}

    friend std::ostream &operator<<(std::ostream &os, const BigInt &bi);

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
  };

} // namespace ds

#endif // __BIGINT_H__
