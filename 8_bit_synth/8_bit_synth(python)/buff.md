# C语言程序设计课程项目答辩

## Introduction (Problem Statement)

We are trying to build a tool to use expression to generate sounds.

By expression , I mean an arithmetic expression with a variable in it. So based on user's input, for example, let's say "t*2", we  want to generate a .wav file corresponding to it. How can this work?

A sound is some kind of oscillation. So to build a sound, first you need to regulate... //学姐这儿你写稿子吧

## Group Division
|函数|姓名|
|:-- |:--|
|void \* memorycpy(void \* dest, const void \*src, size_t count);|范熙来|
|int str_replace(char \*p_result, char\* p_source, char\* p_seach, char \*p_repstr);|范熙来|
|int getnum(unsigned long int num, int n);|孙芊荟|
|int get(unsigned long int num);|孙芊荟|
|...|...|

## Analysis
How can we turn expression into wav file?
take this as example
...(ppt animation)
so, to conclude, to do this, firstly, we need:
1. sub_string substitution: we need to replace the "t" here with string of number (eg. "200")
2. expression evaluation: we need a function to calculate the value from the string of expression (eg. f("200*3+1") => 601)
3. wav file generating: after the evaluations steps, we need to save the data we've calculate to the wave file, so that we can hear the sound

## Design
...(flowchart_overview) (check)
So, to accoplish this

## Implementation

### main: basic program frame
...(flowchart_main()) (check)

### str_replace
...(ppt animation) (check)

### expression evaluation
...(ppt animation) (check)

### wav file generating
...(flowchart_cal())
...(ppt animation)

## Testing
我来弄


## Result&Conclusion
不要了
可以演示一下
