#ifndef TOKEN_H
#define TOKEN_H

//Token
#define DECLARE_TOKEN        1
#define NAME_TOKEN           2
#define EQUAL_TOKEN          3
#define OPERATER_TOKEN       4
#define RIGHT_SMALL_BLACKETS 5
#define LEFT_SMALL_BLACKETS  6
#define RIGHT_MID_BLACKETS   7
#define LEFT_MID_BLACKETS    8
#define END_TOKEN            9

//Line Flag
#define DECLEAR              1
//Declare the varriable.
#define DESIGNATE            2
//That mean there is a rVal be defignated to lVal.
#define INIT                 3
//Init the varrirable.
#define NARRATIVE            4
//That mean the line just call function or some else.
#define OPERATE              5
//That mean the line may be some movement to operate number,
//this often appear behind the DESIGNATE rVal

#endif
