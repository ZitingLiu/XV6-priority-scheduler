//ZitingLiu 002981429 GuanqiLi 001585017
#include "types.h"
#include "user.h"
#include "date.h"

int main(int argc, char **argv){
    struct rtcdate *d=malloc(sizeof(struct rtcdate));
    date(d);
    printf(1,"%d/%d/%d %d:%d:%d\n",d->month,d->day,d->year,d->hour,d->minute,d->second);

    exit();
}