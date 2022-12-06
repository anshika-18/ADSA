// Implementing Red-Black Tree in C++

#include <iostream>
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  string color;
};

typedef Node *NodePtr;

class RedBlackTree {
   private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = -1;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = "Black";
  }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }


  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == "Black") {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == "Red") {
          s->color = "Black";
          x->parent->color = "Red";
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == "Black" && s->right->color == "Black") {
          s->color = "Red";
          x = x->parent;
        } else {
          if (s->right->color == "Black") {
            s->left->color = "Black";
            s->color = "Red";
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = "Black";
          s->right->color = "Black";
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == "Red") {
          s->color = "Black";
          x->parent->color = "Red";
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == "Black" && s->right->color == "Black") {
          s->color = "Red";
          x = x->parent;
        } else {
          if (s->left->color == "Black") {
            s->right->color = "Black";
            s->color = "Red";
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = "Black";
          s->left->color = "Black";
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = "Black";
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    string y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == "Black") {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == "Red") {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == "Red") {
          u->color = "Black";
          k->parent->color = "Black";
          k->parent->parent->color = "Red";
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = "Black";
          k->parent->parent->color = "Red";
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == "Red") {
          u->color = "Black";
          k->parent->color = "Black";
          k->parent->parent->color = "Red";
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = "Black";
          k->parent->parent->color = "Red";
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = "Black";
  }

   public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = "Black";
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key) {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = "Red";

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = "Black";
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }
};

int main() {
  RedBlackTree bst;
  while(1)
  {
      cout<<"Enter 1 to insert a node"<<endl;
      cout<<"Enter 2 to delete a node"<<endl;
      cout<<"Enter 3 to print tree"<<endl;
      cout<<"Enter 0 to exit"<<endl;
      int choice;
      cout<<"Enter your choice : ";
      cin>>choice;
      switch(choice)
      {
        case 1:
            cout<<"Enter node to be inserted : ";
            int val;
            cin>>val;
            bst.insert(val);
            break;
        case 2:
            cout<<"Enter node to be deleted : ";
            cin>>val;
            bst.deleteNode(val);
            break;
        case 3:
            cout<<endl;
            cout<<endl;
            cout<<"Tree is : ";
            bst.inorder();
            cout<<endl;
            cout<<endl;
            break;
        default:
            return 0;
      }
  }
}