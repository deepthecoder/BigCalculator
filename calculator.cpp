#include "BigInt.h"
#include <stack>
#include<iostream>


/**
 * This file consists of helper functions
 * which first evaluates the infix expression
 * converts to postfix expression
 * and then evaluate the postfix expression.
 *
 */





std::string infixToPostfix(const std::string &infix)
{
  std::string postfix;

  /** Precedence of operators
   * Multiplication(*) has the highest precedence
   * Addition and Subtraction have the 2nd highest precedece.
   */

  std::map<char, int> prec;
  prec['*'] = 2;
  prec['+'] = 1;
  prec['-'] = 1;

  std::stack<char> st;             //initializing the stack of type character
  st.push('N');                    //The stack initially holds character N which denotes empty stack.
  int infixLen = infix.length();   //infixLen is the length of the infix string provided by console.


  //parsing the characters of the infix expression.
  for (int i = 0; i < infixLen; i++)
  {

    if (infix[i] == ' ' || infix[i] == '\t'||infix[i] == '\n')   //Replacing extra spaces, tab spaces, newlines with single space
      postfix +=' ';


    if ((infix[i] >= '0' && infix[i] <= '9'))                    // If the scanned character is an operand, add it to output string.
      postfix += infix[i];

    /** If the scanned character is an operator
     *
     *if stack is empty, push the operator
     *if stack has an operator,check the precedence and based on that insertion is done.
     */


    else if(infix[i]=='+'||infix[i]=='*'||infix[i]=='-')
    {
        char c=infix[i];
        if(st.top()=='N')
            st.push(c);
        else
        {
            if(st.top()!='N' && st.top()!='(' && prec[st.top()]>=prec[c])
            {
                postfix+=st.top();
                st.pop();
                st.push(c);
            }
            else
                st.push(c);
        }
    }
    else if(infix[i]=='(')
    {
        st.push('(');
    }
    else if(infix[i]==')')    //If the operator is ')', keep popping the operators until a '(' is encountered.
    {
        while(st.top()!='N')
        {
            if(st.top()=='(')
            {
                st.pop();
                break;
            }
            else
            {
                postfix+=st.top();
                st.pop();
            }
        }
    }
  }

  //popping the remaining operators in the stack.
  while (st.top() != 'N')
  {
    char c = st.top();
    st.pop();
    postfix += c;
  }
return postfix;

}

//helper function to evaluate the Postfix string
ds::BigInt evaluatePostfix(const std::string &postfix)
{
    ds::BigInt result("");
    std::string s="";
    int j=0;
    std::stack<std::string> st;     //stack for storing the operands temporarily until an operand is met

    //evaluating the postfix expression and parsing the characters
    for(size_t i=0;i<postfix.size();i++)
    {
        if(postfix[i]-'0'>=0 && postfix[i]-'0'<=9)       //if the character is a digit, push it onto stack.
        {
            for(j=i;j<postfix.size();j++)
            {
                if(isdigit(postfix[j]))
                {
                    s+=postfix[j];
                }
                else
                    break;
            }
            st.push(s);
            s="";
            i=j;
        }
        if(postfix[i]!=' ')
        {
            std::string a=st.top();
            st.pop();
            std::string b=st.top();
            st.pop();
            ds::BigInt x(a);
            ds::BigInt y(b);

            //checking for the operator and applying them accordingly.
            if(postfix[i]=='+')
            {
                     result=x+y;
            }
            if(postfix[i]=='-')
            {
                     result=x-y;
            }
            if(postfix[i]=='*')
            {
                     result=x*y;
            }

            //storing the result of the of the arithmetic operation as a temporary string.
            for(int h=0;h<result.digits.size();h++)
            {
                int g=result.digits[h];
                s+=std::to_string(g);
            }
            st.push(s);    //pushing the final string into the stack.
            s="";          //clearing the string.
        }
    }
    return result;
}

