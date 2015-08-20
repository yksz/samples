#include "state.h"

static const State* state = &idle;

void onPlay()
{
    state = state->play();
}

void onPause()
{
    state = state->pause();
}

void onStop()
{
    state = state->stop();
}

int main(void)
{
    onPlay();
    onPause();
    onPlay();
    onPlay();
    onStop();
    onPause();
    return 0;
}
