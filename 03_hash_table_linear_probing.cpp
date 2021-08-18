#include <stdio.h>
#include <string.h>

const int MAX_ELEMENT = 5;
const int MAX_LENGTH = 255;
char hashTable[MAX_ELEMENT][MAX_LENGTH];

int hash(const char *str) {
  int sum = 0;
  for(int i = 0; str[i] != '\0'; i++) {
    sum += str[i] - '0';
  }
  return sum % MAX_ELEMENT;
}

void linearProbing(int idx, const char *str) {
  for(int i = (idx + 1) % MAX_ELEMENT; i != idx; i += 1 % MAX_ELEMENT) {
    if(!hashTable[i][0]) {
      strcpy(hashTable[i], str);
      return;
    }
  }
  puts("Table is full!");
}

void insert(const char *str) {
  int idx = hash(str);
  if(!hashTable[idx][0]) {
    strcpy(hashTable[idx], str);
  } else {
    linearProbing(idx, str);
  }
}

void view() {
  for(int i = 0; i < MAX_ELEMENT; i++) {
    printf("%d -> %s\n", i, hashTable[i]);
  }
}

int main() {
  insert("s1mple");
  insert("b1t");
  insert("Boombl4");
  insert("electronic");
  insert("flamie");
  insert("Perfecto");
  insert("B1ad3");
  view();
  return 0;
}
