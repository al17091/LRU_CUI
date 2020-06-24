#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum keycode{
    Esc=-1,
    up=0,
    down,
    right,
    left,
    enter,
    quit,
    other
};

enum keycode inputKey();