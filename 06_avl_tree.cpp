#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value, height, bf;
  Node *left, *right;
};

Node *createNode(int value) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->value = value;
  temp->height = 1;
  temp->bf = 0;
  temp->left = temp->right = NULL;
  return temp;
}

int max(int x, int y) {
  return (x > y) ? x : y;
}

int getHeight(Node *root) {
  return (root) ? root->height : 0;
}

int getBalanceFactor(Node *root) {
  return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

int setHeight(Node *root) {
  return max(getHeight(root->left), getHeight(root->right)) + 1;
}

Node *update(Node *root) {
  root->bf = getBalanceFactor(root);
  root->height = setHeight(root);
  return root;
}

Node *leftRotate(Node *root) {
  Node *pivot = root->right;
  Node *subtree = pivot->left;
  pivot->left = root;
  root->right = subtree;
  root = update(root);
  pivot = update(pivot);
  return pivot;
}

Node *rightRotate(Node *root) {
  Node *pivot = root->left;
  Node *subtree = pivot->right;
  pivot->right = subtree;
  root->left = subtree;
  root = update(root);
  pivot = update(pivot);
  return pivot;
}

Node *rotation(Node *root) {
  if(root->bf > 1 && root->left->bf >= 0) {
    return rightRotate(root);
  } else if(root->bf > 1 && root->left->bf < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  } else if(root->bf < -1 && root->right->bf <= 0) {
    return leftRotate(root);
  } else if(root->bf < -1 && root->right->bf > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }
  return root;
}

Node *insert(Node *root, int value) {
  if(!root) {
    return createNode(value);
  } else if(value < root->value) {
    root->left = insert(root->left, value);
  } else if(value > root->value) {
    root->right = insert(root->right, value);
  }
  return rotation(update(root));
}

int search(Node *root, int value) {
  if(!root) {
    return 0;
  } else if(value < root->value) {
    return search(root->left, value);
  } else if(value > root->value) {
    return search(root->right, value);
  }
  return 1;
}

Node *getPredecessor(Node *root) {
  Node *temp = root->left;
  while(temp->right) {
    temp = temp->right;
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
      Node *temp = (root->left) ? root->left : root->right;
      free(root);
      return temp;
    }
    Node *predecessor = getPredecessor(root);
    root->value = predecessor->value;
    root->left = remove(root->left, predecessor->value);
  }
  return rotation(update(root));
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
  Node *root = NULL;
  int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4, 1, 9, 25, 6, 30, 31};
  for(int i =  0; i < 15; i++) {
    root = insert(root, toInsert[i]);
    printf("Added %d to the tree.\n", toInsert[i]);
    inOrder(root);
    puts("");
  }
  for(int i = 0; i < 15; i++) {
    root = remove(root, toInsert[i]);
    printf("Removed %d from the tree.\n", toInsert[i]);
    inOrder(root);
    puts("");
  }
  return 0;
}
