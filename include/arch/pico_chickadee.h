#ifndef PICO_SUPPORT_CHICKADEE
#define PICO_SUPPORT_CHICKADEE


void* _kalloc(int sz);
void _kfree(void *x);
unsigned long long ticks;

#define pico_free(x) _kfree(x)

static inline void* pico_zalloc(int sz) {
  void* res = _kalloc(sz);
  memset(res, 0, sz);
  return res;
}

static inline unsigned long PICO_TIME()
{
    return (unsigned long) (ticks / 100);
}

static inline unsigned long PICO_TIME_MS()
{
    return (unsigned long) (ticks * 10);
}

static inline void PICO_IDLE()
{
    unsigned long long now = ticks;
    while(now == ticks);
}

#endif
