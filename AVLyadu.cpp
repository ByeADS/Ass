#include <iostream>
#include <algorithm>
using namespace std;

// Node structure for each player
struct Node {
    int player_id;
    int score;
    Node* left;
    Node* right;
    int height;
};

// Get height of a node
int getHeight(Node* root) {
    if (root == nullptr)
        return 0;
    return root->height;
}

// Create a new node for a player
Node* createNode(int player_id, int score) {
    Node* root = new Node();
    root->player_id = player_id;
    root->score = score;
    root->left = nullptr;
    root->right = nullptr;
    root->height = 1;
    return root;
}

// Get balance factor to check if node is balanced
int getBalanceFactor(Node* root) {
    if (root == nullptr)
        return 0;
    return getHeight(root->left) - getHeight(root->right);
}

// Right rotation (LL case)
Node* rightRotate(Node* root) {
    Node* x = root->left;
    Node* T2 = x->right;

    x->right = root;
    root->left = T2;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Left rotation (RR case)
Node* leftRotate(Node* root) {
    Node* y = root->right;
    Node* T2 = y->left;

    y->left = root;
    root->right = T2;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Insert player into AVL tree using score as key
Node* insert(Node* root, int player_id, int score) {
    if (root == nullptr)
        return createNode(player_id, score);

    if (score < root->score)
        root->left = insert(root->left, player_id, score);
    else if (score > root->score)
        root->right = insert(root->right, player_id, score);
    else {
        cout << "Duplicate score not allowed.\n";
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    // Balancing the tree
    if (balance > 1 && score < root->left->score)
        return rightRotate(root);
    if (balance < -1 && score > root->right->score)
        return leftRotate(root);
    if (balance > 1 && score > root->left->score) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && score < root->right->score) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find the node with minimum score (used in deletion)
Node* getMinValueNode(Node* root) {
    Node* current = root;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Remove player by score
Node* deleteNode(Node* root, int score) {
    if (root == nullptr)
        return root;

    if (score < root->score)
        root->left = deleteNode(root->left, score);
    else if (score > root->score)
        root->right = deleteNode(root->right, score);
    else {
        // Node found
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = getMinValueNode(root->right);
            root->score = temp->score;
            root->player_id = temp->player_id;
            root->right = deleteNode(root->right, temp->score);
        }
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Display leaderboard in descending order
void displayLeaderboard(Node* root) {
    if (root != nullptr) {
        displayLeaderboard(root->right);  // Reverse in-order for descending
        cout << "Player ID: " << root->player_id << " | Score: " << root->score << endl;
        displayLeaderboard(root->left);
    }
}

int main() {
    Node* root = nullptr;

    // Register players
    root = insert(root, 101, 500);
    root = insert(root, 102, 800);
    root = insert(root, 103, 300);
    root = insert(root, 104, 600);
    root = insert(root, 105, 700);

    cout << "\nLeaderboard:\n";
    displayLeaderboard(root);

    // Remove a player by score
    cout << "\nRemoving player with score 500...\n";
    root = deleteNode(root, 500);

    cout << "\nUpdated Leaderboard:\n";
    displayLeaderboard(root);

return 0;
}