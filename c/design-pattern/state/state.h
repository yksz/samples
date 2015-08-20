#ifndef STATE_H
#define STATE_H

typedef struct state State;
struct state
{
    const State* (*play)(void);
    const State* (*pause)(void);
    const State* (*stop)(void);
};

extern const State idle;
extern const State play;
extern const State pause;

#endif /* STATE_H */
