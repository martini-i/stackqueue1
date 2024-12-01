#include<iostream>
#include<string>
#include<vector>
#include<utility>
#include <algorithm>


// Add class Stack here
class Stack
{
    private:
        void push(std::vector<std::pair<char, int>>& a, std::pair<char, int> b)
        {
            a.push_back(b);
        }
        std::pair<char, int> top(std::vector<std::pair<char, int>>& a)
        {
            if (a.size() == 0)
            {
                return std::make_pair(NULL, NULL);
            }
            return a[a.size()-1];
        }
        void pop(std::vector<std::pair<char, int>>& a)
        {
            a.pop_back();
        }
        bool match(char a, char b)
        {
            if (a == '(' && b == ')')
            {
                return true;
            }
            else if (a == '[' && b == ']')
            {
                return true;
            }
            else if (a == '{' && b == '}')
            {
                return true;
            }
            return false;
        }
        bool isOpen(char a)
        {
            return a == '(' || a == '[' || a == '{';
        }
        bool isClose(char a)
        {
            return a == ')' || a == ']' || a == '}';
        }
    public:
        void validPara(std::string pairs) {
        std::vector<std::pair<char, int>> stack;
        for (int i = 0; i < pairs.size(); i++) {
            char c = pairs[i];
            if (isOpen(c)) {
                push(stack, {c, i});
            } else if (isClose(c)) {
                if (!stack.empty() && match(top(stack).first, c)) {
                    pop(stack);
                } else {
                    std::cout << "Invalid" << std::endl;
                    return;
                }
            }
        }
        std::cout << (stack.empty() ? "Valid" : "Invalid") << std::endl;
    }

    int indexError(std::string pairs) {
        std::vector<std::pair<char, int>> stack;
        for (int i = 0; i < pairs.size(); i++) {
            char c = pairs[i];
            if (isOpen(c)) {
                push(stack, {c, i});
            } else if (isClose(c)) {
                if (!stack.empty() && match(top(stack).first, c)) {
                    pop(stack);
                } else {
                    return i;
                }
            }
        }
        return stack.empty() ? -1 : stack.front().second;
    }

    void minPara(std::string pairs) {
        std::vector<std::pair<char, int>> stack;
        int unbalanced = 0;
        for (char c : pairs) {
            if (isOpen(c)) {
                push(stack, {c, -1});
            } else if (isClose(c)) {
                if (!stack.empty() && match(top(stack).first, c)) {
                    pop(stack);
                } else {
                    unbalanced++;
                }
            }
        }
        std::cout << stack.size() + unbalanced << std::endl;
    }

    void scorePara(std::string pairs) {
        std::vector<std::pair<char, int>> stack;
        int balanced = 0;
        for (char c : pairs) {
            if (isOpen(c)) {
                push(stack, {c, -1});
            } else if (isClose(c)) {
                if (!stack.empty() && match(top(stack).first, c)) {
                    pop(stack);
                    balanced++;
                }
            }
        }
        std::cout << balanced << std::endl;
    }
};

class Queue
{
    private:
        std::vector<std::string> queue;
        std::string pop()
        {
            auto a = queue[0];
            queue.erase(queue.begin());
            return a;
        }
        std::string reverse(std::string s)
        {
            std::string a = "";
            for (int i = s.size()-1; i >= 0; i--)
            {
                a += s[i];
            }
            return a;
        }
    public:
        void enqueue(std::string s)
        {
            for (size_t i = 0; i < s.size(); i += 8)
        {
            std::string chunk = s.substr(i, 8);
            queue.push_back(reverse(chunk));
        }
    }

    void processMsg()
    {
        std::string fullMessage;
        while (!queue.empty())
        {
            fullMessage += reverse(pop());
        }
        std::cout << fullMessage << std::endl;
    }
};


int main(){
    Stack s1;
    s1.validPara("(([]))");
    s1.minPara("(([]))");
    s1.scorePara("(([]))");
    s1.validPara("(([])");
    std::cout<<s1.indexError("(([))")<<std::endl;
    s1.minPara("(([])");
    s1.validPara("(([{}))");
    std::cout<<s1.indexError("(([[}])")<<std::endl; 
    s1.minPara("(([{}))");
    s1.scorePara("(([{}))");
    std::cout<<s1.indexError("({}[]()[)")<<std::endl;
    s1.validPara("(([))");
    s1.minPara("(([))");
    std::cout<<s1.indexError("[({)]")<<std::endl;
    s1.validPara("(([{[{({})}]}]))");
    s1.minPara("(([{[{({})}]}]))");
    s1.scorePara("(([{[{({})}]}]))");
    s1.validPara("(([[{[{({})}]))");
    s1.validPara("(([[{[{({})}]}])]))");
    s1.scorePara("(([[{[{({})}]}])]))");
    std::cout<<s1.indexError("(([[{{({})]}])]))")<<std::endl;
    s1.validPara("(())");
    s1.validPara("(())");
    s1.validPara("void function(){}");
    s1.scorePara("void function(){}");
    s1.validPara("void function(");
    s1.minPara("void function(");
    s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
    s1.scorePara("void function(std::string expre){if(expre){return 1;}else{return 0;}}");
    s1.validPara("void function(std::string expre){if(expre){return 1;}else{return 0;}");
    s1.validPara("void function(std::string expre){if(expre){return 1;else{return 0;");
    s1.minPara("void function(std::string expre){if(expre){return 1;else{return 0;");
    std::cout<<s1.indexError("void function(std::string expre){if(expre){return 1;else{return 0;")<<std::endl;
    Queue q1;
    q1.enqueue("This is a secure message.");
    q1.processMsg();
    q1.enqueue("The product I received is damaged. What should I do?");
    q1.processMsg();
    q1.enqueue("I need assistance with setting up my new device");
    q1.processMsg();
    q1.enqueue("The website is not loading properly on my browser.");
    q1.processMsg();
    q1.enqueue("I accidentally placed the wrong order. Can it be canceled?");
    q1.processMsg();
    q1.enqueue("This is your project3. Have a happy thanksgiving!!! Hahaha");
    q1.processMsg();
    q1.enqueue("I forgot my password and can't reset it. Help, please! Do you provide technical support for mobile devices?");
    q1.processMsg();
    q1.enqueue("The software update is causing issues on my computer. The response time on your website is very slow.");
    q1.processMsg();
    return 0;
}