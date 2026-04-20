/* 
* menu.c  - include all the students menu add, delete, view
*/

/*
DESCRIPTION 
This will be responsible for adding students, List student, Delete Student,
Search by name - roll number and rank, Delete by name -roll number - all.
 */

 /* includes */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "menustudent.h"
#include "studentinc.h"

/* defines */
#define ROLL_NUM_LEN        5U
#define LABEL_MAX           50U
#define CHOICE_BUFFER_LEN   4U
#define CHOICE_LEN          2U
#define MARK_LEN            (3U)

/* typedef */

/* globals */

/* locals */

static bool menuStudentOverview(void);
static int32_t menuGetRollNumber(void);
static bool menuGetStudentName(char *cBuff);
static float menuGetmark(char *cShowLabel);
static bool menuAddStudent(void);
static bool menuListStudent(void);
static bool menuDeleteStudent(void);
static bool DisplayMenu(const STUDENT_MENU *stMenuItemPass);
static uint32_t GetChoiceFromUser(void);
static bool menuListSearchByName(void);
static bool menuListSortByName(void);
static bool menuListSortByRoll(void);
static bool menuDeleteByRoll(void);
static bool menuDeleteByName(void);
static bool menuDeleteAll(void);
static bool menuListSortByRank(void);
enum _STUDMENU_ENUM
{
    STUDMENU_OVERVIEW = 1,
    MENU_ADD,
    MENU_LIST,
    MENU_DELETE,   
};
enum _STUDENTLIST_ENUM
{
    STUDENTLIST_SEARCH = 1,
    STUDENTLIST_SORT_BYNAME,
    STUDENTLIST_SORT_BYROLLNO,
    STUDENTLIST_SORT_BYRANK,
};
enum _STUDENTDEL_ENUM
{
    STUDENTDEL_BYNAME = 1,
    STUDENTDEL_BYROLLNO,
    STUDENTDEL_ALL
};

const STUDENT_MENU stMenuItem[] =
    {
        {.ulIndex = STUDMENU_OVERVIEW,
         .cMenuLabel = "Student overview",
         .pMenuOperation = menuStudentOverview
        },
        {.ulIndex = MENU_ADD,
         .cMenuLabel = "Student Add",
         .pMenuOperation = menuAddStudent
        },
        {.ulIndex = MENU_LIST,
         .cMenuLabel = "Student List",
         .pMenuOperation = menuListStudent
        },
        {.ulIndex = MENU_DELETE,
         .cMenuLabel = "Student Delete",
         .pMenuOperation = menuDeleteStudent
        },
    };

const STUDENT_LIST stMenuList[] =
    {
        {.ulIndex = STUDENTLIST_SEARCH,
         .cMenuLabel = "Student Search",
         .pMenuOperation = menuListSearchByName
        },
        {.ulIndex = STUDENTLIST_SORT_BYNAME,
         .cMenuLabel = "SortByName",
         .pMenuOperation = menuListSortByName
        },
        {.ulIndex = STUDENTLIST_SORT_BYROLLNO,
         .cMenuLabel = "Sort By RollNo",
         .pMenuOperation = menuListSortByRoll
        },
        {.ulIndex = STUDENTLIST_SORT_BYRANK,
         .cMenuLabel = "Sort By Rank",
         .pMenuOperation = menuListSortByRank
        },
    };
const STUDENT_DEL stMenuDel[] =
    {
        {.ulIndex = STUDENTDEL_BYNAME,
         .cMenuLabel = "Student overview",
         .pMenuOperation = menuDeleteByName
        },
        {.ulIndex = STUDENTDEL_BYROLLNO,
         .cMenuLabel = "Student Add",
         .pMenuOperation = menuDeleteByRoll
        },
        {.ulIndex = STUDENTDEL_ALL,
         .cMenuLabel = "Student List",
         .pMenuOperation = menuDeleteAll
        },
    };
/* forward declaration */
bool menuMain(void);

/*******************************************************************************
*
* menuMain - shows the menu
*
* DESCRIPTION
* The function is used to add student details name, marks, roll numbers
* mark
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
bool menuMain(void)
    {
    uint32_t ulChoice = 0;
    while (1)
    {
        if (true == DisplayMenu(stMenuItem))
        {
            ulChoice = GetChoiceFromUser();
            printf("%u\n\n", ulChoice);
            if ((MENU_START_INDEX < ulChoice) && (MENU_END_INDEX > ulChoice))
            {
                ulChoice -=1;
                stMenuItem[ulChoice].pMenuOperation();
            }
            else
            {
                printf("Invalid choice exiting from menu...\n");
                break;
            }
        }
    }

    return true;
    }
/*******************************************************************************
*
* GetChoiceFromUser - select menu choice
*
* DESCRIPTION
* The function is used to select choice from menu
* mark
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static uint32_t GetChoiceFromUser(void)
    {
    uint32_t ulChoice = 0;
    int32_t ulChar = 0;
    char cChoiceBuffer[CHOICE_BUFFER_LEN] = {0};

    printf(" Enter your choice \n");
    memset(cChoiceBuffer, 0, CHOICE_BUFFER_LEN);

    if (NULL != fgets(cChoiceBuffer, CHOICE_LEN, stdin))
        {
        sscanf(cChoiceBuffer, "%u", &ulChoice);

        if (NULL == strchr(cChoiceBuffer, '\n') )
            {
            while (((ulChar = getchar()) != '\n') && (ulChar != EOF))
                ;
            }
        }

    return (ulChoice);
    }
/*******************************************************************************
*
* DisplayMenu - displaying menu student overview ,Add , List, Delete
*
* DESCRIPTION
* The function is used to select choice from menu
* mark
* PARAMETER : menu list 
*
* GLOBALS   : N/A
*
* RETURNS   : on succes - return true , failure - return false
*
* ERRNO     : N/A
*/
static bool DisplayMenu
    (
    const STUDENT_MENU *stMenuItemPass
    )       
    {
    uint32_t ulIndex = 0;                              
    bool blReturnValue = false;

    if (NULL != stMenuItemPass)
    {
        for (ulIndex = 0; ulIndex < MENU_ITEMS; ulIndex++)
        {
            printf("%u .%s\n", stMenuItemPass[ulIndex].ulIndex,
                   stMenuItemPass[ulIndex].cMenuLabel);
        }

        blReturnValue = true;
    }

    return blReturnValue;
}
/*******************************************************************************
*
* menuStudentOverview - Display overview of student count and average mark
*
* DESCRIPTION
* The function is used to display student count and average mark
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : on succes - return true , failure - return false
*
* ERRNO     : N/A
*/
static bool menuStudentOverview(void)
    {
    bool blReturnStatus = false;
    uint32_t ulActiveCount = 0;
    uint32_t ulAverageMark = 0;

    if(false == studentGetCount(&ulActiveCount))
        {
        printf("No student record found\n");
        }
    else
        {
            studentGetAvgMarksOfSubjects(&ulAverageMark);
            printf("Total Record Count = %u\n", ulActiveCount);
            printf("Average Mark = %u\n",ulAverageMark);
            blReturnStatus = true;
        }
    return blReturnStatus;
    }
/*******************************************************************************
*
* menuAddStudent - function for adding stude details.
*
* DESCRIPTION
* The function is used to add student details name, marks, roll numbers
* mark
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuAddStudent(void)
    {
    uint8_t ucIndex = 0;
    student pstInfo;
    bool blReturnStatus = false;
    char LabelBuff[LABEL_MAX];

    memset(&pstInfo, 0, sizeof(student));
    menuGetStudentName((const char *)pstInfo.ucStudentName);
    pstInfo.ulRollNumber = menuGetRollNumber();

    for(ucIndex = 0; ucIndex < NO_OF_SUBJECT; ucIndex++)
        {
        memset(LabelBuff, 0,sizeof(LabelBuff));
        snprintf(LabelBuff, sizeof(LabelBuff),
        (char *)"Enter mark for subject %d :", 
        ucIndex + 1);
        pstInfo.fMarkInfo[ucIndex] = menuGetmark(LabelBuff);
        }
    
    studentAdd(&pstInfo);
    blReturnStatus = true;

    return blReturnStatus;
    }
/*******************************************************************************
*
* menuGetStudentName - for getting student name
*
* DESCRIPTION
* The function is used to aget student name
* 
* PARAMETER : pointer
*
* GLOBALS   : N/A
*
* RETURNS   : On success - true On faiure - false
*
* ERRNO     : N/A
*/
bool menuGetStudentName
    (
    char *cBuff
    )
    {
    bool blReturnStatus = false;
    if(cBuff != NULL)
        {
        printf("Enter student name : \n");
        if (NULL != fgets(cBuff, MAX_STUDENT_NAME, stdin))
            {
                blReturnStatus = true;
            }
        }
        return blReturnStatus;
    }
/*******************************************************************************
*
* menuGetRollNumber - for getting student roll number
*
* DESCRIPTION
* The function is used to get roll number
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : roll number
*
* ERRNO     : N/A
*/
int32_t menuGetRollNumber(void)
    {
    char cRollBuff[ROLL_NUM_LEN] = {0};
    int32_t ulRollNumber = 0;

    printf("enter roll number : \n");
    memset(cRollBuff, 0, ROLL_NUM_LEN);

    if (NULL != fgets(cRollBuff, ROLL_NUM_LEN, stdin))
        {
        sscanf(cRollBuff, "%d", &ulRollNumber);

        if (NULL == strchr(cRollBuff, '\n') )
            {
            while (((ulRollNumber = getchar()) != '\n') 
            && (ulRollNumber != EOF));
            }
        }
        return ulRollNumber;
    }
/*******************************************************************************
*
* menuGetmark - for getting student mark
*
* DESCRIPTION
* The function is used to get student mark
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : mark will be returned
*
* ERRNO     : N/A
*/
float menuGetmark
    (
    const char *cShowLabel
    )
    {
    char cMarkBuff[MARK_LEN] = {0};   
    float fMarkInfo = 0;
    char *endptr = NULL;
    memset(cMarkBuff, 0, MARK_LEN);

    if(cShowLabel != NULL)
        {
        printf("%s",cShowLabel);
        if (NULL != fgets(cMarkBuff, MARK_LEN, stdin))
            {
            fMarkInfo = strtof(cMarkBuff, &endptr);
            if (strchr(cMarkBuff, '\n') == NULL) 
                {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                }
            }
        }
        return fMarkInfo;
    }
/*******************************************************************************
*
* menuListStudent - Show the menulist of the student
*
* DESCRIPTION
* The function is used to show the menu list of the student , search, sort by
* name, sort by roll number, sort by rank
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : mark will be returned
*
* ERRNO     : N/A
*/
static bool menuListStudent(void)
    {
    uint32_t ulChoice = 0;
    while (1)
        {
        if (true == DisplayMenu(stMenuList))
            {
            ulChoice = GetChoiceFromUser();
            printf("%u\n\n", ulChoice);
            if ((MENU_LIST_START < ulChoice) && (MENU_LIST_END > ulChoice))
                {
                ulChoice -=1;
                stMenuList[ulChoice].pMenuOperation();
                }
            else
                {
                printf("Invalid choice exiting from menu...\n");
                break;
                }
            }
        }
        return true;
    }
/*******************************************************************************
*
* menuDeleteStudent - shows the delete menu.
* DESCRIPTION
* The function used show the deleted menu - delete by name, delete by rollNo,
* delete all.
*
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuDeleteStudent(void)
    {
    uint32_t ulChoice = 0;
    while (1)
        {
        if (true == DisplayMenu(stMenuDel))
            {
            ulChoice = GetChoiceFromUser();
            printf("%u\n\n", ulChoice);
            if ((MENU_DELETE_START < ulChoice) && (MENU_DELETE_END > ulChoice))
                {
                ulChoice -=1;
                stMenuDel[ulChoice].pMenuOperation();
                }
            else
                {
                printf("Invalid choice exiting from menu...\n");
                break;
                }
            }
        }
        return true;
    }
/*******************************************************************************
*
* menuDeleteAll - delete all record.
* DESCRIPTION
* The function used delete all record stored
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuDeleteAll(void)
    {
    bool blReturnStatus = false;
    studentDeleteAll();
    blReturnStatus =  true;
    return blReturnStatus;
    }
/*******************************************************************************
*
* menuListSearchByName - search by name.
* DESCRIPTION
* The function used to search a record by name
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuListSearchByName(void)
    {
    bool blReturnStatus = false;
    char *cNameBuff[MAX_STUDENT_NAME];
    if(true == menuGetStudentName(cNameBuff))
        {
        if(false == studentSearchByName(cNameBuff))
            {
             printf("Record not found\n");
            }
        else
            {
            blReturnStatus = true;   
            }   
        }
    return blReturnStatus;
    }
/*******************************************************************************
*
* menuListSortByName - sort by Name.
* DESCRIPTION
* The function used to sort the list by name
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuListSortByName(void)
    {
    studentSortByName();
    }
/*******************************************************************************
*
* menuListSortByRoll - sort by Roll number.
* DESCRIPTION
* The function used to sort the list by roll number
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuListSortByRoll(void)
    {
    studentSortByRollNumber();  
    }
/*******************************************************************************
*
* menuListSortByRank - sort by rank.
* DESCRIPTION
* The function used to sort the list by rank
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuListSortByRank(void)
    {
    studentSortByRank();
    }
/*******************************************************************************
*
* menuDeleteByName - menu used for delete record by name.
* DESCRIPTION
* The function used to delete a student by name
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuDeleteByName(void)
    {
    bool blReturnStatus = false;
    char *cNameBuff[MAX_STUDENT_NAME];
    if(true == menuGetStudentName(cNameBuff))
        {
        if(true == studentDeleteByName(cNameBuff))
            {
            printf("record deleted \n");  
            blReturnStatus = true; 
            }
        else
            {
            printf("record not found \n");
            }
        }
        return blReturnStatus;
    }
/*******************************************************************************
*
* menuDeleteByRoll - menu used for delete record by ROLL NUMBER
* DESCRIPTION
* The function used to delete a student by ROLLNUMBER
* 
* PARAMETER : N/A
*
* GLOBALS   : N/A
*
* RETURNS   : N/A
*
* ERRNO     : N/A
*/
static bool menuDeleteByRoll(void)
    {
    int32_t ulRollNumber = 0;
    ulRollNumber = menuGetRollNumber();
        {
        if(true == studentDeleteByRollNumber(ulRollNumber))
            {
            printf("record deleted \n");
            }
        else
            {
            printf("record not found \n");
            }
        }
    }