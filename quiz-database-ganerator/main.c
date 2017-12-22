#include <stdio.h>
#include "ezxml.h"
#include <windows.h>

int main()
{
    ezxml_t File, QuestionTag;
    FILE* XmlFile;
    char* XmlBuffer;
    int QuestionNumber=0;
    int OptionNumber;
    char Buffer[200];
    // introduction screen..............
    printf("\t////////////////////////////\n\n");
    printf("\tcreate new Database for Quiz\n\n");
    printf("\t////////////////////////////\n\n");
    Sleep(2000);
    system("cls");
    // create new ezxml struct..........
    File = ezxml_new("Quiz");
    // xml file to store ezxml struct........
    XmlFile = fopen("Data.xml", "w");
    while(1)
    {
        char ret;
        // create tag for new question........
        QuestionTag = ezxml_add_child(File, "Question",QuestionNumber);
        // tag for question text.........
        printf("Enter Question %d\n",QuestionNumber);
        scanf(" %[^\n]s", Buffer);    // read whole line of text....
        ezxml_set_txt(ezxml_add_child(QuestionTag, "Que", 0), Buffer);
        //get options for question.......
        for(OptionNumber=0;OptionNumber<4;OptionNumber++)
        {
            printf("/n Enter the option %d/n", OptionNumber);
            scanf(" %[^\n]s", Buffer);
            ezxml_set_txt(ezxml_add_child(QuestionTag, "Option", OptionNumber), Buffer);
        }
        printf("enter the right option\n");
        scanf(" %c", Buffer);
        Buffer[1] = '\0';
        ezxml_set_txt(ezxml_add_child(QuestionTag, "Answer", 0), Buffer);
        printf("do you want to add another question ? [y/n]");
        scanf(" %c", &ret);
        if(ret=='n' || ret=='N')
            break;
        system("cls");
        QuestionNumber++;
    }
    // store ezxml to xml file......
    XmlBuffer = ezxml_toxml(File);
    fprintf(XmlFile, XmlBuffer);
    // free memory for ezxml and xml file.......
    fclose(XmlFile);
    free(XmlBuffer);
    return 0;
}
