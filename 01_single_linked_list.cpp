#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next;
} *head, *tail;

Node *createNode(int value) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->value = value;
  temp->next = NULL;
  return temp;
}

void pushHead(int value) {
  Node *temp = createNode(value);
  if(!head) {
    head = tail = temp;
  } else {
    temp->next = head;
    head = temp;
  }
}

void pushTail(int value) {
  Node *temp = createNode(value);
  if(!head) {
    head = tail = temp;
  } else {
    tail->next = temp;
    tail = temp;
  }
}

void pushMid(int value) {
  Node *newNode = createNode(value);
  if(!head) {
    head = tail = newNode;
  } else if(value < head->value) {
    pushHead(value);
  } else if(value > tail->value) {
    pushTail(value);
  } else {
    Node *temp = head;
    while(value > temp->next->value) {
      temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
  }
}

void popHead() {
  if(!head) {
    return;
  } else if(head == tail) {
    free(head);
    head = tail = NULL;
  } else {
    Node *temp = head->next;
    head->next = NULL;
    free(head);
    head = temp;
  }
}

void popTail() {
  if(!head) {
    return;
  } else if(head == tail) {
    free(tail);
    head = tail = NULL;
  } else {
    Node *temp = head;
    while(temp->next != tail) {
      temp = temp->next;
    }
    temp->next = NULL;
    free(tail);
    tail = temp;
  }
}

void popMid(int value) {
  if(!head) {
    return;
  } else if(value == head->value) {
    popHead();
  } else if(value == tail->value) {
    popTail();
  } else {
    Node *temp = head;
    while(value != temp->next->value) {
      temp = temp->next;
    }
    Node *toFree = temp->next;
    temp->next = toFree->next;
    toFree->next = NULL;
    free(toFree);
    toFree = NULL;
  }
}

void view() {
  if(!head) {
    return;
  } else {
    Node *temp = head;
    while(temp) {
      printf("%d -> ", temp->value);
      temp = temp->next;
    }
    puts("NULL");
  }
}

int main() {
  int n = 7;
  int toPush[] = {21, 34, 10, 45, 103, 54, 56};
  for(int i = 0; i < n; i++) {
    pushMid(toPush[i]);
  }

  popMid(45);
  popHead();
  popTail();

  view();
  return 0;
}
