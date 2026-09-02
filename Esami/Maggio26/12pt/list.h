#ifndef INC_12PT_LIST_H
#define INC_12PT_LIST_H

typedef struct list *LIST;

LIST LISTdup(LIST l);
void LISTfree(LIST l);

#endif //INC_12PT_LIST_H
