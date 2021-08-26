#ifdef _WIN32
#include <Windows.h>
#define GETCH _getch()
#define CLEAR "cls"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Timer
{
    int hrs, min, sec;
};

int main()
{
    struct Timer time;
    time.hrs = 0;
    time.min = 0;
    time.sec = 0;

    FILE* fptr = NULL;
    int i = 1;
    fptr = fopen("recordedLap.txt", "w");
    system("Color 0A");

    while (1)
    {

        if (_kbhit())
        {
            switch (GETCH)
            {
            case 'L': //lap
                // fptr = fopen("recordedLap.txt", "w");
                fprintf(fptr, "%d\t%d:%d:%d\n", i, time.hrs, time.min, time.sec);
                i++;
                break;

            case 'P': //pause
                printf("\n\t\tPress p to play: ");
                while (GETCH != 'p')
                    ;
                break;

            case 'R': //restart
                time.hrs = time.min = time.sec = 0;
                break;
            
            case 'Q': //quit
                printf("\n\nExiting");
                _sleep(1000);
                printf(".");
                _sleep(1000);
                printf("..");
                _sleep(1000);
                printf("...\n");
                fclose(fptr);

                fptr = fopen("recordedLap.txt", "r");
                printf("These are your Laps\n");
                if (fptr) {
                    char c = ' ';
                    while ((c = getc(fptr)) != EOF)
                        putchar(c);
                    fclose(fptr);
                }
                if(fptr!=0)
                    fclose(fptr);
                return EXIT_SUCCESS;
                break;
            }
        }
        else
        {
            _sleep(950);//~1000ms ~ 1sec
            time.sec++;
            time.min += time.sec / 60;
            time.sec %= 60;
            time.hrs += time.min / 60;
            time.min %= 60;
            system(CLEAR);
            printf("\n\n\n");
            printf("\t\t Hrs : Mins : Secs\n");
            if (!printf("\t\t%4d : %4d : %4d", time.hrs, time.min, time.sec))
            {
                fprintf(stderr, "O/P");
                return EXIT_FAILURE;
            }
        }
    }

    fclose(fptr);
    fptr = fopen("recordedLap.txt", "r");
    if (fptr) {
        char c = ' ';
        while ((c = getc(fptr)) != EOF)
            putchar(c);
        fclose(fptr);
    }
    fclose(fptr);
    fptr = NULL;
    return EXIT_SUCCESS;
}
