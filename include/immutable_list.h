#pragma once
#include <stddef.h>
#include "dynamic_list.h"


struct ImmutableList {
  void *data;

  size_t item_size;
  size_t size;

  const void *(*at)(const struct ImmutableList *self, const size_t i);
  void (*free)(struct ImmutableList *self);

  struct DynamicList *(*to_dynamic)(const struct ImmutableList *self);
};

struct ImmutableList *NewImmutableList(void *data, const size_t item_size, const size_t size);
