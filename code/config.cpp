#include "config.h"

int getSunNum(int pltId){
    switch(pltId)
    {
    case 0:
        return 50;
    case 1:
        return 100;
    case 2:
        return 150;
    case 3:
        return 200;
    case 4:
        return 50;
    case 5:
        return 300;
    case 6:
        return 50;
    }
    return 0;
}
