#ifndef AVL_H
#define AVL_H

#include <vector>
#include <string>

template <class T>
class AVL
{
private:
    class Node
    {
    public:
        Node* left;
        Node* right;
        T element;
        int height;

        Node(T element) {
            this->element = element;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 0;
        }
        ~Node() {};
    };
    Node* root;
    void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);


public:
    AVL() {
        this->root = nullptr;
    }
    ~AVL() {
        deleteTree(this->root);
    }

    void insert(T element) {
        this->root = insertHelper(this->root, element);
    }
    Node* insertHelper(Node* node, T element) {
        if (node == nullptr)
        {
            Node* newNode = new Node(element);
            return newNode;
        }

        if (element < node->element) {
            node->left = insertHelper(node->left, element);
        }
        else if (element > node->element) {
            node->right = insertHelper(node->right, element);
        }

        return balanceNode(node);
    }

    Node* removeHelper(Node* node, T element) {
        if (node == nullptr){
            return nullptr;
        }

        if (element < node->element) {
            node->left = removeHelper(node->left, element);
        }
        else if (element > node->element) {
            node->right = removeHelper(node->right, element);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = nullptr;
                if (node->left != nullptr) {
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                Node* child = findMax(node->left);
                node->element = child->element;
                node->left = removeHelper(node->left, child->element);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalance(node);

        if (balanceFactor > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balanceFactor > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balanceFactor < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balanceFactor < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    void remove(T element) {
        this->root = removeHelper(this->root, element);
    }
    
    int getHeight(Node* node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }
    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }
    void updateHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if (leftHeight > rightHeight) {
            node->height = leftHeight + 1;
        }
        else {
            node->height = rightHeight + 1;
        }
    }
    Node* rotateLeft(Node* node) {
        Node* pivot = node->right;
        node->right = pivot->left;
        pivot->left = node;
        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }
    Node* rotateRight(Node* node) {
        Node* pivot = node->left;
        node->left = pivot->right;
        pivot->right = node;
        updateHeight(node);
        updateHeight(pivot);
        return pivot;
    }
    Node* balanceNode(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        updateHeight(node);
        int balanceFactor = getBalance(node);

        if (balanceFactor > 1)
        {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balanceFactor < -1)
        {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }


    std::vector<T> inOrderWalk() {
        std::vector<T> result;
        inOrderWalkHelper(this->root, result);
        return result;
    }
    void inOrderWalkHelper(Node* current, std::vector<T>& result) {
        if (current == nullptr) {
            return;
        }
        inOrderWalkHelper(current->left, result);
        result.push_back(current->element);
        inOrderWalkHelper(current->right, result);
    }

    std::vector<T> preOrderWalk() {
        std::vector<T> result;
        preOrderWalkHelper(this->root, result);
        return result;
    }

    void preOrderWalkHelper(Node* current, std::vector<T>& result) {
        if (current == nullptr) {
            return;
        }
        result.push_back(current->element);
        preOrderWalkHelper(current->left, result);
        preOrderWalkHelper(current->right, result);
    }


    std::vector<T> postOrderWalk() {
        std::vector<T> result;
        postOrderWalkHelper(this->root, result);
        return result;
    }

    void postOrderWalkHelper(Node* current, std::vector<T>& result) {
        if (current == nullptr) {
            return;
        }
        postOrderWalkHelper(current->left, result);
        postOrderWalkHelper(current->right, result);
        result.push_back(current->element);
    }
    void deleteTree(Node* node) {
        if (node != nullptr){
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    
   
    bool find(T element) {
        Node* current = this->root;

        while (current != nullptr) {
            if (current->element == element) {
                return true;
            }
            if (current->element > element) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return false;
    }
    
    int getTreeHeight() {
        if (this->root == nullptr) {
            return -1;
        }
            
        return getHeight(this->root);
    }

    T getMin() {
        Node* minNode = findMin(this->root);
        return minNode->element;
    }

    Node* findMin(Node* node)
    {   
        if (node == nullptr) {
            return nullptr;
        }
        else {
            Node* minNode = node;
            while (minNode->left != nullptr) {
                minNode = minNode->left;
            }
            return minNode;
        }
    }
    
    T getMax() {
        Node* maxNode = findMax(this->root);
        return maxNode->element;
    }

    Node* findMax(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        else {
            Node* maxNode = node;
            while (maxNode->right != nullptr) {
                maxNode = maxNode->right;
            }
            return maxNode;
        }
        
    }
    
    std::string ToGraphviz();
};



















template <class T>
std::string AVL<T>::ToGraphviz()
{
    std::string toReturn = "";
    if (root)
    {
        std::string listOfNodes;
        std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
        toReturn += std::string("digraph {\n");
        size_t id = 0;
        ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
        toReturn += listOfNodes;
        toReturn += listOfConnections;
        toReturn += std::string("}");
    }
    return toReturn;
}

template <class T>
void AVL<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID)
{
    size_t myID = uniqueID;
    listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
    if (toWorkWith->left)
    {
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
        ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->left, ++uniqueID);
    }
    else
    {
        listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
    }

    if (toWorkWith->right)
    {
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
        ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->right, ++uniqueID);
    }
    else
    {
        listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
        listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
    }
}

#endif // AVL_H