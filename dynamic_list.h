#pragma once
#include <stddef.h>
#include "immutable_list.h"


struct DynamicList {
  void *data;

  size_t item_size;
  size_t size;
  size_t capacity;

  int (*append)(struct DynamicList *self, const void *item);
  int (*get)(const struct DynamicList *self, const size_t i, void *res);
  int (*free)(struct DynamicList *self);
  
  struct ImmutableList *(*to_immutable)(const struct DynamicList *self);
};

struct DynamicList *NewDynamicList(const size_t item_size, const size_t init_capacity);
