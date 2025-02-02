#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    std::vector<int> myVector;

    // กำหนดขนาดเริ่มต้นของ vector
    myVector.reserve(10);

    cout << "Initial capacity: " << myVector.capacity() << endl;

    // เพิ่มสมาชิกใน vector
    for (int i = 0; i < 20; ++i) {
        myVector.push_back(i);
        std::cout << "Capacity after adding element " << i + 1 << ": " << myVector.capacity() << std::endl;
    }
    cout << "Last capacity: " << myVector.capacity() << endl;

    
}
