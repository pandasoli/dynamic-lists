#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "dynamic_list.h"
#include "immutable_list.h"


const void *ImmutableList_at(const struct ImmutableList *self, const size_t i) {
  return self->data + (i * self->item_size);
}

void ImmutableList_free(struct ImmutableList *self) {
  free(self);
}

struct DynamicList *ImmutableList_to_dynamic(const struct ImmutableList *self) {
  struct DynamicList *res = NewDynamicList(self->item_size, self->size);

  res->data = self->data;
  res->size = self->size;

  return res;
}


struct ImmutableList *NewImmutableList(void *data, const size_t item_size, const size_t size) {
  struct ImmutableList *res = malloc(sizeof(struct ImmutableList));

  res->data = data;

  res->item_size = item_size;
  res->size = size;

  res->at = &ImmutableList_at;
  res->free = &ImmutableList_free,
  res->to_dynamic = &ImmutableList_to_dynamic;

  return res;
}
