  #ifndef DQUEUE_H
  #define DQUEUE_H

  struct _dqueue;
  typedef struct _dqueue* dqueue;

  /* create an empty dqueue */
  extern dqueue dq_create(void);
  
  /* insert an element at the front of the dqueue */
  extern void dq_enq_front(dqueue q, void *element);

  /* insert an element at the back of the dqueue */ 
  extern void dq_enq_back(dqueue q, void *element);

  /* delete an element from the front of the dqueue and return it */
  extern void *dq_deq_front(dqueue q);

  /* returns the element at the back of the dqueue without removing it */
  extern void *dq_peek_front(dqueue q);

  /* delete an element from the back of the dqueue and return it */
  extern void *dq_deq_back(dqueue q);

  /* returns the element at the back of the dqueue without removing it */
  extern void *dq_peek_back(dqueue q);

  /* returns the element at the specified position */
 // extern void *dq_at(dqueue q, int p);

  /* return a true value if and only if the dqueue is empty */
  extern int dq_empty(dqueue q);

  #endif
