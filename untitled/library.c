#include <stdio.h>
int main(){
    const char *s= "#include <stdio.h>int main(){const char *s=;printf(%.18s%c%.25s%c%s%c%.8s%c%.33s%c%s,s,10,s+18,34,s,34,s+43,34,s+51,34,s+84);return 0;}";
    printf("%.18s%c%.25s%c%s%c%.8s%c%.33s%c%s",s,10,s+18,34,s,34,s+43,34,s+51,34,s+84);return 0;}