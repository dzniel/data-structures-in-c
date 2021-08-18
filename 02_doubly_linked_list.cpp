#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *prev, *next;
} *head, *tail;

Node *createNode(int value) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->value = value;
  temp->next = temp->prev = NULL;
  return temp;
}

void pushHead(int value) {
  Node *temp = createNode(value);
  if(!head) {
    head = tail = temp;
  } else {
    temp->next = head;
    head->prev = temp;
    head = temp;
  }
}

void pushTail(int value) {
  Node *temp = createNode(value);
  if(!head) {
    head = tail = temp;
  } else {
    tail->next = temp;
    temp->prev = tail;
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
    while(value > temp->value) {
      temp = temp->next;
    }
    temp->prev->next = newNode;
    newNode->prev = temp->prev;
    newNode->next = temp;
    temp->prev = newNode;
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
    head->next = head->next->prev = NULL;
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
      Node *temp = tail->prev;
      tail->prev = tail->prev->next = NULL;
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
    while(value != temp->value) {
      temp = temp->next;
    }
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp->prev = temp->next = NULL;
    free(temp);
  }
}

void view() {
  if(!head) {
    return;
  } else {
    Node *temp = head;
    while(temp) {
      printf("%d <-> ", temp->value);
      temp = temp->next;
    }
    puts("NULL");
  }
}

int main() {
  int n = 5;
  int toPush[] = {3, 2, 5, 4, 6};
  for(int i = 0; i < n; i++) {
    pushMid(toPush[i]);
  }

  popMid(4);

  view();
  return 0;
}
