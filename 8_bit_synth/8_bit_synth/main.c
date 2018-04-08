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
    unsigned long int t = 300;
    char * sub;
    sub = subs("3+4000/t-(50+6)*81", "t", num2chars(t));
    printf("%d\n", cal(sub));
    return 0;
}
