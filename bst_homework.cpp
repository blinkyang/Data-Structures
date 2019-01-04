// BST implementation with nodes as BRIDGES BSTElement objects. insert, add_node(), getNode(), getNode() methods provided. Students to code rotateRight() and rotateLeft() methods.
#include <string>
#include <cassert>
#include "Bridges.h"
#include "BSTElement.h"


using namespace std;
using namespace bridges;


std::string getEnvVar(string const & key);

struct pivotFamily {
    BSTElement<int, string> *pivot;
    BSTElement<int, string> *pivot_leftchild;
    BSTElement<int, string> *pivot_rightchild;
    BSTElement<int, string> *pivot_parent;
    BSTElement<int, string> *pivot_parent_leftchild;
    BSTElement<int, string> *pivot_parent_rightchild;
    BSTElement<int, string> *pivot_grandparent;
};


class BST {
  public:
	  BST();
	  int insert(int key, string value);
	  BSTElement<int,string>* getNode(int key) const;
 	  void rotateRight(BSTElement<int, string> *pivot);
	  void rotateLeft(BSTElement<int, string> *pivot);
	  void display(int i);
  private:
	  BSTElement<int, string> *root;
	  // Private methods
	  void add_node(BSTElement<int, string> *parent, BSTElement<int, string> *new_node);
 	  BSTElement<int, string>* findParentNode(BSTElement<int, string> *node) const;
	  pivotFamily findFamily(BSTElement<int, string> *pivot);


};


int main() {

	BST my_tree;

	my_tree.insert(2, "two");
	my_tree.insert(1, "one");
	my_tree.insert(3, "three");
	my_tree.insert(7, "seven");
	my_tree.insert(10, "ten");
	my_tree.insert(2, "two");
   	my_tree.insert(5, "five");
   	my_tree.insert(8, "eight");
   	my_tree.insert(6, "six");
   	my_tree.insert(4, "four");

	my_tree.display(1);

	BSTElement<int, string> *n = my_tree.getNode(5);

	if (n != nullptr) {
		cout << "Value of key is " << n->getValue() << endl;

		my_tree.rotateRight(n);
		my_tree.display(2); // Check if right rotation was correctly implemented
		n = my_tree.getNode(7);

    cout << "Value of key is " << n->getValue() << endl;
		my_tree.rotateLeft(n);
		my_tree.display(3);
	}
	else {
		cout << "Node does not exist" << endl;
	}


	return 0;
}

BST::BST() {
	root = nullptr;

}


int BST::insert(int key, string value) {
	BSTElement<int, string> *new_node = new BSTElement<int, string>(key, value);
	assert(new_node);
	new_node->setKey(key);
	new_node->setLeft(nullptr);
	new_node->setRight(nullptr);

	if (root == nullptr) {
		root = new_node;
	}
   	else
		add_node(root, new_node);

	return 1; //Success
}

BSTElement<int, string>* BST::getNode(int element) const {
   BSTElement<int, string>* current = root;
   while (current != nullptr)
   {
      if (element < current->getKey())
      {
         current = current->getLeft();
      }
      else if (element > current->getKey())
      {
         current = current->getRight();
      }
      else return current;
   }
   return nullptr;
}

void BST::rotateRight(BSTElement<int, string> *pivot)
{
  //cout << "ROTATING RIGHT" << endl;
	pivotFamily fam = findFamily(pivot);
  pivot->setRight(fam.pivot_parent);
  (fam.pivot_parent)->setLeft(fam.pivot_rightchild);
  if ((fam.pivot_grandparent)->getKey() < (fam.pivot_parent)->getKey())
  {
    fam.pivot_grandparent->setRight(pivot);
  }
  else
  {
    fam.pivot_grandparent->setLeft(pivot);
  }


}

void BST::rotateLeft(BSTElement<int, string> *pivot)
{
  //cout << "ROTATING LEFT" << endl;
  pivotFamily fam = findFamily(pivot);
  pivot->setLeft(fam.pivot_parent);
  (fam.pivot_parent)->setRight(fam.pivot_leftchild);

  if((fam.pivot_grandparent)->getKey() > (fam.pivot_parent)->getKey())
  {
    fam.pivot_grandparent->setLeft(pivot);
  }
  else
  {
    fam.pivot_grandparent->setRight(pivot);
  }

}



void BST::display(int i) {
	string hilite_color = "orange",
		   def_color = "green",
		   end_color = "red";
	Bridges::initialize(i, getEnvVar("BRIDGESUSERNAME"), getEnvVar("BRIDGESKEY"));
	Bridges::setTitle("Binary Search Tree Visualization");

	Bridges::setDataStructure(root);
	root->getVisualizer()->setColor(Color("red"));

	Bridges::visualize();
}



// Private methods

void BST::add_node(BSTElement<int, string> *parent, BSTElement<int, string> *new_node) {
   if (new_node->getKey() < parent->getKey())
   {
      if (parent->getLeft() == nullptr)
      	parent->setLeft(new_node);
      else
      	add_node(parent->getLeft(), new_node);
   }
   else if (new_node->getKey() > parent->getKey())
   {
      if (parent->getRight() == nullptr)
      	parent->setRight(new_node);
      else
      	add_node(parent->getRight(), new_node);
   }
}

BSTElement<int, string>* BST::findParentNode(BSTElement<int, string> *node) const
{

  BSTElement<int, string>* p_node = nullptr;
  BSTElement<int, string>* c_node = root;
do
{
    if (c_node->getKey() == node->getKey()) { cout << "Match on root" << endl;}
    else if (c_node->getKey() > node->getKey())
    {
      p_node = c_node;
      c_node = c_node->getLeft();

      //cout << "You are going left" << endl;
    }
    else
    {
      p_node = c_node;
      c_node = c_node->getRight();
      //cout << "You are going right" << endl;
    }
} while(c_node != node);
  //cout << "Parent is: " << p_node->getKey() << endl << endl;
  return p_node;

}

pivotFamily BST::findFamily(BSTElement<int, string> *pivot)
{
    pivotFamily pF;
    pF.pivot = pivot;
    pF.pivot_parent = findParentNode(pivot);
    pF.pivot_leftchild = pivot->getLeft();
    pF.pivot_rightchild = pivot->getRight();
    pF.pivot_parent_leftchild = (pF.pivot_parent)->getLeft(); //possibly same as pivot
    pF.pivot_parent_rightchild = (pF.pivot_parent)->getRight(); //possible same as pivot
    pF.pivot_grandparent = findParentNode(pF.pivot_parent);

    return pF;
}


string getEnvVar(string const & key) {
    char * val = getenv( key.c_str() );
    return val == NULL ? string("") : string(val);
}
