#include <nrfx.h>
#include <nrfx_uarte.h>
#include <nrf_gpio.h>
#include <stdlib.h>
#include <nrfx_glue.h>


static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
static uint8_t uarte_buffer;


//void uarte_write(uint8_t *data , uint8_t length);
void uarte_write(uint8_t* data, uint8_t length);
void uarte_handler(nrfx_uarte_event_t const *p_event, void *p_context);
void readstring(uint8_t str[]);
int strtoint(uint32_t inputstr[]);
void uarte_handler(nrfx_uarte_event_t const *p_event, void *p_context);