#include <iostream>
using namespace std;

struct Node {
    string key, value;
    Node *left, *right;

    Node(string k, string v) {
        key = k;
        value = v;
        left = right = NULL;
    }
};

class Dictionary {
    Node* root;

    Node* insert(Node* root, string k, string v) {
        if (!root) return new Node(k, v);
        if (k == root->key)
            root->value = v;
        else if (k < root->key)
            root->left = insert(root->left, k, v);
        else
            root->right = insert(root->right, k, v);
        return root;
    }

    Node* minValueNode(Node* n) {
        Node* cur = n;
        while (cur && cur->left) cur = cur->left;
        return cur;
    }

    Node* deleteNode(Node* root, string k) {
        if (!root) return NULL;
        if (k < root->key)
            root->left = deleteNode(root->left, k);
        else if (k > root->key)
            root->right = deleteNode(root->right, k);
        else {
            if (!root->left) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (!root->right) {
                Node* temp = root->left;
                delete root;
                return temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        return root;
    }

    Node* search(Node* root, string k) {
        if (!root || root->key == k) return root;
        if (k < root->key)
            return search(root->left, k);
        return search(root->right, k);
    }

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        cout << root->key << ": " << root->value << endl;
        inorder(root->right);
    }

    void mirror(Node* root) {
        if (!root) return;
        mirror(root->left);
        mirror(root->right);
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }

    Node* copyTree(Node* root) {
        if (!root) return NULL;
        Node* newNode = new Node(root->key, root->value);
        newNode->left = copyTree(root->left);
        newNode->right = copyTree(root->right);
        return newNode;
    }

    void levelOrder(Node* root) {
        if (!root) return;
        Node* q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Node* cur = q[front++];
            cout << cur->key << ": " << cur->value << endl;
            if (cur->left) q[rear++] = cur->left;
            if (cur->right) q[rear++] = cur->right;
        }
    }

public:
    Dictionary() {
        root = NULL;
    }

    void insert(string k, string v) {
        root = insert(root, k, v);
    }

    void deleteWord(string k) {
        root = deleteNode(root, k);
    }

    void searchWord(string k) {
        Node* res = search(root, k);
        if (res)
            cout << "Found: " << res->key << " -> " << res->value << endl;
        else
            cout << "Not Found\n";
    }

    void display() {
        cout << "Dictionary (Inorder):\n";
        inorder(root);
    }

    void makeMirror() {
        mirror(root);
        cout << "Mirror created.\n";
    }

    Dictionary getCopy() {
        Dictionary d;
        d.root = copyTree(root);
        return d;
    }

    void levelDisplay() {
        cout << "Level-wise Display:\n";
        levelOrder(root);
    }
};

int main() {
    Dictionary dict, copyDict;
    int choice;
    string word, meaning;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert word\n";
        cout << "2. Search word\n";
        cout << "3. Delete word\n";
        cout << "4. Display (Inorder)\n";
        cout << "5. Mirror image\n";
        cout << "6. Create copy\n";
        cout << "7. Display level-wise\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                dict.insert(word, meaning);
                break;
            case 2:
                cout << "Enter word to search: ";
                cin >> word;
                dict.searchWord(word);
                break;
            case 3:
                cout << "Enter word to delete: ";
                cin >> word;
                dict.deleteWord(word);
                break;
            case 4:
                dict.display();
                break;
            case 5:
                dict.makeMirror();
                dict.display();
                break;
            case 6:
                copyDict = dict.getCopy();
                cout << "Copy of dictionary:\n";
                copyDict.display();
                break;
            case 7:
                dict.levelDisplay();
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 8);

    return 0;
}