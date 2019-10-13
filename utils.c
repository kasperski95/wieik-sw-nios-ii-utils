
#define uint32_t unsigned int

/* -------------------------------------------------------------------------------------- */
/* HAL: CONSTANTS */
#define LEDS_RED_BASE 0x10000000
#define SW_SLIDERS_BASE 0x10000040

/* HAL: MACROS */
#define IOWR(base_address, offset, value) *((typeof(value) *)(base_address + offset)) = value
#define IORD(base_address, offset) *(volatile uint32_t *)((uint32_t)base_address + (uint32_t)offset)
#define IOWR_ALTERA_AVALON_PIO_IRQ_MASK

/* -------------------------------------------------------------------------------------- */
/* DECLARATIONS */
uint32_t utils__set_bit(uint32_t index, uint32_t current_value, uint32_t new_value);

/* -------------------------------------------------------------------------------------- */
/* MAIN */

int main()
{
  uint32_t x;
  while (1)
  {
    x = IORD(SW_SLIDERS_BASE, 0);
    IOWR(LEDS_RED_BASE, 0, utils__set_bit(0, x, ~x));
  }
  return 0;
}

/* -------------------------------------------------------------------------------------- */
/* DEFINITIONS */
uint32_t utils__set_bit(uint32_t index, uint32_t current_value, uint32_t new_value)
{
  return (current_value & ~(1 << index)) | (new_value & (1 << index));
}

struct interrupt_data
{
};

static void isr_pushbuttons(struct interrupt_data *data)
{
  int pb = IORD(...);

  switch (pb)
  {
    ...

        default : IOWR(..., 0, ...);
    break;
  }
  count2++;
}

int main()
{

  ... *leds = (int *)(...);

  struct interrupt_data data;

  data.leds_addr = leds;

  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(...);

  alt_ic_isr_register(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, ..., handle_sliders_interrupt, &data, 0x0);

  alt_ic_irq_enable(SW_SLIDERS_IRQ_INTERRUPT_CONTROLLER_ID, SW_SLIDERS_IRQ);
}