#ifndef _MYINFIXPOSTFIX_
#define _MYINFIXPOSTFIX_
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include<stdio.h>
#include<ctype.h>
#include "myStack.hpp"
class myInfixPostfix
{
private:
bool isOprand(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == ' ');
}
int Prec(char ch)
{
    switch(ch)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}

public:
    myInfixPostfix(){}
    ~myInfixPostfix(){}
    std::string getPostfix(std::string str)
    {
        myStack<std::string> sign;
        std::string results;
        for(int i = 0; i < str.length(); i++)
        {
            if (str[i] == ' '){} //等于空格
            else if (!isOprand(str[i])) //是数字
            {
                results += '('; //答案 += （
                results += str[i]; //答案 += 当前字符
                while (isdigit(str[i+1])) //下一个字符是否是数字
                    results += str[++i];//答案+= 下一个字符 ++i
                results += ')'; //答案 += ）
            }
            else if(Prec(str[i]) != -1) //当前字符是运算符号，不是括号（也不是数字 也不是空格）
            {
                if(sign.empty())//stack是空的
                    sign.push(str[i]);//直接push
                else if(Prec(str[i]) > Prec(sign.top()[0]))//当前优先级大于上一位
                    sign.push(str[i]); //直接push
                else if (Prec(str[i]) < Prec(sign.top()[0])) //当前优先级小于上一位
                {
                    while (Prec(str[i]) <= Prec(sign.top()[0]) && !sign.empty())
                        results += sign.pop(); //结果 加上当前字符 stack.pop
                    sign.push(str[i]); //stack push 当前字符
                }
                else //优先级相等时
                {
                    results += sign.pop();
                    sign.push(str[i]);
                }
            }
            else // prec == -1 是括号
            {
                if(str[i] == '(') //当前字符等于(
                    sign.push(str[i]); //直接加
                else //等于）时
                {
                    while(sign.top()[0] != '(') //当stack top 没找到 （
                        results += sign.pop(); // 答案等于stack top（pop）
                    sign.pop();//pop掉 （
                }   
            }
        }
        while(!sign.empty())
            results += sign.pop();
        // std::cout << "results =   " << results << std::endl;
        return results;
    }
    float PostfixCalculator(std::string exp)
    {
        myStack<float> nums;
        for(int i = 0; i < exp.length(); i++)
        {
            if(exp[i] == '(')
            {
                std::string temp;
                while(exp[i+1] != ')')
                    temp += exp[++i];
                float num = std::stof(temp);
                nums.push(num);
            }
            else if (exp[i] == '+')
            {
                float b = nums.pop();
                float a = nums.pop();
                float c = a + b;
                nums.push(c);
            }
            else if (exp[i] == '-')
            {
                float b = nums.pop();
                float a = nums.pop();
                float c = a - b;
                nums.push(c);
            }
            else if (exp[i] == '*')
            {
                float b = nums.pop();
                float a = nums.pop();
                float c = a * b;
                nums.push(c);
            }
            else if (exp[i] == '/')
            {
                float b = nums.pop();
                float a = nums.pop();
                float c = a / b;
                nums.push(c);
            }
        }
        return nums.pop();
    }
};
#endif