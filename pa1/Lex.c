// -----------------------------------------------------------------------------
//  Nayeel Imtiaz, naimtiaz
//  2022 Spring CSE101 PA1
//  Lex.c
//  This file performs an indirect insertion sort on a list
//  of strings using the List ADT.
// -----------------------------------------------------------------------------

#include "List.h"
#include <string.h>

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int line_count;
   FILE *in, *out;
   char line[MAX_LEN];

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   // read each line of input file, then count and print tokens
   line_count = 0;
    while( fgets(line, MAX_LEN, in) != NULL)  {
      line_count++;
   }


   //printf("This program has %i lines.\n", line_count);
   char **words = (char **) calloc(line_count, sizeof(char *));
    fseek(in, 0, SEEK_SET);

    for (int i = 0; i < line_count; i++) {
        fgets(line, MAX_LEN, in);
        line[strlen(line)-1] = '\0';
        *(words + i) = malloc(strlen(line)+1);
        strcpy(words[i], line);
    }

//   char **words = NULL;
// 	unsigned long long size_out = 0;
// 	unsigned long long cap = 16;

// 	words = (char **) realloc(out, cap * sizeof(char *));

// 	while (fgets(line, MAX_LEN, in)) {
// 		line[MAX_LEN-1] = '\0';
// 		*(out+size_out) = strdup(my_buf);
// 		line_count += 1;
// 		if (size_out >= cap) {
// 			cap *= 2;
// 			out = (char **) realloc(out, cap * sizeof(char *));
// 		}

// 	}

// 	fclose(infile);		 
// 	*num_words = size_out;

//   return out;

    // for (i = 0; i < line_count; i++) {
    //     append(sol, i);
    // }

    /* for i in range(line_count):
            if i = 0:
                append(sol, current word)
                continue
            
            set cursor to front
            bool reach_null = true
            while cursor != null:
                if cursor >= current word:
                    insert_before(sol, current word)
                    reach_null = false
                    break
                cursor_next;
            if reach_null:
                append(sol, current_word)
            

    */

    List sol = newList();

    for (int i = 0; i < line_count; i++) {
        if (i == 0) {
            append(sol, i);
            continue;
        }

        moveFront(sol);
        bool reach_null = true;
        char *current_word = words[i];
        while (index(sol) != -1) {
            if (strncmp(words[get(sol)], current_word, MAX_LEN) >= 0) {
                insertBefore(sol, i);
                reach_null = false;
                break;
            }
            moveNext(sol);
        }

        if (reach_null) {
            append(sol, i);
        }
    }

    // NEW ALGORITHM
    //     List sol = newList();

    // for (int i = 0; i < line_count; i++) {
    //     if (i == 0) {
    //         append(sol, i);
    //         continue;
    //     }

    //     moveBack(sol);
    //     bool reach_null = true;
    //     char *current_word = words[i];
    //     while (index(sol) != -1) {
    //         if (strncmp(words[get(sol)], current_word, MAX_LEN) <= 0) {
    //             insertAfter(sol, i);
    //             reach_null = false;
    //             break;
    //         }
    //         movePrev(sol);
    //     }

    //     if (reach_null) {
    //         prepend(sol, i);
    //     }
    // }

    // //Print strings in `words` array
    // // for (int i = 0; i < line_count; i++) {
    // //     printf("%s\n", words[i]);
    // // } 

    // Printed sorted list of words
    if (length(sol) > 0) {
        moveFront(sol);
        while (index(sol) != -1) {
            fprintf(out, "%s\n", words[get(sol)]);
            moveNext(sol);
        }
    }

    // Free list
    freeList(&sol);

    // Free array of strings
    for (int i = 0; i < line_count; i++) {
        free(words[i]);
        words[i] = NULL;
    }

    free(words);
    words = NULL;

//    while( fscanf(in, "%s", line) == 1 ) {
//        printf("%s - %li\n", line, strlen(line));
//    }
   // close files 
   fclose(in);
   fclose(out);

   return(0);
}

// Check Lex.c