#include <stdio.h>

char *labels[] = {"Label1 ","Label2 ","Label3 ","Label4 ","Label5 ","Label6 ","Label7 ","Label8 "};
char  pswd[]  = {
//                 0   1   2   3   4   5   6   7   8   9   a   b   c   d   e   f
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x1e\x00\x00\x00\x00\x00\x00\x00" //Password1
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x1f\x00\x00\x00\x00\x00\x00\x00" //Password2
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x20\x00\x00\x00\x00\x00\x00\x00" //Password3
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x21\x00\x00\x00\x00\x00\x00\x00" //Password4
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x22\x00\x00\x00\x00\x00\x00\x00" //Password5
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x23\x00\x00\x00\x00\x00\x00\x00" //Password6
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x24\x00\x00\x00\x00\x00\x00\x00" //Password7
                 "\x13\x04\x16\x16\x1a\x12\x15\x07\x25\x00\x00\x00\x00\x00\x00\x00" //Password8
                };
char  ctrl[]  = {
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                 "\x02\x00\x02\x00\x02\x00\x02\x00\x02\x00\x00\x00\x00\x00\x00\x00"
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                 "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                };
int main()
{
 int i;
 for (i=0;i<64;i++) printf("%c",*(*labels+i));
 for (i=0;i<0x80;i++) printf("%c",pswd[i]|ctrl[i]<<6);
}