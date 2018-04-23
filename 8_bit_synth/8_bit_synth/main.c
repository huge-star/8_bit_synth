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

int main()
{
    char exp[50];
    printf("Please enter the exp >> ");
    scanf("%s", exp);
    generate("shit.wav", 1, exp);
    return 0;
}

