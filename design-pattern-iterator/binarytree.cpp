#include <iostream>


using namespace std;


// Declaration Node ! //
template <typename T> struct Node
{
    T value;
    Node<T> *left {nullptr};
    Node<T> *right {nullptr};
    Node<T> *parent {nullptr};
    BinaryTree<T>* tree {nullptr}
};

explicit Node (const T& value) : value(value) { }

Node (const T& value, Node<T>* const left, Node<T>* const right) : value {value}, left{left}, right{right}
{
    this->left->tree = this->right->tree = tree;
    this->left->parent = this->right->parent = this;
}

void set_tree(BinaryTree<T>* t)
{
    tree = t;
    if (left)
    {
        left->set_tree(t);
    }
    if (right)
    {
        right->set_tree(t);
    }
};

template<typename U>
struct PreOrderIterator
{
    Node<U>* current;

    explicit PreOrderIterator(Node<U>* current) : current (current)
    {
    }

    bool operator!=(const PreOrderIterator<U>& other)
    {
        return current != other.current;
    }

    Node<U>& operator*()
    {
        return *current;
    }

    PreOrderIterator<U>& operator++()
    {
        if(current->right)
        {
            current = current->right;
            while(current->left)
            {
                current = current->left;
            }
        }
        else
        {
            Node<T>* p = current->parent;
            while(p&& current == p->right)
            {
                current = p;
                p = p->parent;
            }
            current = p;
        }
        return *this;
    }
};

typedef PreOrderIterator<T> iterator;

iterator begin()
{
    Node<T>* n = root;

    if (n)
    {
        while(n->left)
        {
            n=n->left;
        }
    }
    return iterator{n};
}

iterator end()
{
    return iterator { nullptr };
}

BinaryTree<string> family
{
    new Node<string>
    { "me" , new Node<string> { "mother ", new Node<string>{"mothers mother"}, new Node<string>{"mothers father"}}, 
        new Node <string> {"father"}
    } 
};

for(auto it = family.begin(); it != family.end(); ++it)
{
    std::cout << (*it).value << "\n";
}

class pre_order_traversal
{
    BinaryTree<T>& tree;

    public:
        pre_order_traversal(BinaryTree<T>& tee) : tree { tree } {}
        iterator begin() { return tree.begin(); }
        iterator end() { return tree.end(); }    
} pre_order;

// Coroutine //
generator<Node<T>*> post_order_impl(Node<T>* node)
{
    if (node)
    {
        for (auto x: post_order_impl(node->left))
        {
            co_yield x;
        }
        for (auto y: post_order_impl(node->right))
        {
            co_yield y;
        }
        co_yield node;
    }
};

generator<Node<T>*> post_order()
{
    return post_order_impl(root);
};


