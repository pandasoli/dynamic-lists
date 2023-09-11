#include <stdio.h>
#include "../dynamic_list.h"
#include "../immutable_list.h"


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
    dlist->free(dlist);
  }

  printf("From immutable list\n");
  for (int i = 0; i < list->size; i++) {
    const Person *item = list->at(list, i);
    if (res == -1) return 1;

    printf("%s\n", item->name);
  }

  struct DynamicList *dlist = list->to_dynamic(list);
  list->free(list);

  printf("\nFrom dynamic list\n");
  for (int i = 0; i < dlist->size; i++) {
    Person *item = dlist->at(dlist, i);
    if (res == -1) return 1;

    printf("%s\n", item->name);
  }

  dlist->free(dlist);

  return 0;
}
