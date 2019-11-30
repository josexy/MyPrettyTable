
#ifndef PRETTYTABLE_SIGN_H
#define PRETTYTABLE_SIGN_H

// special punctuation character
enum{
    PC1=0x3002u,
    PC2=0xFF1Fu,
    PC3=0xFF01u,
    PC4=0xFF0Cu,
    PC5=0x3001u,
    PC6=0xFF1Bu,
    PC7=0xFF1Au,
    PC8=0x300Cu,
    PC9=0x300Du,
    PC10=0x2018u,
    PC11=0x2019u,
    PC12=0xFF08u,
    PC13=0xFF09u,
    PC14=0x3014u,
    PC15=0x3015u,
    PC16=0x3010u,
    PC17=0x3011u,
    PC18=0x2014u,
    PC19=0x2026u,
    PC20=0x2013u,
    PC21=0xFF0Eu,
    PC22=0x300Au,
    PC23=0x300Bu,
    PC24=0x3008u,
    PC25=0x3009u,
};
enum class Sign{
    PT_PLUS='+', 
    PT_H ='-', 
    PT_V ='|', 
    PT_DOT= '.', 
    PT_EQUAL= '=' ,
    PT_SIG_1= '@' ,
    PT_SIG_2= '#' ,
    PT_SIG_3= '$', 
    PT_SIG_4= '%', 
    PT_SIG_5= '\\', 
    PT_SIG_6='*', 
    PT_SIG_7='/'
};
#endif
