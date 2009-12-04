  #ifndef DLIST_H
  #define DLIST_H

  typedef struct dcell *dlist;

  struct dcell
  {
    void *element;
    dlist next;
    dlist prev;
  };

  extern dlist dcons(void *element, dlist prev, dlist next);
  extern dlist create_and_link(void *element, dlist prev, dlist next);
  extern void* unlink_and_free(dlist l);

  #endif
