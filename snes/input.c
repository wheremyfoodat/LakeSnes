
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "input.h"
#include "snes.h"

Input* input_init(Snes* snes) {
  Input* input = malloc(sizeof(Input));
  input->snes = snes;
  // TODO: handle (where?)
  input->type = 1;
  input->currentState = 0;
  // TODO: handle I/O line (and latching of PPU)
  return input;
}

void input_free(Input* input) {
  free(input);
}

void input_reset(Input* input) {
  input->latchLine = false;
  input->latchedState = 0;
}

void input_latch(Input* input, bool value) {
  input->latchLine = value;
  if(input->latchLine) input->latchedState = input->currentState;
}

uint8_t input_read(Input* input) {
  if(input->latchLine) input->latchedState = input->currentState;
  uint8_t ret = input->latchedState & 1;
  input->latchedState >>= 1;
  input->latchedState |= 0x8000;
  return ret;
}
