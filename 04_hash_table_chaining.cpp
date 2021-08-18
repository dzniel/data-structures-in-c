#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_ELEMENT = 10;

struct Node {
  char name[255];
  Node *next;
} *head[MAX_ELEMENT], *tail[MAX_ELEMENT];

Node *createNode(const char *name) {
  Node *temp = (Node *)malloc(sizeof(Node));
  strcpy(temp->name, name);
  temp->next = NULL;
  return temp;
}

unsigned long djb2(const char *name) {
  unsigned long hash = 5381;
  int c;
  while((c = *name++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash % MAX_ELEMENT;
}

void insert(const char *name) {
  Node *temp = createNode(name);
  int idx = djb2(name);
  if(!head[idx]) {
    head[idx] = tail[idx] = temp;
  } else {
    tail[idx]->next = temp;
    tail[idx] = temp;
  }
}

void traverse(int i) {
  Node *temp = head[i];
  while(temp) {
    printf("%s -> ", temp->name);
    temp = temp->next;
  }
}

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("Index %d: ", i);
    if(head[i]) {
      traverse(i);
    }
    puts("NULL");
  }
}

int main() {
  insert("s1mple");
  insert("electronic");
  insert("Perfecto");
  insert("Boombl4");
  insert("flamie");
  insert("b1t");
  insert("B1ad3");
  view();
  return 0;
}
