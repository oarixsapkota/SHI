#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LABA_IMPLEMENTATION
#include "laba.h"

char *s_read_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "FATAL : Failed to open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  const size_t file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *content = malloc(file_size + 1);

  const size_t bytes = fread(content, 1, file_size, file);
  if (bytes != file_size) {
    fprintf(stderr, "FATAL : Failed to read bytes form file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  content[file_size] = '\0';

  fclose(file);
  return content;
}

char *s_substr(const char *str, const size_t start, const size_t end) {
  const size_t length = end - start;
  char *substr = malloc(length + 1);
  strncpy(substr, str + start, length);
  substr[length] = '\0';
  return substr;
}

char *get_word(const char *buffer, size_t *i, size_t *col) {
  const size_t start = *i;
  while (!isspace(buffer[*i])) {
    ++*col;
    ++*i;
  }
  return s_substr(buffer, start, *i);
}

typedef struct {
  char *word;
  size_t line;
  size_t col;
} Word;

Word *new_word(const char *word, size_t line, size_t col) {
  Word *node = (Word *)malloc(sizeof(Word));
  *node = (Word){(char *)word, line, col};
  return node;
}

int main(void) {
  char *buffer = s_read_file("lorem_plus.txt");

  // START LABA
  Laba *laba = init_laba(char *, 10);

  size_t i = 0, line = 1, col = 1;
  while (buffer[i] != '\0') {
    // Handle whitespace.
    if (isspace(buffer[i])) {
      if (buffer[i] == '\n') {
        col = 1;
        ++line;
      } else {
        ++col;
      }
      ++i;
      continue;
    }
    size_t tcol = col;
    char *word = get_word(buffer, &i, &col);
    push_laba(laba, Word *, new_word(word, line, tcol));
    ++i;
  }
  push_laba(laba, Word *, NULL);

  i = 0;
  Word *word = index_laba(laba, i);
  while (word != NULL) {
    word = index_laba(laba, i);
    printf("Word : %s", word->word);
    ++i;
  }

  free(buffer);
  return 0;
}
