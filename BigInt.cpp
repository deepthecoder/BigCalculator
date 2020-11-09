#include "BigInt.h"
#include <iostream>
#include <algorithm>



/**
 * this file consists of functions which
 * evaluate the basic arithmetic operations
 * and can accept big integers.
 *
 */





namespace ds
{
  BigInt::BigInt(const std::string &val)
  {
    for (size_t j = 0; j < val.size(); j++)
    {
      digits.push_back(val[j] - '0');
    }
  }

  std::ostream &operator<<(std::ostream &os, const BigInt &bi)
  {
    for (int i = 0; i < bi.digits.size(); i++)
      os << bi.digits[i];
    return os;
  }

  //function for performing the addition operation
  BigInt BigInt::operator+(const BigInt &other) const
  {

    std::string num1 = "", num2 = "";
    for (int i = 0; i < digits.size(); i++)
    {
      num1.push_back(digits[i] + '0');
    }

    for (int i = 0; i < other.digits.size(); i++)
    {
      num2.push_back(other.digits[i] + '0');
    }

    if (num1.size() > num2.size())
      swap(num1, num2);
    // Take an empty string for storing result
    std::string str = "";

    // Calculate length of both string
    int n1 = num1.size(), n2 = num2.size();

    // Reverse both of strings
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    int carry = 0;
    for (int i = 0; i < n1; i++)
    {
      // Do school mathematics, compute sum of
      // current digits and carry
      int sum = ((num1[i] - '0') + (num2[i] - '0') + carry);
      str.push_back(sum % 10 + '0');

      // Calculate carry for next step
      carry = sum / 10;
    }

    // Add remaining digits of larger number
    for (int i = n1; i < n2; i++)
    {
      int sum = ((num2[i] - '0') + carry);
      str.push_back(sum % 10 + '0');
      carry = sum / 10;
    }

    // Add remaining carry
    if (carry)
      str.push_back(carry + '0');

    // reverse resultant string
    reverse(str.begin(), str.end());

    BigInt sum(str);
    return sum;
  }

  //function to perform subtraction operator
  BigInt BigInt::operator-(const BigInt &other) const
  {

    std::string num1 = "", num2 = "";
    for (int i = 0; i < digits.size(); i++)
    {
      num1.push_back(digits[i] + '0');
    }

    for (int i = 0; i < other.digits.size(); i++)
    {
      num2.push_back(other.digits[i] + '0');
    }

    int n1 = num1.size(), n2 = num2.size();
    if (n2 > n1)
      swap(num1, num2);
    else
    {
      if (n1 == n2)
      {
        for (int i = 0; i < n1; i++)
        {
          if (num1[i] < num2[i])
          {
            swap(num1, num2);
            break;
          }
          if(num1[i] > num2[i])
          {
              break;
          }
        }
      }
    }

    std::string str = "";

    n1 = num1.length(), n2 = num2.length();

    // Reverse both of strings
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());

    int carry = 0;

    // Run loop till small string length
    // and subtract digit of num1 to num2
    for (int i = 0; i < n2; i++)
    {
      // Do school mathematics, compute difference of current digits
      int sub = ((num1[i] - '0') - (num2[i] - '0') - carry);

      // If subtraction is less then zero
      // we add then we add 10 into sub and
      // take carry as 1 for calculating next step
      if (sub < 0)
      {
        sub = sub + 10;
        carry = 1;
      }
      else
      {
        carry = 0;
      }
        str.push_back(sub + '0');
    }

    // subtract remaining digits of larger number
    for (int i = n2; i < n1; i++)
    {
      int sub = ((num1[i] - '0') - carry);

      // if the sub value is -ve, then make it positive
      if (sub < 0)
      {
        sub = sub + 10;
        carry = 1;
      }
      else
        carry = 0;
      str.push_back(sub + '0');
    }

    // reverse resultant string

    while(str[str.size()-1]=='0' && str.size()>1)
    {

        str.pop_back();
    }
    reverse(str.begin(), str.end());
    BigInt aDiff(str);
    return aDiff;
  }

  //function to perform multiplication operator
  BigInt BigInt::operator*(const BigInt &other) const
  {

    std::string num1 = "", num2 = "";
    for (int i = 0; i < digits.size(); i++)
    {
      num1.push_back(digits[i] + '0');
    }

    for (int i = 0; i < other.digits.size(); i++)
    {
      num2.push_back(other.digits[i] + '0');
    }

    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
      return (BigInt("0"));

    // will keep the result number in vector
    // in reverse order
    std::vector<int> result(len1 + len2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i = len1 - 1; i >= 0; i--)
    {
      int carry = 0;
      int n1 = num1[i] - '0';

      // To shift position to left after every
      // multiplication of a digit in num2
      i_n2 = 0;

      // Go from right to left in num2
      for (int j = len2 - 1; j >= 0; j--)
      {
        // Take current digit of second number
        int n2 = num2[j] - '0';

        // Multiply with current digit of first number
        // and add result to previously stored result
        // at current position.
        int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

        // Carry for next iteration
        carry = sum / 10;

        // Store result
        result[i_n1 + i_n2] = sum % 10;

        i_n2++;
      }

      // store carry in next cell
      if (carry > 0)
        result[i_n1 + i_n2] += carry;

      // To shift position to left after every
      // multiplication of a digit in num1.
      i_n1++;
    }


    // ignore '0's from the right
    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
      i--;
    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
      return (BigInt("0"));
    // generate the result string
    std::string s = "";

    for(int k=result.size()-1;k>=0;k--)
    {
        if(k==result.size()-1 && result[k]!=0)
            s+=result[k]+'0';
        else if(k!=result.size()-1)
            s+=result[k]+'0';
    }
    return BigInt(s);
  }
} // namespace ds
