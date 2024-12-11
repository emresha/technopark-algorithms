#include <iostream>
#include <string>

struct Node
{
    long long key;
    int height;
    Node *left;
    Node *right;
    Node *parent;

    Node(long long k)
    {
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

int height(Node *node)
{
    return node ? node->height : 0;
}

int balance_factor(Node *node)
{
    return height(node->right) - height(node->left);
}

void fix_height(Node *node)
{
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = std::max(hl, hr) + 1;
}

Node *rotate_left(Node *p)
{
    Node *q = p->right;
    q->parent = p->parent;
    p->right = q->left;
    if (q->left)
        q->left->parent = p;
    q->left = p;
    p->parent = q;
    fix_height(p);
    fix_height(q);
    return q;
}

Node *rotate_right(Node *p)
{
    Node *q = p->left;
    q->parent = p->parent;
    p->left = q->right;
    if (q->right)
        q->right->parent = p;
    q->right = p;
    p->parent = q;
    fix_height(p);
    fix_height(q);
    return q;
}

Node *balance(Node *node)
{
    fix_height(node);
    if (balance_factor(node) == 2)
    {
        if (balance_factor(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    if (balance_factor(node) == -2)
    {
        if (balance_factor(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    return node;
}

Node *insert(Node *root, long long key, Node *&new_node)
{
    if (!root)
    {
        new_node = new Node(key);
        return new_node;
    }
    if (key < root->key)
    {
        root->left = insert(root->left, key, new_node);
        root->left->parent = root;
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key, new_node);
        root->right->parent = root;
    }
    return balance(root);
}

Node *find_min(Node *node)
{
    return node->left ? find_min(node->left) : node;
}

Node *remove_min(Node *node)
{
    if (!node->left)
        return node->right;
    node->left = remove_min(node->left);
    if (node->left)
        node->left->parent = node;
    return balance(node);
}

Node *remove(Node *root, long long key)
{
    if (!root)
        return nullptr;
    if (key < root->key)
    {
        root->left = remove(root->left, key);
        if (root->left)
            root->left->parent = root;
    }
    else if (key > root->key)
    {
        root->right = remove(root->right, key);
        if (root->right)
            root->right->parent = root;
    }
    else
    {
        Node *left = root->left;
        Node *right = root->right;
        
        if (!right)
        {
            if (left)
                left->parent = root->parent;
            
            delete root;
            return left;
        }
        Node *min = find_min(right);
        min->right = remove_min(right);
        if (min->right)
            min->right->parent = min;
        min->left = left;
        if (left)
            left->parent = min;
        min->parent = root->parent;
        delete root;
        return balance(min);
    }
    return balance(root);
}

bool exists(Node *root, long long key)
{
    if (!root)
        return false;
    if (key == root->key)
        return true;
    if (key < root->key)
        return exists(root->left, key);
    else
        return exists(root->right, key);
}

Node *next(Node *root, long long key)
{
    Node *succ = nullptr;
    while (root)
    {
        if (root->key > key)
        {
            succ = root;
            root = root->left;
        }
        else
            root = root->right;
    }
    return succ;
}

Node *prev(Node *root, long long key)
{
    Node *pred = nullptr;
    while (root)
    {
        if (root->key < key)
        {
            pred = root;
            root = root->right;
        }
        else
            root = root->left;
    }
    return pred;
}

int main(void)
{
    std::string command;
    long long x;
    Node *root = nullptr;

    while (std::cin >> command >> x)
    {
        if (command == "insert")
        {
            if (!exists(root, x))
            {
                Node *new_node = nullptr;
                root = insert(root, x, new_node);
            }
        }
        else if (command == "delete")
        {
            if (exists(root, x))
            {
                root = remove(root, x);
            }
        }
        else if (command == "exists")
        {
            std::cout << (exists(root, x) ? "true" : "false") << '\n';
        }
        else if (command == "next")
        {
            Node *succ = next(root, x);
            if (succ)
                std::cout << succ->key << '\n';
            else
                std::cout << "none\n";
        }
        else if (command == "prev")
        {
            Node *pred = prev(root, x);
            if (pred)
                std::cout << pred->key << '\n';
            else
                std::cout << "none\n";
        }
    }

    return 0;
}
