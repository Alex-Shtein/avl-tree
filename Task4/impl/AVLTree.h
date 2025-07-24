#ifndef IMPL_AVLTREE_H
#define IMPL_AVLTREE_H

template <typename T>
AVLTree<T>::Node::Node(const T &key, Node *left, Node *right)
{
    _key = key;
    _left = left;
    _right = right;
    _height = 1;
}

template <typename T>
AVLTree<T>::Node::~Node()
{
    delete _left;
    delete _right;
}

template <typename T>
T AVLTree<T>::Node::GetKey()
{
    return _key;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::GetLeft()
{
    return _left;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::Node::GetRight()
{
    return _right;
}

template <typename T>
int AVLTree<T>::Node::GetHeight()
{
    return _height;
}

template <typename T>
void AVLTree<T>::Node::SetKey(const T &key)
{
    _key = key;
}

template <typename T>
void AVLTree<T>::Node::SetLeft(Node *left)
{
    _left = left;
}

template <typename T>
void AVLTree<T>::Node::SetRight(Node *right)
{
    _right = right;
}

template <typename T>
void AVLTree<T>::Node::SetHeight(int height)
{
    _height = height;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::Find(const T &key)
{
    if (Empty())
    {
        return nullptr;
    }
    Node *current = _root;
    while (current != nullptr)
    {
        if (key < current->GetKey())
        {
            current = current->GetLeft();
        }
        else if (key > current->GetKey())
        {
            current = current->GetRight();
        }
        else
        {
            return current;
        }
    }
    return current;
}

template <typename T>
int AVLTree<T>::Height(Node *node)
{
    return (!node ? -1 : node->GetHeight());
}

template <typename T>
int AVLTree<T>::GetBalance(Node *node)
{
    if (!node)
        return 0;
    else
        return Height(node->GetLeft()) - Height(node->GetRight());
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::Rotate(Node *node)
{
    int balance = GetBalance(node);

    if (balance > 1)
    {
        if (GetBalance(node->GetLeft()) >= 0)
        {
            return RightRotate(node);
        }
        else
        {
            node->SetLeft(LeftRotate(node->GetLeft()));
            return RightRotate(node);
        }
    }

    if (balance < -1)
    {
        if (GetBalance(node->GetRight()) <= 0)
        {
            return LeftRotate(node);
        }
        else
        {
            node->SetRight(RightRotate(node->GetRight()));
            return LeftRotate(node);
        }
    }

    return node;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::RemoveR(const T &key, Node *node)
{
    if (node == NULL)
        return node;

    if (key < node->GetKey())
        node->SetLeft(RemoveR(key, node->GetLeft()));

    else if (key > node->GetKey())
        node->SetRight(RemoveR(key, node->GetRight()));

    else
    {
        if ((!node->GetLeft()) || (!node->GetRight()))
        {
            Node *temp = node->GetLeft() ? node->GetLeft() : node->GetRight();

            if (!temp)
            {
                temp = node;
                node = nullptr;
            }
            else
                *node = *temp;
            free(temp);
        }
        else
        {
            Node *temp = FindMin(node->GetRight());
            node->SetKey(temp->GetKey());
            node->SetRight(RemoveR(temp->GetKey(), node->GetRight()));
        }
    }

    if (!node)
        return node;

    node->SetHeight(1 + std::max(Height(node->GetLeft()), Height(node->GetRight())));

    return Rotate(node);
}
template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::InsertR(const T &key, Node *node)
{
    if (!node)
    {
        return new Node(key, nullptr, nullptr);
    }

    if (key < node->GetKey())
    {
        node->SetLeft(InsertR(key, node->GetLeft()));
    }
    else if (key > node->GetKey())
    {
        node->SetRight(InsertR(key, node->GetRight()));
    }
    else
    {
        return node;
    }

    node->SetHeight(1 + std::max(Height(node->GetLeft()), Height(node->GetRight())));

    return Rotate(node);
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::RightRotate(Node *node)
{
    Node *left = node->GetLeft();
    node->SetLeft(left->GetRight());
    left->SetRight(node);
    node->SetHeight(std::max(Height(node->GetLeft()), Height(node->GetRight())) + 1);
    left->SetHeight(std::max(Height(left->GetLeft()), node->GetHeight()) + 1);
    return left;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::LeftRotate(Node *node)
{
    Node *right = node->GetRight();
    node->SetRight(right->GetLeft());
    right->SetLeft(node);
    node->SetHeight(std::max(Height(node->GetLeft()), Height(node->GetRight())) + 1);
    right->SetHeight(std::max(Height(right->GetRight()), node->GetHeight()) + 1);
    return right;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::FindMin(Node *node)
{
    if (!node)
        return nullptr;
    else if (!node->GetLeft())
        return node;
    else
        return FindMin(node->GetLeft());
}

template <typename T>
AVLTree<T>::AVLTree()
{
    _root = nullptr;
}

template <typename T>
AVLTree<T>::AVLTree(const AVLTree<T> &tree)
{
    _root = nullptr;
    std::vector<Node *> nodes;
    Node *current = tree._root;
    while (current)
    {
        Insert(current->GetKey());
        if (current->GetRight())
        {
            nodes.push_back(current->GetRight());
        }
        if (current->GetLeft())
        {
            current = current->GetLeft();
        }
        else if (nodes.empty())
        {
            break;
        }
        else
        {
            current = nodes.back();
            nodes.pop_back();
        }
    }
}

template <typename T>
AVLTree<T>::AVLTree(AVLTree<T> &&tree)
{
    _root = tree._root;
    tree._root = nullptr;
}

template <typename T>
AVLTree<T>::AVLTree(T *arr, int size)
{
    _root = nullptr;
    for (int i = 0; i < size; ++i)
    {
        Insert(arr[i]);
    }
}

template <typename T>
AVLTree<T>::~AVLTree<T>()
{
    while (!Empty())
    {
        Remove(_root->GetKey());
    }
}

template <typename T>
bool AVLTree<T>::Insert(const T &key)
{
    _root = InsertR(key, _root);
    return true;
}

template <typename T>
bool AVLTree<T>::Remove(const T &key)
{
    _root = RemoveR(key, _root);
    return true;
}

template <typename T>
bool AVLTree<T>::Contains(const T &key)
{
    Node *node = Find(key);
    return node != nullptr;
}

template <typename T>
bool AVLTree<T>::Empty()
{
    return !_root;
}

template <typename T>
std::vector<T> AVLTree<T>::RoundLrootR()
{
    std::vector<T> result;
    std::vector<Node *> nodes;
    Node *current = _root;
    while (current || !nodes.empty())
    {
        while (current)
        {
            nodes.push_back(current);
            current = current->GetLeft();
        }

        result.push_back(nodes.back()->GetKey());
        current = nodes.back()->GetRight();
        nodes.pop_back();
    }
    return result;
}

template <typename T>
std::vector<T> AVLTree<T>::RoundRrootL()
{
    std::vector<T> result;
    std::vector<Node *> nodes;
    Node *current = _root;
    while (current || !nodes.empty())
    {
        while (current)
        {
            nodes.push_back(current);
            current = current->GetRight();
        }

        result.push_back(nodes.back()->GetKey());
        current = nodes.back()->GetLeft();
        nodes.pop_back();
    }
    return result;
}

#endif