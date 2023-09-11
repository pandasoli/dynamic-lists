#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "dynamic_list.h"
#include "immutable_list.h"


int DynamicList_append(struct DynamicList *self, const void *item) {
  if (self == NULL || item == NULL)
    return -1;

  if (self->size >= self->capacity) {
    unsigned new_capacity = self->capacity * 2;
    void *new_data = realloc(self->data, self->item_size * new_capacity);

    if (new_data == NULL)
      return -1;

    self->data = new_data;
    self->capacity = new_capacity;
  }

  void *dest = self->data + (self->size * self->item_size);
  memcpy(dest, item, self->item_size);
  self->size++;

  return 0;
}

int DynamicList_get(const struct DynamicList *self, const size_t i, void *res) {
  if (self == NULL || res == NULL || i >= self->size)
    return -1;

  void *source = self->data + (i * self->item_size);
  memcpy(res, source, self->item_size);

  return 0;
}

int DynamicList_free(struct DynamicList *self) {
  if (self == NULL)
    return -1;

  free(self);

  return 0;
}

struct ImmutableList *DynamicList_to_immutable(const struct DynamicList *self) {
  return NewImmutableList(self->data, self->item_size, self->size);
}


struct DynamicList *NewDynamicList(const size_t item_size, const size_t init_capacity) {
  struct DynamicList *res = malloc(sizeof(struct DynamicList));
  if (res == NULL)
    return NULL;

  res->data = malloc(item_size * init_capacity);
  if (res->data == NULL)
    return NULL;

  res->item_size = item_size;
  res->size = 0;
  res->capacity = init_capacity;

  res->get = &DynamicList_get;
  res->append = &DynamicList_append;
  res->free = &DynamicList_free;
  res->to_immutable = &DynamicList_to_immutable;

  return res;
}
