#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 1

typedef struct vector {
  size_t size;
  size_t capacity;
  char *datum;
} Vector;

void clear(Vector *vector);
void init(Vector *vector);
int insert(Vector *vector, char datum);
void delete(Vector *vector, char datum);
int append(Vector *vector, char datum);
int set(Vector *vector, char datum, unsigned int index);
char get(Vector *vector, int index);
void resizeIfFull(Vector *vector);
int find(Vector *vector, char datum);
void print(Vector *vector);

int main(void) {
  Vector list;
  init(&list);
  insert(&list, 'b');
  insert(&list, 'c');
  insert(&list, 'b');
  insert(&list, 'f');
  insert(&list, 'd');
  insert(&list, 'y');
  insert(&list, 'a');
  print(&list);

  delete(&list, 'a');
  delete(&list, 'c');
  print(&list);

  append(&list, 'z');
  append(&list, 'e');
  print(&list);

  set(&list, 'a', 0);
  set(&list, 'c', 2);
  set(&list, 'd', 1);
  print(&list);

  printf("index at letter f: %d\n", find(&list, 'f'));
  printf("%c\n", get(&list, 3));

  clear(&list);
  return 0;
}

void clear(Vector *vector) {
    free(vector->datum);
}

void init(Vector *vector) {
  vector->size = 0;
  vector->capacity = CAPACITY;
  vector->datum = calloc(CAPACITY, sizeof(char));
}

int insert(Vector *vector, char datum) {
  //check if list is empty
  if(vector->datum[0] == 0) {
    vector->datum[0] = datum;
    vector->size++;
    return 0;
  }

  //check if element should be first in arraylist
  if(vector->datum[0] >= datum) {
    resizeIfFull(vector);
    char tmp;
    for(size_t i = vector->size; i > 0; --i){
      vector->datum[i] = vector->datum[i-1];
    }
    vector->datum[0] = datum;
    vector->size++;
    return 0;
  }

  //check if element should go last in arraylist
  if(vector->datum[vector->size-1] <= datum) {
    resizeIfFull(vector);
    vector->datum[vector->size] = datum;
    vector->size++;
    return 0;
  }

  //check if inbetween elements
  for(size_t i = 1; i < vector->size; ++i) {
    if((vector->datum[i-1] <= datum) && (vector->datum[i] >= datum)) {
      resizeIfFull(vector);
      for(size_t j = vector->size; j > i; --j){
        vector->datum[j] = vector->datum[j-1];
      }
      vector->datum[i] = datum;
      vector->size++;
      return 0;
    }
  }

}

void delete(Vector *vector, char datum) {
  int index;
  for(size_t i = 0; i < vector->size; ++i) {
    if(vector->datum[i] == datum) {
      index = i;
      break;
    }
  }

  for(size_t i = index; i < vector->size-1; ++i) {
    vector->datum[i] = vector->datum[i+1];
  }
  //vector->datum[vector->size-1] = '\0';
  vector->size -= 1;
}

int append(Vector *vector, char datum) {
  if(vector->datum[vector->size-1] > datum && datum != 0) {
    printf("Bull sugarcubes! You can't append %c after %c in this sorted array list!\n",
  datum, vector->datum[vector->size-1]);
    return 1;
  }
  resizeIfFull(vector);
  vector->datum[vector->size++] = datum;
  return 0;
}

int set(Vector *vector, char datum, unsigned int index) {
  //check if index is greater than size
  if(vector->size <= index) {
    if(datum >= vector->datum[vector->size-1]) {
      while(vector->size <= index) {
        append(vector, 0);
      }
      vector->datum[index] = datum;
    } else {
      printf("Bull sugarcubes! You can't set %c in place of %c in this sorted array list!\n",
      datum, vector->datum[vector->size-1]);
    }
    return 0;
  } //check if index at beginning
  if(index == 0 && vector->datum[index] >= datum) {
    vector->datum[0] = datum;
    return 0;
  } //check if index is the last element
  if(index == vector->size-1 && vector->datum[index] <= datum) {
    vector->datum[vector->size-1] = datum;
    return 0;
  } //checks inbetween two elements
  if(index != 0) {
    if(vector->datum[index-1] <= datum && vector->datum[index+1] >= datum) {
      vector->datum[index] = datum;
      return 0;
    }
  }
  printf("Bull sugarcubes! You can't set %c in place of %c in this sorted array list!\n", datum, vector->datum[index]);
  return 0;
}

char get(Vector *vector, int index){
  return vector->datum[index];
}

void resizeIfFull(Vector *vector) {
  if(vector->size >= vector->capacity) {
    vector->capacity *= 2;
    vector->datum = realloc(vector->datum, sizeof(char) * vector->capacity);
  }
}

int find(Vector *vector, char datum){
  for(size_t i = 0; i < vector->size; ++i) {
    if(vector->datum[i] == datum) {
      return i;
    }
  }
  return -1;
}

void print(Vector *vector) {
  for(size_t i = 0; i < vector->size; ++i) {
    printf("%c", vector->datum[i]);
  }
  puts("");
}
