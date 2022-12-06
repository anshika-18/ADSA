// AVL tree

#include <iostream>
using namespace std;

struct Node 
{
  int key;
  Node *left;
  Node *right;
  int height;
};

int height(Node *node) 
{
  if (node == NULL)
    return 0;
  return node->height;
}

Node *newNode(int key) 
{
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

Node *rightRotate(Node *y) 
{
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),height(y->right)) +1;
  x->height = max(height(x->left),height(x->right)) +1;
  return x;
}

Node *leftRotate(Node *x) 
{
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),height(x->right)) +1;
  y->height = max(height(y->left),height(y->right)) +1;
  return y;
}

int getBalanceFactor(Node *node) 
{
  if (node == NULL)
    return 0;
  return height(node->left) -height(node->right);
}

Node *insertNode(Node *node, int key) 
{
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  node->height = 1 + max(height(node->left),height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) 
  {
    if (key < node->left->key) 
    {
      return rightRotate(node);
    } 
    else if (key > node->left->key) 
    {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) 
  {
    if (key > node->right->key) 
    {
      return leftRotate(node);
    } 
    else if (key < node->right->key) 
    {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

Node *nodeWithMimumValue(Node *node) 
{
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

Node *deleteNode(Node *root, int key) 
{
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else 
  {
    if ((root->left == NULL) ||(root->right == NULL)) 
    {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) 
      {
        temp = root;
        root = NULL;
      } 
      else
        *root = *temp;
      free(temp);
    } 
    else 
    {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key;
      root->right = deleteNode(root->right,temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) 
  {
    if (getBalanceFactor(root->left) >= 0) 
    {
      return rightRotate(root);
    } 
    else 
    {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) 
  {
    if (getBalanceFactor(root->right) <= 0) 
    {
      return leftRotate(root);
    } 
    else 
    {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

void printTree(Node *root) 
{
    if(root==NULL)
    {
        return;
    }
    printTree(root->left);
    cout << root->key<<" ";
    printTree(root->right);
}

int main() 
{
  Node *root = NULL;
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
            root=insertNode(root,val);
            break;
        case 2:
            cout<<"Enter node to be deleted : ";
            cin>>val;
            deleteNode(root,val);
            break;
        case 3:
            printTree(root);
            cout<<endl;
            break;
        default:
            return 0;
      }
  }

}