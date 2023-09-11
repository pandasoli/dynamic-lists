#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "dynamic_list.h"
#include "immutable_list.h"


int ImmutableList_get(const struct ImmutableList *self, const size_t i, void *res) {
  if (self == NULL || res == NULL || i >= self->size)
    return -1;

  const void *source = self->data + (i * self->item_size);
  memcpy(res, source, self->item_size);

  return 0;
}

int ImmutableList_free(struct ImmutableList *self) {
  if (self == NULL)
    return -1;

  free(self);

  return 0;
}

struct DynamicList *ImmutableList_to_dynamic(const struct ImmutableList *self) {
  struct DynamicList *res = NewDynamicList(self->item_size, self->size);

  for (int i = 0; i < self->size; i++) {
    void *item;
    self->get(self, i, item);
    res->append(res, item);
  }

  return res;
}


struct ImmutableList *NewImmutableList(const void *data, const size_t item_size, const size_t size) {
  struct ImmutableList list = {
    data,
    item_size,
    size,

    &ImmutableList_get,
    &ImmutableList_free,

    &ImmutableList_to_dynamic
  };

  const size_t listsize = sizeof(struct ImmutableList);
  struct ImmutableList *res = malloc(listsize);
  memcpy(res, &list, listsize);

  return res;
}
