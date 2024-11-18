/*
 * Exercise 1-13.
 * Write a program to print a histogram of the lengths of words in its input.
 * It is easy to draw the histogram with the bars horizontal;
 * a vertical orientation is more challenging.
 */

#include <stdio.h>

#define MAX_LENGTH 10
#define IN_WORD 1
#define OUT_WORD 0

int main(void)
{
    int c, word_in_flag;
    int word_length[MAX_LENGTH + 1];
    int l;
    int i, j;
    unsigned int max_count;
    for (i = 0; i <= MAX_LENGTH; ++i)
        word_length[i] = 0;
    word_in_flag = OUT_WORD;
    while (1) {
        c = getchar();
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            if (word_in_flag == OUT_WORD) {
                l = 0;
                word_in_flag = IN_WORD;
            }
            ++l;
        } else {
            if (word_in_flag == IN_WORD) {
                if (l <= MAX_LENGTH)
                    ++word_length[l - 1];
                else
                    ++word_length[MAX_LENGTH];
                word_in_flag = OUT_WORD;
            }
            if (c == EOF)
                break;
        }
    }
//horizon
    for (i = 0; i <= MAX_LENGTH; ++i) {
        if (i != MAX_LENGTH)
            printf("     %2d | ", i + 1);
        else
            printf("    >%2d | ", MAX_LENGTH);
        for (j = 0; j < word_length[i]; ++j)
            putchar('+');
        putchar('\n');
    }
//vertical
    max_count = 0;
    for (i = 0; i <= MAX_LENGTH; ++i)
        if (word_length[i] > max_count)
            max_count = word_length[i];
    for (i = 0; i < max_count; ++i) {
        printf("  %2u | ", max_count - i);
        for (j = 0; j <= MAX_LENGTH; ++j)
            if (word_length[j] >= max_count - i)
                printf("  +");
            else
                printf("   ");
        printf("\n");
    }
    printf(" ------");
    for (i = 0; i <= MAX_LENGTH; ++i)
        printf("---");
    printf("--\n");
    printf("       ");
    for (i = 0; i < MAX_LENGTH;)
        printf(" %2u", ++i);
    printf(" >%2u", MAX_LENGTH);
    printf("\n");
    return 0;
}
/*
void updatecounts(int counts[], int len, int wordlen);
int getpeak(int counts[], int len);
void painth(int counts[], int len);
void paintv(int counts[], int len);

int main() {
  int len = 10;
  int counts[len];
  int i;
  for (i = 0; i < len; counts[i++] = 0)
    ;

  int isIn = 0;
  int wordlen = 0;
  char c;
  while ((c = getchar()) != EOF) {
    if (isIn) {
      if (isspace(c)) {
        updatecounts(counts, len, wordlen);
        isIn = 0;
        wordlen = 0;
      } else {
        wordlen++;
      }
    } else {
      if (!isspace(c)) {
        isIn = 1;
        wordlen = 1;
      }
    }
  }
  if (wordlen > 0)
    updatecounts(counts, len, wordlen);

  painth(counts, len);

  paintv(counts, len);
}

void updatecounts(int counts[], int len, int wordlen) {
  wordlen = wordlen < len ? wordlen : len;
  counts[wordlen - 1]++;
}

int getpeak(int counts[], int len) {
  int peak = 0;
  int i;
  for (i = 0; i < len; i++) {
    peak = peak > counts[i] ? peak : counts[i];
  }
  return peak;
}

void painth(int counts[], int len) {
  printf("\nHorizontal histogram:\n\n");
  int peak = getpeak(counts, len);

  int i;
  for (i = 0; i < len; i++) {
    int barlen = counts[i] * 20 / peak + 1;
    char bar[barlen];
    int j;
    for (j = 0; j < barlen - 1; j++) {
      bar[j] = '+';
    }
    bar[j] = '\0';

    char *format = "  %2d: %s %d\n";
    if (i == len - 1) {
      format = ">=%2d: %s %d\n";
    }
    printf(format, i + 1, bar, counts[i]);
  }
}

void paintv(int counts[], int len) {
  printf("\nVertical histogram:\n\n");
  int peak = getpeak(counts, len);
  int i, j, h = 20;

  int bars[len];
  for (i = 0; i < len; i++) {
    bars[i] = counts[i] * h / peak;
  }

  for (i = 0; i <= h; i++) {
    for (j = 0; j < len; j++) {
      if (h - i == bars[j]) {
        printf("%-5d", counts[j]);
      } else if (h - i < bars[j]) {
        printf("%-5c", '+');
      } else {
        printf("%-5c", ' ');
      }
    }
    printf("\n");
  }

  for (i = 0; i < len; i++) {
    printf("=====");
  }
  printf("\n");

  for (i = 0; i < len; i++) {
    char *format = "%-5d";
    if (i == len - 1) {
      format = ">=%-5d";
    }
    printf(format, i + 1);
  }
  printf("\n");
}
*/
