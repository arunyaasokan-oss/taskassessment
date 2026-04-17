/* student.h - supporting function for students */

#ifndef __INCmenuh
#define __INCmenuh

#include <stdint.h>
#include <stdbool.h>

/* defines */
#define MENU_ITEMS          4U
#define MENU_ITEM_LEN       50U
#define MENU_START_INDEX    0U
#define MENU_END_INDEX      4U

/* typedef */
typedef bool (*pvMenuOperationHandler)(void);
typedef struct 
{
    uint32_t ulIndex;
    char cMenuLabel[MENU_ITEM_LEN];
    pvMenuOperationHandler pMenuOperation;
}STUDENT_MENU;

/* function declaration */
extern bool menuMain(void);
#endif                                                         /*__INCmenuh*/
