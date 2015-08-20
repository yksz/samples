#include "state.h"
#include <stdio.h>

static const State* idle_play(void)
{
    printf("play\n");
    return &play;
}

static const State* idle_pause(void)
{
    return &idle;
}

static const State* idle_stop(void)
{
    return &idle;
}

static const State* play_play(void)
{
    return &play;
}

static const State* play_pause(void)
{
    printf("pause\n");
    return &pause;
}

static const State* play_stop(void)
{
    printf("stop\n");
    return &idle;
}

static const State* pause_play(void)
{
    printf("resume\n");
    return &play;
}

static const State* pause_pause(void)
{
    return &pause;
}

static const State* pause_stop(void)
{
    printf("stop\n");
    return &idle;
}

const State idle = { idle_play, idle_pause, idle_stop };
const State play = { play_play, play_pause, play_stop };
const State pause = { pause_play, pause_pause, pause_stop };
