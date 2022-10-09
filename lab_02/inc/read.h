#ifndef __READ_H__
#define __READ_H__

#include "info.h"
#include "errors.h"

int read_num_of_records(FILE *f, int *size, int max_size);
int read_word(FILE *f, int max_len, char word[]);
int read_prices(FILE *f, int *min_price, int *max_price);
int fill_info_child(FILE *f, child_t *child);
int fill_info_adult(FILE *f, adult_t *adult);
int fill_info_music(FILE *f, music_t *music);
int fill_theatre_repertoire(FILE *f, theatres_t *theatre);
int read_type_of_performance(FILE *f, char str_type_of_performance[], type_of_performance_t *type_of_performance);
int read_option(int *option);

#endif // __READ_H__