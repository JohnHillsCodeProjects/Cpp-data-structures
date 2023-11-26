#include <iostream>
#include "BinaryTree.h"
#include <string>

using namespace std;

void removalTest()
{
    BinaryTree<int,char> tree;
    int nodes[14] = { 8,4,12,14,6,10,2,1,3,5,7,9,13,11 };
    for (int i = 0; i < 14; i++) tree.insert(nodes[i] * 10, 'n');
    cout << "Template tree\n";
    tree.displayTree();
    BinaryTree<int, char> tree1(tree), tree2(tree), tree3(tree), tree4(tree);
    cout << "\nRemove leaf node (70)\n";
    tree1.remove(70); char* value1 = tree1.lookup(70);
    cout << "Look up for value 70 finds " << value1 << endl;
    cout << "\nRemove node with one child(140)\n";
    tree2.remove(140); tree2.displayTree();
    cout << "\nRemove node with 2 children (80)\n";
    tree3.remove(80); tree3.displayTree();
    //TreeNode* value3 = tree3.findNode(100);
    //cout << value3->children[0] << " " << value3->children[1] << endl;
    cout << "\nRemove nonexistent node (87)\n";
    tree4.remove(87); tree4.displayTree();
}

void moveTest()
{
    BinaryTree<int, char> tree1;
    int nodes[14] = { 8,4,12,14,6,10,2,1,3,5,7,9,13,11 };
    for (int i = 0; i < 14; i++) tree1.insert(nodes[i], 'n');
    cout << "Before move:\ntree1.isTreeEmpty() = " << tree1.isTreeEmpty() << "\ntree2 = tree1: ";
    BinaryTree<int, char> tree2(std::move(tree1));
    cout << "After move:\ntree1.isTreeEmpty() = " << tree1.isTreeEmpty() << "\ntree2.isTreeEmpty() = " << tree2.isTreeEmpty() << endl;
}

struct tst { int x, y, z; };

tst operator+(tst t1, tst t2) {
    tst ret;
    int x = t1.x + t2.x;
    int y = t1.y + t2.y;
    int z = t1.z + t2.z;
    ret.x = x; ret.y = y; ret.z = z;
    return ret;
}

void tstOperatorTest()
{
    tst t1 = { 3,4,5 };
    tst t2 = { 7,8,9 };
    tst t3 = { 11,12,13 };
    tst t4 = t1 + t2;
    tst t5 = t1 + t2 + t3;
    cout << "t4 = { " << t4.x << "," << t4.y << "," << t4.z << " }" << endl;
    cout << "t5 = { " << t5.x << "," << t5.y << "," << t5.z << " }" << endl;
}

void assignmentTest()
{
    BinaryTree<int, char> tree1;
    int nodes[6] = { 8,4,12,14,6,10 };
    for (int i = 0; i < 6; i++) tree1.insert(nodes[i], 'n');

    BinaryTree<int, char> tree2(tree1); //Normal copy
    cout << "tree2 root = " << tree2.getRoot()->key << " " << tree2.getRoot()->value << endl << endl;

    BinaryTree<int, char> tree3; tree3 = tree1; //Operator copy
    cout << "tree3 root = " << tree3.getRoot()->key << " " << tree3.getRoot()->value << endl << endl;

    BinaryTree<int, char> tree4(std::move(tree2)); //Normal move
    cout << "tree2.isTreeEmpty() = " << tree2.isTreeEmpty() << " | tree4.isTreeEmpty() = " << tree4.isTreeEmpty();
    cout << "\ntree4 root = " << tree4.getRoot()->key << " " << tree4.getRoot()->value << endl << endl;

    BinaryTree<int, char> tree5; tree5 = std::move(tree3); //Operator move
    cout << "tree3.isTreeEmpty() = " << tree3.isTreeEmpty() << " | tree5.isTreeEmpty() = " << tree5.isTreeEmpty();
    cout << "\ntree5 root = " << tree5.getRoot()->key << " " << tree5.getRoot()->value << endl << endl;
}

int main(int argc, char* argv[])
{
    assignmentTest();
    moveTest();
    removalTest();
    return 0;
}