#include <iostream>
#include <string>
using namespace std;

bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}
int checkPrecedence(char c)
{
    if (c == '^') {return 3;}
    if (c == '*' || c == '/') {return 2;}
    if (c == '+' || c == '-') {return 1;}
    if (c == '(') {return 0;}
    return -1;
}

int evaluatePostfix(string Pos)
{
    string Stack;
    for (int i = 0; i < Pos.length(); ++i)
    {
        char c = Pos[i];
        if (isOperator(c))
        {
            char op2 = Pos.back() - 48;
            Pos.pop_back();

            char op1 = Pos.back() - 48;
            Pos.pop_back();

        }
        else
        {
            Stack.push_back(c);
        }
    }

}

int main()
{
    string In, Pos, Stack;

    cout << "Enter you infix expression" << endl;
    cin >> In;
    cout << In << endl;
    
    for (int i = 0; i < In.length(); ++i)
    {
        char c = In[i];
        cout << i << " currently " << c << endl;
        if (c == '(') 
        {
            Stack.push_back(c);
        }
        else if (c == ')')
        {
            while (Stack.back() != '(')
            {
                char o = Stack.back();
                Pos.push_back(o);
                Stack.pop_back();
            }
            Stack.pop_back();
        }    
        else if (isOperator(c))
        {
            while (checkPrecedence(Stack.back()) >= checkPrecedence(c))
            {
                char o = Stack.back();
                Stack.pop_back();
                Pos.push_back(o);
            }
            Stack.push_back(c);
        }
        else
        {
            Pos.push_back(c);
        }
    }
    while(!Stack.empty())
    {
        char o = Stack.back();
        Pos.push_back(o);
        Stack.pop_back();
    }
    cout << Pos << endl;
    
    cout << endl << evaluatePostfix(Pos);
    return 0;
}