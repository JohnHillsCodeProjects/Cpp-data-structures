#include "SLList.h"
#include <iostream>

using std::cout;
using std::endl;

void first_tests() {
    cout << "\nTesting basic constructor, empty(), push_front() and push_back() on empty and non-empty lists, length() on list with 0 to 2 items\n";
    SLList<char> list1;
    if (list1.empty()) cout << "Pass: Constructor and empty test.\n";
    else cout << "~~~Fail: Constructor and empty test.\n";

    SLList<char> list2;
    list2.push_front('X');
    SLList<char> list3;
    list3.push_back('X');
    if (!list2.empty()) cout << "Pass: push_front() on empty list.\n";
    else cout << "~~~Fail: push_front() on empty list.\n";
    if (!list3.empty()) cout << "Pass: push_back() on empty list.\n";
    else cout << "~~~Fail: push_back() on empty list.\n";

    list3.push_front('O');
    list3.push_back('O');
    if (list1.length() == 0) cout << "Pass: length() on empty list.\n";
    else cout << "~~~Fail: length() on empty list. Output: " << list1.length() << endl;
    if (list2.length() == 1) cout << "Pass: length() on single node.\n";
    else cout << "~~~Fail: length() on single node. Output: " << list2.length() << endl;
    if (list3.length() == 3) cout << "Pass: length() on 3 nodes.\n";
    else cout << "~~~Fail: length() on 3 nodes. Output: " << list3.length() << endl;

    cout << "\nTesting displayAll on lists.";
    cout << "\nlist1: Expected = This list is empty. | Output = "; list1.displayAll(); 
    cout << "\nlist2: Expected = (X) | Output = "; list2.displayAll();
    cout << "\nlist3: Expected = (O , X , O) | Output = "; list3.displayAll();
    cout << "\nSince this test relies on console output, it's difficult for the code to determine a pass or fail itself.\n\n";

    list3.insert(1, '7');
    list3.displayAll(); cout << endl;
    if (list3.length() == 4) cout << "Pass: insert() on list3 preserves length.\n";
    else cout << "~~~Fail: insert() on list3 didn't preserve length. Output: " << list3.length() << endl;
}

int main()
{
    cout << "Begin testing SLList\n";
    first_tests();
}