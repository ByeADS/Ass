#include <iostream>
using namespace std;

struct Node {
    int id, score;
    int height;
    Node *left, *right;

    Node(int pid, int s) {
        id = pid;
        score = s;
        height = 1;
        left = right = NULL;
    }
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int id, int score) {
    if (!node) return new Node(id, score);

    if (id < node->id)
        node->left = insert(node->left, id, score);
    else if (id > node->id)
        node->right = insert(node->right, id, score);
    else {
        node->score = score;
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int bal = getBalance(node);

    if (bal > 1 && id < node->left->id)
        return rotateRight(node);
    if (bal < -1 && id > node->right->id)
        return rotateLeft(node);
    if (bal > 1 && id > node->left->id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bal < -1 && id < node->right->id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* cur = node;
    while (cur->left != NULL)
        cur = cur->left;
    return cur;
}

Node* deleteNode(Node* root, int id) {
    if (!root) return root;

    if (id < root->id)
        root->left = deleteNode(root->left, id);
    else if (id > root->id)
        root->right = deleteNode(root->right, id);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->id = temp->id;
            root->score = temp->score;
            root->right = deleteNode(root->right, temp->id);
        }
    }

    if (!root) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bal = getBalance(root);

    if (bal > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (bal > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (bal < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (bal < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void leaderboard(Node* root) {
    if (!root) return;
    leaderboard(root->right);
    cout << "Player ID: " << root->id << ", Score: " << root->score << "\n";
    leaderboard(root->left);
}

int main() {
    Node* root = NULL;
    int choice, id, score;

    do {
        cout << "\n--- Multiplayer Game System ---\n";
        cout << "1. Register Player\n";
        cout << "2. Show Leaderboard\n";
        cout << "3. Remove Player\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Player ID: ";
                cin >> id;
                cout << "Enter Score: ";
                cin >> score;
                root = insert(root, id, score);
                cout << "Player Registered.\n";
                break;
            case 2:
                cout << "\n--- Leaderboard (High to Low) ---\n";
                leaderboard(root);
                break;
            case 3:
                cout << "Enter Player ID to remove: ";
                cin >> id;
                root = deleteNode(root, id);
                cout << "Player Removed.\n";
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Choice.\n";
        }

    } while(choice != 4);

    return 0;
}