#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int current_state = 0 ;
int head,states;
char tape [100];
char alphabet[100];
char transition[100][100];
int anothercounter;
int numberOfTransitions = 0;


int acceptance_check ()
{
    int i ;
    // abababaababababab
    // 10101010112568180
    while(tape[head] != '\0')
    {
        for (i = 0; i < numberOfTransitions; i++)
        {
            if (transition[i][0] - '0' == current_state && transition[i][2] == tape[head])
            {
                current_state = transition[i][4] - '0';
                tape[head] = transition[i][6];
                if (transition[i][8]=='r')
                    head++;
                else if (transition[i][8]=='l')
                    head--;
                if ((transition[i][8]=='l')&& head == 0) /* Handling if tape is empty */
                {
                    printf("Error Occurred ");
                    return;
                }
                if (transition[i][8]=='y')
                    return 1;
                if (transition[i][8]=='n')
                    return 0;
            }
        }
    }
}

void file_extraction ()
{
    FILE *fp;
    int count = 0;
    char ch;
    int i,j;

    fp = fopen("input.txt", "r");
    fscanf(fp,"%d ",&states);

    while ((ch = fgetc(fp)) != '\n')
        if (ch != ',')
            alphabet[count++] = ch;

    numberOfTransitions = states * (count);

    for (i = 0; i < numberOfTransitions; i++)
        fscanf(fp,"%s",&transition[i]);

    count = 0;
    ch = fgetc(fp);
    while ((ch = fgetc(fp)) != '\n')
        tape[count++] = ch;

    anothercounter = count;

    fscanf(fp,"%d",&head);
    for(i = count; i < (count+10); i++)
        tape[i] = '#';

}

int main()
{
    int result,i ;
    char filename[100] ;
    file_extraction();
    result = acceptance_check();
    result == 1 ? printf("The String Is Accepted.\n") : printf("The String Is Rejected.\n");
    printf("The Head Had Stopped At Position Number %d\n",head);
    printf("The Tape Contains %s",tape);
    return 0;
}
