#ifndef BST_H
#define BST_H

#include <vector>
#include <string>

template <class T>
class BST
{
private:
	class Node
	{
	public:
		T element;
		Node *left;
		Node *right;
		Node(T element) {
			this->element = element;
			this->left = nullptr;
			this->right = nullptr;
		}
		~Node(){
			
		}
	};
	Node* root;
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
public:
	std::string ToGraphviz();
	BST() {
		this->root = nullptr;
	}
	~BST() {
		deleteTree(this->root);
	}

	void deleteTree(Node* node) {
		if (node != nullptr) {
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
		
	}

	void insert(T element) {

		if (this->root == nullptr) {
			this->root = new Node(element);
		}
		else {
			Node* current = this->root;
			Node* parent = nullptr;

			while (current != nullptr) {
				parent = current;
				if (current->element == element) {
					return;
				}
				if (element < current->element) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}

			if (element < parent->element) {
				parent->left = new Node(element);
			}
			else {
				parent->right = new Node(element);
			}	
		}
	}
	void remove(T element) {
		Node* current = this->root;
		Node* parent = nullptr;

		while (current != nullptr && current->element != element) {
			parent = current;

			if (current->element > element) {
				if (current->left != nullptr) {
					current = current->left;
				}
			}
			else {
				if (current->right != nullptr) {
					current = current->right;
				}
			}
		}

		if (current != nullptr && current->left == nullptr && current->right == nullptr) {
			if (current != this->root) {
				if (parent->left == current) {
					parent->left = nullptr;
				}
				else {
					parent->right = nullptr;
				}
			}
			else {
				this->root = nullptr;
			}

			delete current;
			current = nullptr;
		}
		else if (current != nullptr && current->left == nullptr && current->right != nullptr) {
			if (current != this->root) {
				if (current->element > parent->element) {
					parent->right = current->right;
				}
				else {
					parent->left = current->right;
				}
			}
			else {
				this->root = current->right;
			}
			delete current;
			current = nullptr;
		}
		else if (current != nullptr && current->left != nullptr && current->right == nullptr) {
			if (current != this->root) {
				if (current->element < parent->element) {
					parent->left = current->left;
				}
				else {
					parent->right = current->left;
				}
			}
			else {
				this->root = current->left;
			}
			delete current;
			current = nullptr;
		}
		else if (current != nullptr && current->left != nullptr && current->right != nullptr) {
			Node* currenttochange = current->left;
			Node* parenttochange = current;
			while (currenttochange->right != nullptr) {
				parenttochange = currenttochange;
				currenttochange = currenttochange->right;
			}
			if (parenttochange != current) {
				parenttochange->right = nullptr;

				if (currenttochange->left != nullptr) {
					parenttochange->right = currenttochange->left;
				}
				else {
					currenttochange->left = current->left;
				}
			}
			if (current != this->root) {
				if (currenttochange->element > parenttochange->element) {
					parenttochange->right = currenttochange;
				}
				else {
					parenttochange->left = currenttochange;
				}
			}
			else {
				this->root = currenttochange;
			}
			currenttochange->right = current->right;
			delete current;
			current = nullptr;
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

	std::vector<T> inOrderWalk() {
		std::vector<T> result;
		inOrderWalkHelper(root, result);
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
		preOrderWalkHelper(root, result);
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
		postOrderWalkHelper(root, result);
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


	int getTreeHeight() {
		return getTreeHeightHelper(this->root);
	}
	int getTreeHeightHelper(Node* current) {
		if (current == nullptr) {
			return -1;
		}
		else {
			int leftHeight = getTreeHeightHelper(current->left);
			int rightHeight = getTreeHeightHelper(current->right);
			return std::max(leftHeight, rightHeight) + 1;
		}
	}
	T getMin() {
		if (this->root == nullptr) {
			return this->root->element;
		}
		else {
			Node* minNode = this->root;
			while (minNode->left != nullptr) {
				minNode = minNode->left;
			}
			return minNode->element;
		}
	}

	T getMax() {
		if (this->root == nullptr) {
			return this->root->element;
		}
		else {
			Node* maxNode = this->root;
			while (maxNode->right != nullptr) {
				maxNode = maxNode->right;
			}
			return maxNode->element;
		}  
	}
};

template <class T>
std::string BST<T>::ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if(this->root) // root is a pointer to the root node of the tree
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
void BST<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if(toWorkWith->left)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->left, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
			
	if(toWorkWith->right)
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
#endif //BST_H
