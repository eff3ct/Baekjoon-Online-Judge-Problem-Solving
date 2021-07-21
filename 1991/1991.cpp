// https://www.acmicpc.net/problem/1991 //
#include <iostream>

using namespace std;

class Node {
    private:
        char label;
        Node* left;
        Node* right;

    public:
        //initializer
        Node() {
            label = '\0';
            left = NULL; right = NULL;
        }
        //add child node
        void addNodeLR(Node* l, Node* r) {
            left = l;
            right = r;
        }
        //set label
        void setLabel(char lab) {
            label = lab;
        }
        //print label
        void printLabel() {
            cout << label;
        }
        //get left
        Node* getLeft() {
            return left;
        }
        //get right
        Node* getRight() {
            return right;
        }
};

void printPreOrder(Node* root) {
    if(root == NULL) return;
    root->printLabel();
    printPreOrder(root->getLeft());
    printPreOrder(root->getRight());
}
void printInOrder(Node* root) {
    if(root == NULL) return;
    printInOrder(root->getLeft());
    root->printLabel();
    printInOrder(root->getRight());
}
void printPostOrder(Node* root) {
    if(root == NULL) return;
    printPostOrder(root->getLeft());
    printPostOrder(root->getRight());
    root->printLabel();
}

int main() {
    int N; cin >> N;

    Node* root = new Node[N];

    for(int i = 0; i < N; ++i) {
        root[i].setLabel('A' + i);
    }

    for(int i = 0; i < N; ++i) {
        char rootNode, leftNode, rightNode;
        cin >> rootNode >> leftNode >> rightNode;
        if(leftNode != '.' && rightNode != '.') {
            rootNode -= 'A'; leftNode -= 'A'; rightNode -= 'A';
            root[rootNode].addNodeLR(&root[leftNode], &root[rightNode]);
        }
        else if(leftNode == '.' && rightNode != '.') {
            rootNode -= 'A'; rightNode -= 'A';
            root[rootNode].addNodeLR(NULL, &root[rightNode]);
        }
        else if(leftNode != '.' && rightNode == '.') {
            rootNode -= 'A'; leftNode -= 'A';
            root[rootNode].addNodeLR(&root[leftNode], NULL);
        }
    }

    printPreOrder(&root[0]);
    cout << "\n";
    printInOrder(&root[0]);
    cout << "\n";
    printPostOrder(&root[0]);

    delete[] root;
    return 0;
}