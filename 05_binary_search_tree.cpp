#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *left, *right;
};

Node *createNode(int value) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->value = value;
  temp->left = temp->right = NULL;
  return temp;
}

Node *insert(Node *root, int value) {
  if(!root) {
    return createNode(value);
  } else if(value < root->value) {
    root->left = insert(root->left, value);
  } else if(value > root->value) {
    root->right = insert(root->right, value);
  }
  return root;
}

Node *getSuccessor(Node *root) {
  Node *temp = root->right;
  while(temp && temp->right) {
    temp = temp->right;
  }
  return temp;
}

Node *getPredecessor(Node *root) {
  Node *temp = root->left;
  while(temp && temp->left) {
    temp = temp->left;
  }
  return temp;
}

Node *remove(Node *root, int value) {
  if(!root) {
    return root;
  } else if(value < root->value) {
    root->left = remove(root->left, value);
  } else if(value > root->value) {
    root->right = remove(root->right, value);
  } else {
    if(!root->left || !root->right) {
      Node *newRoot = root->left ? root->left : root->right;
      root->left = root->right = NULL;
      free(root);
      root = NULL;
      return newRoot;
    }
    Node *predecessor = getPredecessor(root);
    root->value = predecessor->value;
    root->right = remove(root->right, predecessor->value);
  }
  return root;
}

bool searchNode(Node *root, int value) {
  if(!root) {
    return false;
  } else if(value < root->value) {
    return searchNode(root->left, value);
  } else if(value > root->value) {
    return searchNode(root->right, value);
  }
  return true;
}

void preOrder(Node *root) {
  if(root) {
    printf("%d ", root->value);
    preOrder(root->left);
    preOrder(root->right);
  }
}

void inOrder(Node *root) {
  if(root) {
    inOrder(root->left);
    printf("%d ", root->value);
    inOrder(root->right);
  }
}

void postOrder(Node *root) {
  if(root) {
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->value);
  }
}

int main() {
  Node *baseRoot = NULL;
  int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4, 1, 9, 25, 6, 30, 31};
  for(int i =  0; i < 15; i++) {
    baseRoot = insert(baseRoot, toInsert[i]);
    printf("Added %d to the tree.\n", toInsert[i]);
    inOrder(baseRoot);
    puts("");
  }
  for(int i = 0; i < 15; i++) {
    baseRoot = remove(baseRoot, toInsert[i]);
    printf("Removed %d from the tree.\n", toInsert[i]);
    inOrder(baseRoot);
    puts("");
  }
  return 0;
}
