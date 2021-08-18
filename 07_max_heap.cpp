#include <stdio.h>

int heap[100] = {0};
int element = 0;

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void upHeap(int idx) {
  if(idx == 1) {
    return;
  } else if(heap[idx] > heap[idx / 2]) {
    swap(&heap[idx], &heap[idx / 2]);
    upHeap(idx / 2);
  }
}

void downHeap(int idx) {
  int temp = idx;
  int left = 2 * idx;
  int right = 2 * idx + 1;
  if(left <= element && heap[temp] < heap[left]) {
    temp = left;
  }
  if(right <= element && heap[temp] < heap[right]) {
    temp = right;
  }
  if(temp == idx) {
    return;
  }
  swap(&heap[idx], &heap[temp]);
  downHeap(temp);
}

void insert(int value) {
  heap[++element] = value;
  upHeap(element);
}

int extract() {
  if(!element) {
    return 0;
  } else if(element == 1) {
    int temp = heap[element];
    heap[element--] = 0;
    return temp;
  }
  int temp = heap[1];
  heap[1] = heap[element];
  heap[element--] = 0;
  downHeap(1);
  return temp;
}

void view() {
  for(int i = 1; i <= element; i++) {
    printf("%d", heap[i]);
    (i == element) ? puts("") : printf(" | ");
  }
}

int main() {
  int toInsert[] = {30, 40, 50, 35, 20, 10, 5};
  for(int i = 0; i < 7; i++) {
    insert(toInsert[i]);
  }
  view();
  for(int i = 0; i < 3; i++) {
    printf("Deleted: %d\n", extract());
    view();
  }
  return 0;
}
