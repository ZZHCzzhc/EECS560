
#include <iostream>
#include <fstream>
using namespace std;
template <typename Comparable>
class myBinarySearchTree
{
public:
    myBinarySearchTree()
    {
        root = nullptr;
    }
    myBinarySearchTree(const myBinarySearchTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    myBinarySearchTree(myBinarySearchTree &&rhs)
    {
        root = move(rhs.root);
    }

    ~myBinarySearchTree()
    {
        makeEmpty();
    }

    const Comparable &findMin() const
    {
        return findMin(root)->element;
    }

    const Comparable &findMax() const
    {
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    void printTree(ostream &out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << endl;
        else
            printTree(root, out);
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    void insert(Comparable &&x)
    {
        insert(x, root);
    }

    void remove(const Comparable &x)
    {
        remove(x, root);
    }

    myBinarySearchTree &operator=(const myBinarySearchTree &rhs)
    {
        if (this != rhs)
        {
            makeEmpty(root); // i think should make it empty before clone, or it will
            root = clone(rhs.root);
        }
        return this;
    }

    myBinarySearchTree &operator=(myBinarySearchTree &&rhs)
    {
            swap(root, rhs.root);
            return this;
    }

    void printTreeInorder(ostream &out = cout)
    {
        if (!isEmpty())
            printTreeInorder(root, out);
    }

    void printTreePreorder(ostream &out = cout)
    {
        if (!isEmpty())
            printTreePreorder(root, out);
    }

    void printTreePostorder(ostream &out = cout)
    {
        if (!isEmpty())
            printTreePostorder(root, out);
    }

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}
        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{move(theElement)}, left{lt}, right{rt} {}
    };

    BinaryNode *root;

    void insert(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ; // Duplicate; do nothing
    }

    void insert(Comparable &&x, BinaryNode *&t)
    {
        if (t == nullptr)
            t = new BinaryNode{move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(move(x), t->left);
        else if (t->element < x)
            insert(move(x), t->right);
        else
            ; // Duplicate; do nothing
    }

    void remove(const Comparable &x, BinaryNode *&t)
    {
        if (t == nullptr)
            return; // Item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode *findMin(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }

    void makeEmpty(BinaryNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode *t, ostream &out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << endl;
            printTree(t->right, out);
        }
    }

    BinaryNode *clone(BinaryNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

    void printTreeInorder(BinaryNode *t, ostream &out) const
    {
        if (t != nullptr)
        {
            printTreeInorder(t->left, out);
            out << t->element << endl;
            printTreeInorder(t->right, out);
        }
    }

    void printTreePreorder(BinaryNode *t, ostream &out) const
    {
        if (t != nullptr)
        {
            out << t->element << endl;
            printTreePreorder(t->left, out);
            printTreePreorder(t->right, out);
        }
    }

    void printTreePostorder(BinaryNode *t, ostream &out) const
    {
        if (t != nullptr)
        {
            printTreePostorder(t->left, out);
            printTreePostorder(t->right, out);
            out << t->element << endl;
        }
    }
};
