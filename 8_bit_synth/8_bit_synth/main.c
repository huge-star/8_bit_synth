//
//  main.c
//  8_bit_synth
//
//  Created by 范熙来 on 2018/3/23.
//  Copyright © 2018年 范熙来. All rights reserved.
//

#include "main.h"
#include "substitude.h"
#include "calculate.h"
#include "stdio.h"



int main()
{
    FILE *fp; // to write date to the file "format.txt"
    char *name; // to store the name of the sound
    int ctr = 1;
    char exp[50] = {'0'};
    int flag = 1;
    int sel;
    fp = fopen("format.txt","w"); //判断写入是否成功
    if(NULL == fp)
    {
        printf("Can't write file!\n");
    }
    while(flag) {
      printf("What would you like to do?\n\n");
      printf("1. exp\n");
      printf("2. save\n");
      printf("3. load\n");
      printf("4. quit\n");
      printf("\n>>>");
      scanf("%d", &sel);
      if (sel == 1) {
        printf("Please enter the exp >> ");
        scanf("%s", exp);
        generate("sound.wav", 2, exp, (440*159)/100);
          printf("Please enter p/P(play the wav) or l/L(play the wav circularly) or s/S(stop operating)");
          for (int k=-1;;)
          {
              k = getch(); /*取得键值*/
              if (k == 80|| k==112) /*放音乐*/
                  PlaySound("sound.wav",NULL,SND_FILENAME);
              if (k == 76|| k==108)/*循环放音乐*/
                  PlaySound("sound.wav",NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);

              if (k == 83|| k==115) /*停止操作*/
                  break;
              else
                  printf("Please enter the right key");
          }
      }
          else if (sel == 2) {
          printf("Please enter the name of this sound: ");
          scanf("%s", name);
          fprintf(fp, "%d. %s %s", ctr, name, exp);
          ctr++;
      } else if (sel == 3) {
          rewind(fp); /*定位文件*/
          rewind(fp); /*定位文件*/
      } else if (sel == 4) {
        flag = 0;
      } else {
        printf("\nplease enter right number\n");
      }


    }
    fclose(fp);

    return 0;
}
