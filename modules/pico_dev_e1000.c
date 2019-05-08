#include "pico_device.h"
#include "pico_stack.h"
#include "pico_dev_e1000.h"

uint8_t mac = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};

extern int e1000_write(void* buf, int len);
extern int e1000_read(int count);

static int pico_e1000_send(struct pico_device *dev, void *buf, int len) {
  return e1000_write(buf, (uint32_t) len);
}

static int pico_e1000_poll(struct pico_device *dev, int loop_score) {
  return e1000_read(loop_score);
}

struct pico_device *pico_e1000_create() {
  struct pico_device* e1000 = PICO_ZALLOC(sizeof(struct pico_device));

  if (!e1000) return NULL;

  if(0 != pico_device_init((struct pico_device*) e1000, "e1000", mac)) {
    dbg("Ipc init failed.\n");
    return NULL;
  }

  e1000->send = pico_e1000_send;
  e1000->poll = pico_e1000_poll;

  struct pico_ip4 ipaddr, netmask;
  pico_string_to_ipv4("172.16.0.2", &ipaddr.addr);
  pico_string_to_ipv4("255.255.255.0", &netmask.addr);
  pico_ipv4_link_add(e1000, ipaddr, netmask);

  // app_tcpecho(55);

  return e1000;
}
