/* 
* main.c  - student record entry
*/

/*
DESCRIPTION 
This will be responsible for calling strudent record menu.
 */

 /* includes */
 #include <stdio.h>
 #include "menustudent.h"

/* defines */

/* typedef */

/* globals */

/* locals */

/* forward declaration */

int main(void)
    {
    bool blReturnStatus = false; 

    blReturnStatus = menuMain();

    if(false == blReturnStatus)
        {
        printf("Existing from the menu.Stopped excution\n");
        }
        
    return 1;
    }