/*
Постройте B-дерево минимального порядка t и выведите его по слоям.
В качестве ключа используются числа, лежащие в диапазоне [0..2^32 - 1]

Требования:

B-дерево должно быть реализовано в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Формат ввода
Сначала вводится минимальный порядок дерева t.
Затем вводятся элементы дерева.

Формат вывода
Программа должна вывести B-дерево по слоям.
Каждый слой на новой строке, элементы должны выводится в том порядке, в котором они лежат в узлах.
*/

#include <bits/stdc++.h>
using namespace std;

// компаратор
int compare(void *a, void *b)
{
    return *(int *)a - *(int *)b;
}

template <typename Key>
class BTreeNode
{
public:
    bool is_leaf;
    vector<Key> keys;
    vector<BTreeNode *> children;

    BTreeNode(bool leaf)
    {
        is_leaf = leaf;
    }

    void insert_non_full(Key key, int (*cmp)(void *, void *), int t)
    {
        int i = keys.size() - 1;

        if (is_leaf)
        {
            keys.push_back(key);
            while (i >= 0 && cmp(&key, &keys[i]) < 0)
            {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
        }
        else
        {
            while (i >= 0 && cmp(&key, &keys[i]) < 0)
                i--;
            i++;

            if (children[i]->keys.size() == 2 * t - 1)
            {
                split_child(i, children[i], cmp, t);

                if (cmp(&key, &keys[i]) > 0)
                    i++;
            }
            children[i]->insert_non_full(key, cmp, t);
        }
    }

    void split_child(int i, BTreeNode *y, int (*cmp)(void *, void *), int t)
    {
        BTreeNode *z = new BTreeNode(y->is_leaf);
        for (int j = 0; j < t - 1; j++)
            z->keys.push_back(y->keys[j + t]);

        if (!y->is_leaf)
        {
            for (int j = 0; j < t; j++)
                z->children.push_back(y->children[j + t]);
            y->children.resize(t);
        }

        y->keys.resize(t - 1);

        children.insert(children.begin() + i + 1, z);

        keys.insert(keys.begin() + i, y->keys[t - 1]);
    }
};

template <typename Key>
class BTree
{
public:
    BTreeNode<Key> *root;
    int t;
    int (*cmp)(void *, void *);

    BTree(int t_degree, int (*comparator)(void *, void *))
    {
        root = nullptr;
        t = t_degree;
        cmp = comparator;
    }

    void insert(Key key)
    {
        if (root == nullptr)
        {
            root = new BTreeNode<Key>(true);
            root->keys.push_back(key);
        }
        else
        {
            if (root->keys.size() == 2 * t - 1)
            {
                BTreeNode<Key> *s = new BTreeNode<Key>(false);
                s->children.push_back(root);
                s->split_child(0, root, cmp, t);

                int i = 0;
                if (cmp(&key, &s->keys[0]) > 0)
                    i++;
                s->children[i]->insert_non_full(key, cmp, t);

                root = s;
            }
            else
                root->insert_non_full(key, cmp, t);
        }
    }

    vector<vector<Key>> level_order_traversal() const
    {
        vector<vector<Key>> levels;
        if (root == nullptr)
            return levels;

        queue<BTreeNode<Key> *> q;
        q.push(root);

        while (!q.empty())
        {
            int level_size = q.size();
            vector<Key> current_level;

            for (int i = 0; i < level_size; ++i)
            {
                BTreeNode<Key> *node = q.front();
                q.pop();

                for (const auto &key : node->keys)
                    current_level.push_back(key);

                if (!node->is_leaf)
                {
                    for (auto child : node->children)
                        q.push(child);
                }
            }
            levels.push_back(current_level);
        }

        return levels;
    }

    ~BTree()
    {
        if (root == nullptr)
            return;

        stack<BTreeNode<Key> *> s;
        stack<BTreeNode<Key> *> output;

        s.push(root);
        while (!s.empty())
        {
            BTreeNode<Key> *node = s.top();
            s.pop();
            output.push(node);
            if (!node->is_leaf)
            {
                for (auto child : node->children)
                    s.push(child);
            }
        }

        while (!output.empty())
        {
            BTreeNode<Key> *node = output.top();
            output.pop();
            delete node;
        }
    }
};

int main(void)
{
    int t;
    cin >> t;

    BTree<int> tree(t, compare);

    int key;
    while (cin >> key)
        tree.insert(key);

    vector<vector<int>> levels = tree.level_order_traversal();

    for (const auto &level : levels)
    {
        for (size_t i = 0; i < level.size(); ++i)
        {
            if (i > 0)
                cout << " ";
            cout << level[i];
        }
        cout << "\n";
    }

    return 0;
}
