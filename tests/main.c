#include <stdio.h>
#include "dynamic_list.h"
#include "immutable_list.h"


typedef struct {
  char name[30];
  unsigned short age;
} Person;

int main(void) {
  struct ImmutableList *list;
  int res;

  {
    const Person panda = { "Panda", 18 };
    const Person finn = { "Finn", 30 };

    struct DynamicList *dlist = NewDynamicList(sizeof(Person), 1);
    if (dlist == NULL) return 1;

    res = dlist->append(dlist, &panda);
    if (res == -1) return 1;

    res = dlist->append(dlist, &finn);
    if (res == -1) return 1;

    res = dlist->append(dlist, &panda);
    if (res == -1) return 1;

    list = dlist->to_immutable(dlist);

    res = dlist->free(dlist);
    if (res == -1) return 1;
  }

  for (int i = 0; i < list->size; i++) {
    Person item;
    res = list->get(list, i, &item);
    if (res == -1) return 1;

    printf("%s\n", item.name);
  }

  struct DynamicList *dlist = list->to_dynamic(list);

  res = list->free(list);
  if (res == -1) return 1;

  for (int i = 0; i < dlist->size; i++) {
    Person item;
    res = dlist->get(dlist, i, &item);
    if (res == -1) return 1;

    printf("%s\n", item.name);
  }

  res = dlist->free(dlist);
  if (res == -1) return 1;

  return 0;
}
