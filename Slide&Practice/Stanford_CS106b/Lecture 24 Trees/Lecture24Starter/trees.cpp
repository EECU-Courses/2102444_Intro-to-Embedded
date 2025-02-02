/*
 * File: trees.cpp
 * -------------
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h"
#include "trees.h"
using namespace std;

/*
                   Pineapple
                /               \
        Coconut          Strawberry
        /       \             /           \
  Banana   Durian    X           Taro

*/
TreeNode* buildExampleTree() {
    /* TODO: Fill in this function! */
    return nullptr;
}

/*
"Do something" with the current node
Traverse the left subtree
Traverse the right subtree

Output:
PineappleCoconutBananaDurianStrawberryTaro
*/
void preorderPrintTree(TreeNode* tree) {
    (void)tree;
}

/*
Traverse the left subtree
"Do something" with the current node
Traverse the right subtree

Output:
BananaCoconutDurianPineappleStrawberryTaro
*/
void inorderPrintTree(TreeNode* tree) {
    (void)tree;
}

/*
Traverse the left subtree
Traverse the right subtree
"Do something" with the current node

Output:
BananaDurianCoconutTaroStrawberryPineapple
*/
void postorderPrintTree(TreeNode* tree) {
    (void)tree;
}

/*
 * The below code is provided as a nice utility to help visualize the
 * structure of a tree. It uses an in-order traversal (backed by a
 * breadth-first search) to accomplish this task. You do not need to
 * understand how this code works.
 */

int treeHeight(TreeNode* tree);
void printChars(int n, char c);
int longestData(TreeNode* tree);
string padString(string s, int len);

void prettyPrint(TreeNode* tree) {
    if (tree == nullptr) return;
    // calculate levels
    int numLevels = treeHeight(tree);
    int maxLength = longestData(tree);

    // go through each level and mark locations of numbers
    Queue<TreeNode*> q;
    q.enqueue(tree);
    int level = 0;
    int numberCount = 1 << level;
    int nextNumberOfCount = 0;
    int spacesSoFar = 0;
    while (!q.isEmpty()) {
        TreeNode* curr = q.dequeue();
        /* Output format:
         *             xxx
         *     xxx             xxx
         * xxx     xxx     xxx     xxx
         *
         */

        int first = (1 << (numLevels - level - 1)) - 1;
        int elementMult = 1 << (numLevels - level);
        int nextPos = (first + (nextNumberOfCount * elementMult)) * maxLength;

        printChars(nextPos - spacesSoFar, ' ');
        spacesSoFar = nextPos;
        if (curr != nullptr) {
            cout << padString(curr->data, maxLength);
        } else {
            printChars(maxLength, '-');
        }
        spacesSoFar += maxLength;
        if (curr != nullptr) {
            q.enqueue(curr->left);
            q.enqueue(curr->right);
        } else {
            q.enqueue(nullptr);
            q.enqueue(nullptr);
        }
        nextNumberOfCount++;
        if (nextNumberOfCount == numberCount) {
            nextNumberOfCount = 0;
            level++;
            numberCount = 1 << level;
            spacesSoFar = 0;
            if (level == numLevels) break; // don't print last level, which will be empty
            cout << endl;
        }
    }
    cout << endl;
}

int longestData(TreeNode* tree) {
    if (tree == nullptr) return 0;
    int longest = max(longestData(tree->left),
                      longestData(tree->right));
    return (max((int)tree->data.length(), longest));
}

void printChars(int n, char c) {
    for (int i = 0; i < n; i++) {
        cout << c;
    }
}

string padString(string s, int len) {
    /* Make the string len characters long by adding with spaces on each side. */
    int sLen = s.length();
    if ((len - sLen) % 2 == 1) {
        s += " ";
        sLen++;
    }
    for (int i = 0; i < (len - sLen) / 2; i++) {
        s = string(" ") + s + " ";
    }
    return s;
}

int treeHeight(TreeNode* tree) {
   if (tree == nullptr) {
       return 0;
   }
   int leftHeight = treeHeight(tree->left);
   int rightHeight = treeHeight(tree->right);
   if (leftHeight > rightHeight) {
       return leftHeight + 1;
   } else {
       return rightHeight + 1;
   }
}
