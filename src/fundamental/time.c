#include "time.h"

void stopwatch (float* swatch)
{
    *swatch += GetFrameTime();
}

bool countdown (float* cdown)
{
    *cdown -= GetFrameTime();
    return (bool)(*cdown <= 0.0f);
}
