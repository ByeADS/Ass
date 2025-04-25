#include <iostream>
#include <queue>
using namespace std;

struct node {
    string word;
    string key;
    node* left;
    node* right;

    node(string w, string k) {
        word = w;
        key = k;
        left = nullptr;
        right = nullptr;
    }
};

// Insert by key
node* insert(node* root, string word, string key) {
    if (root == nullptr) {
        return new node(word, key);
    }
    if (key < root->key) {
        root->left = insert(root->left, word, key);
    } else if (key > root->key) {
        root->right = insert(root->right, word, key);
    }
    return root;
};

// Level-order traversal
void levelOrder(node* root) {
    if (root == nullptr) return;
    queue<node*> q;
    q.push(root);
    while (!q.empty()) {
        node* curr = q.front();
        q.pop();
        cout << "(" << curr->key << ", " << curr->word << ") ";
        if (curr->left != nullptr) q.push(curr->left);
        if (curr->right != nullptr) q.push(curr->right);
    }
}

// Pre-order traversal
void preOrder(node* root) {
    if (root == nullptr) return;
    cout << "(" << root->key << ", " << root->word << ") ";
    preOrder(root->left);
    preOrder(root->right);
}

// Post-order traversal
void postOrder(node* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << "(" << root->key << ", " << root->word << ") ";
}

// In-order traversal
void inOrder(node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << "(" << root->key << ", " << root->word << ") ";
    inOrder(root->right);
}

// Search by key
node* search(node* root, string key) {
    if (root == nullptr || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

// Get inorder successor
node* getSuccessor(node* root) {
    node* curr = root->right;
    while (curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}

// Delete by key
node* delNode(node* root, string key) {
    if (root == nullptr) return root;
    if (key < root->key) {
        root->left = delNode(root->left, key);
    } else if (key > root->key) {
        root->right = delNode(root->right, key);
    } else {
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        }
        node* succ = getSuccessor(root);
        root->key = succ->key;
        root->word = succ->word;
        root->right = delNode(root->right, succ->key);
    }
    return root;
}

int main() {
    node* root = nullptr;
    char choice;

    do {
        int option;
        cout << "\nMenu:\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Delete a word\n";
        cout << "4. Level-order traversal\n";
        cout << "5. Pre-order traversal\n";
        cout << "6. Post-order traversal\n";
        cout << "7. In-order traversal\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: {
                string word, key;
                cout << "Enter the word: ";
                cin >> word;
                cout << "Enter the key: ";
                cin >> key;
                root = insert(root, word, key);
                break;
            }
            case 2: {
                string key;
                cout << "Enter the key to search: ";
                cin >> key;
                node* found = search(root, key);
                if (found) {
                    cout << "Found: " << found->word << endl;
                } else {
                    cout << "Key not found.\n";
                }
                break;
            }
            case 3: {
                string key;
                cout << "Enter the key to delete: ";
                cin >> key;
                root = delNode(root, key);
                cout << "Node deleted (if found).\n";
                break;
            }
            case 4:
                cout << "Level-order traversal: ";
                levelOrder(root);
                cout << endl;
                break;
            case 5:
                cout << "Pre-order traversal: ";
                preOrder(root);
                cout << endl;
                break;
            case 6:
                cout << "Post-order traversal: ";
                postOrder(root);
                cout << endl;
                break;
            case 7:
                cout << "In-order traversal: ";
                inOrder(root);
                cout << endl;
                break;
            case 8:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        cout << "Do you want to perform another operation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    return 0;
}
