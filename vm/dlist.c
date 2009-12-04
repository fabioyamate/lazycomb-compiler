#include "vm.h"
  
  dlist 
  dcons(void *element, dlist prev, dlist next)
  {
    dlist temp = (dlist)malloc(sizeof(struct dcell));
    temp -> element = element;
    temp -> prev = prev;
    temp -> next = next;
    return temp;
  }
  
  dlist
  create_and_link(void *element, dlist prev, dlist next)
  {
    dlist temp = dcons(element, prev, next);
    prev -> next = temp;
    next -> prev = temp;
    return temp;
  }

  void *
  unlink_and_free(dlist l)
  {
    void *temp = l -> element;
    l -> next -> prev = l -> prev;
    l -> prev -> next = l -> next;
    free(l);
    return temp;
  }
