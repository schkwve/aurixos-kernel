#ifndef STDDEF_H
#define STDDEF_H

/* NULL */
#define NULL (void *)0

/* offsetof() */
#define offsetof(type, designator) ((size_t)&(((type *)0)->designator))

/* Standard types definitions */
typedef int ptrdiff_t;
typedef unsigned long int size_t;


#endif /* STDDEF_H */