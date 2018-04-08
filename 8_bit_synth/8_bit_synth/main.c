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
    for (t = 1; t < 441000; t++) {
        sub = subs("t|t*2|(t/1000)%3", "t", num2chars(t));
        printf("%d\n", cal(sub) % 256);
    }
    return 0;
}
