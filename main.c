#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "ezxml.h"
#include <windows.h>

using namespace std;
// buffer for question and options........
char *QuestionBuffer;
char *OptionBuffer[4];   // pointer to options
char Answer, Selected;
int Timer = 60;
ezxml_t File, Question, Option;

bool ReadQuestion()
{
    // load question text from Que tag..........
    QuestionBuffer = ezxml_child(Question, "Que")->txt;
    // get option child for questions.....
    Option = ezxml_child(Question, "Option");
    // load text of each options......
    for(int i=0;i<4;i++)
    {
        OptionBuffer[i] = Option->txt;
        Option = Option->next;
    }
    Answer = *(ezxml_child(Question, "Answer")->txt);
    Question = Question->next;
    return (Question != NULL);
}

void DisplayQuestion()
{
    printf("%s\n\n", QuestionBuffer);
    for(int i=0;i<4;i++)
        printf("%s\n",OptionBuffer[i]);
}

void Introduction()
{
    printf("////////////////////////////////////////////\n");
    printf("///////////   QUIZ COMPETITION /////////////\n");
    printf("////////////////////////////////////////////");
    Sleep(2000);
    system("cls");
}

int main()
{
    File = ezxml_parse_file("Data.xml");
    if(File == NULL)
    {
        printf("data file could not be found\n");
        return -1;
    }
    Introduction();
    Question = ezxml_child(File, "Question");
    ReadQuestion();
    while(1)
    {
        printf("\t\t time left: %d\n\n", Timer);
        if(Timer <= 0)
        {
            printf("Your time is Up!!\n");
            break;
        }
        DisplayQuestion();
        if(kbhit())
        {
            Selected = getch();
            Selected = *(strupr(&Selected));
            if(Selected == Answer)
            {
                printf("Selected answer is right!!\n");
                if(!ReadQuestion())
                {
                    system("cls");
                    printf("Congratulations you have answered all questions!!");
                    break;
                }
            }
            else
            {
                printf("Selected answer is wrong!!\n");
                break;
            }
        }
        Sleep(1000);
        system("cls");
        Timer--;
    }
    Sleep(1000);
    ezxml_free(File);
    return 0;
}
