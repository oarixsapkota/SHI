/*
 *
 * Laba : Linked Arena Bump Allocator
 *
 * IMPLEMENTATION : At the end of <main>.c
 * #define LABA_IMPLEMENTATION
 * #include "laba.h"#
 *
 */

#ifndef LALB_H
#define LALB_H

#include <stddef.h>
#include <stdint.h>

typedef struct MemBlock {
  uint8_t **memory;
  struct MemBlock *next;
  size_t offset;
} MemBlock;

typedef struct {
  size_t block_count;
  size_t type_size;
  size_t capacity;
  MemBlock *head;
  MemBlock *current;
} Laba;

Laba *laba_init(size_t capacity, size_t type_size);
void laba_push(Laba *self, void *node);
void *laba_index(Laba *self, size_t index);
void laba_reset(Laba *self);
void laba_destroy(Laba *self);

#define init_laba(type, capacity) laba_init(capacity, sizeof(type))
#define push_laba(laba, type, node) laba_push(laba, (type)node)
#define index_laba(laba, index) laba_index(laba, index)
#define reset_laba(laba) laba_reset(laba);
#define destroy_laba(laba) laba_destroy(laba)

#endif // LABA_H

// #==========================#
// #  IMPLEMENTATION SECTION  #
// #==========================#

#define LABA_IMPLEMENTATION
#ifdef LABA_IMPLEMENTATION

#include <stdlib.h>

MemBlock *new_mem_block(size_t capacity, size_t type_size) {
  MemBlock *mem = (MemBlock *)malloc(sizeof(MemBlock));
  uint8_t *bytes = (uint8_t *)malloc(capacity * type_size);
  *mem = (MemBlock){&bytes, NULL, 0};
  return mem;
}

Laba *laba_init(size_t capacity, size_t type_size) {
  Laba *node = (Laba *)malloc(sizeof(Laba));
  MemBlock *mem = new_mem_block(capacity, type_size);
  *node = (Laba){0, type_size, capacity, mem, mem};
  return node;
}

void laba_push(Laba *self, void *node) {
  if (self->capacity >= self->current->offset) {
    MemBlock *mem = new_mem_block(self->capacity, self->type_size);
    self->current->next = mem;
    self->current = self->current->next;
  }
  self->current->memory[self->current->offset * self->type_size] =
      (uint8_t *)node;
  ++self->current->offset;
  return;
}

void laba_reset(Laba *self) { *self = (Laba){.current = self->head}; }

#include <stdio.h>
void *laba_index(Laba *self, size_t index) {
  reset_laba(self);

  size_t chunk_idx = (size_t)(index / (self->capacity * self->type_size));
  size_t local_index = index % (self->capacity * self->type_size);

  printf("I :\t%lu\nCHUNK :\t%lu\nOFFSET :\t%lu", index, chunk_idx,
         local_index);

  MemBlock *target_block = self->head;
  for (size_t i = 0; i < chunk_idx; ++i) {
    if (target_block == NULL)
      return NULL;
    target_block = target_block->next;
  }

  uint8_t *element_addr =
      (uint8_t *)target_block->memory + (local_index * self->type_size);
  return (void *)element_addr;
}

void laba_destroy(Laba *self) {
  reset_laba(self);
  MemBlock *current_block = NULL;
  while (self->current != NULL) {
    MemBlock *next_block = current_block->next;
    if (current_block->memory != NULL) {
      free(current_block->memory);
    }
    free(current_block);
    current_block = next_block;
  }

  free(self);
}

#endif // LABA_IMPLEMENTATION
