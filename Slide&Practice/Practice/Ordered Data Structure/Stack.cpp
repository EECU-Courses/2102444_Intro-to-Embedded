#include <iostream> 
#include <stack>
using namespace std;
int main() {
	stack<int> stack;
	stack.push(21);// The values pushed in the stack should be of the same data which is written during declaration of stack
	stack.push(22);
	stack.push(24);
	stack.push(25);
	int num=0;
	stack.push(num);
	stack.pop();
	stack.pop();
	stack.pop();

	while (!stack.empty()) {
		cout << stack.top() <<" " << endl;
		stack.pop();
	}

    cout << "_________________________________________" << endl;

    std::stack<std::string> wordStack;
    wordStack.push("dog");
    wordStack.push("cat");
    wordStack.push("mourse");
    cout << wordStack.top() << endl;
    wordStack.pop();
    cout << wordStack.top() << endl;
    wordStack.pop();
    return 0;
}
