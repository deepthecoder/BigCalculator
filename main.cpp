#include <bits/stdc++.h>
#include "BigInt.h"
using namespace std;

std::string infixToPostfix(const std::string &infix);
ds::BigInt evaluatePostfix(const std::string &postfix);
int main(int argc, char *argv[]) {
   ds::BigInt a("456");
   ds::BigInt b("1123");
   cout<<b<<endl;
   ds::BigInt s = a + b;
   cout << s << endl;

   ds::BigInt d = a - b;
   cout << d << endl;

   ds::BigInt p = a * b;
   cout << p << endl;

   std::string postfix = infixToPostfix("(456 + 1123 * 32453 - 345 - (2345345 + ( 3245 - 1234)) - 5675473 - ( 1234 + 234 ) - 657) * ( 679 - ( 435 + 2345 ))");
   cout << postfix << endl;

   ds::BigInt r = evaluatePostfix(postfix);
   cout << r << endl;
}
