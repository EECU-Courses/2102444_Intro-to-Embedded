#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

int add(int &i){
    i++;
    cout << "I add 1" << endl;
    return i;
}

int die(int i){
    int die = 0;
    while (i!=0){
        die += 1;
        i--;
    }
    i = i;
    cout << "i in die = " << i << endl;
    return die;
}

int main() {
    int i = 10;

    cout << "i = " << i << endl;
    cout << "Die(i) = " << die(i) << endl;
    cout << "i = " << i << endl;
    add(i);
    cout << "i = " << i << endl;
    cout << "i = " << i << endl;

    cout << "______________________________________________" << endl;
    list<int> number = {1,2,3,4,5};
    number.insert(number.end(), 84);
    cout << (number.back()) << endl;

    int j = 9;
    int t = 9.3; // t = 9
    t -= j/2; // t -= 4 : t = 5
    t -= j/2; // t -= 4 : t = 1
    t -= j/2; // t -= 4 : t = -3
    cout << "t : " << t << endl;

    
}
