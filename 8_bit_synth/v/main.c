#include "main.h"
#include "substitude.h"
#include "calculate.h"



int main()
{
    char exp[50] = {'0'}; // to store the exp to run
    int flag = 1; // to show whether quit or not
    int sel; // to select which function to run
    while(flag) {
      system("clear");
      printf("What would you like to do?\n\n");
      printf("1. exp\n");
      printf("2. quit\n");
      printf("\n>>> "); // some instruction message
      scanf("%d", &sel);
      if (sel == 1) {
        printf("\nPlease enter the exp >> ");
        scanf("%s", exp);
        generate("sound.wav", 2, exp, (440*159)/100); // core function: generate the .wav file
      } else if (sel == 2) {
        flag = 0; // quit the program
      } else {
        printf("\nplease enter right number\n"); // error message
        sleep(2);
      }
    }

    return 0;
}
