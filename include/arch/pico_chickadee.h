#ifndef PICO_SUPPORT_CHICKADEE
#define PICO_SUPPORT_CHICKADEE


extern void* _kalloc(int sz);
extern void _kfree(void *x);
extern unsigned long get_ticks();

#define pico_free(x) _kfree(x)

static inline void* pico_zalloc(int sz) {
  void* res = _kalloc(sz);
  memset(res, 0, sz);
  return res;
}

static inline unsigned long PICO_TIME()
{
    return (unsigned long) (get_ticks() / 100);
}

static inline unsigned long PICO_TIME_MS()
{
  // log_printf("called\n");
    return (unsigned long) (get_ticks() * 10);
}

static inline void PICO_IDLE()
{
    unsigned long long now = get_ticks();
    while(now == get_ticks());
}

#endif
