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

enum _STUDMENU_ENUM
{
    STUDMENU_OVERVIEW = 1,
    MENU_ADD,
    MENU_LIST,
    MENU_DELETE,
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
            printf("%d\n\n", ulChoice);
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
        sscanf(cChoiceBuffer, "%d", &ulChoice);

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
            printf("%d .%s\n", stMenuItemPass[ulIndex].ulIndex,
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
            printf("Total Record Count = %d\n", ulActiveCount);
            printf("Average Mark = %.02d\n",ulAverageMark);
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
    char LabelBuff[LABEL_MAX];

    memset(&pstInfo, 0, sizeof(student));
    menuGetStudentName(pstInfo.ucStudentName);
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
    char *cShowLabel
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
static bool menuListStudent(void)
    {

    }
static bool menuDeleteStudent(void)
    {

    }