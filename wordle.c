#include "wordle.h"
#include <stdio.h>
#include <stdbool.h> 
#include <string.h> 
#include "cs136-trace.h"


// see wordle.h
bool evaluate_guess(const char *secret, const char *guess, char *result) {
  int len = strlen(secret);
  if (strcmp(guess, secret) == 0) {
    for (int i = 0; i < len; i++) {
      result[i] = guess[i] - 32;
    }
    return true; 
  }
  for (int i = 0; i < len; i++) {
    if (guess[i] == secret[i])  {
      result[i] = guess[i] - 32;
      trace_char(result[i]); 
    }
    else {
      for (int j = 0; j < len; j++) {
        if (guess[i] == secret[j])  {
          result[i] = guess[i]; 
          break; 
        }
      }
      if (result[i] != guess[i])  {
        result[i] = '.';
      }
    }
  }   
  return false; 
}

// see wordle.h
int find_in_list(const char *guess, char *word_list[], int num_words) {
  for (int i = 0; i < num_words; i++) {
    if (strcmp(guess, word_list[i]) == 0) {
      return i; 
    }
    if (strcmp(guess, word_list[i]) < 0) {
      return -1; 
    }
  }
  return -1; 
}

// see wordle.h
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet) {
  char counter = 97;
  int len_w = 0; 
  for (int i = 0; i < 26; ++i) {
    alphabet[i] = counter;
    ++counter;
  }
  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < num_guesses; j++) {
      len_w = strlen(guesses[j]);
      if ((alphabet[i] >= 'A' && alphabet[i] <= 'Z') ||
            (alphabet[i] <= 'a' && alphabet[i] >= 'z')){
        break;
      }
      for (int k = 0; k < len_w; ++k) {
        if (alphabet[i] == guesses[j][k]){
          if (results[j][k] == '.') {
            alphabet[i] = '.';
          }
          else if
           ((alphabet[i] >= 'A' && alphabet[i] <= 'Z') ||
            (alphabet[i] >= 'a') && (alphabet[i] <= 'z'))
            {
            alphabet[i] -= 32;
            break;
          }
        }
      }
    }}
}

// in_word (results[], num_guesses, next_guess)
//determines if the word can be in the results
// time: O(n^3) 
bool in_word(char *results[], int num_guesses, const char *next_guess) {
  int len_next = strlen(next_guess);
  int counter = 0;
  for (int i = 0; i < num_guesses; ++i) {
    counter = strlen(results[i]);
    for (int j = 0; j < counter; ++j) {
      if ((results[i][j] >= 'a') && 
        (results[i][j] <= 'z')){
      for (int k = 0; k < len_next; ++k) {
        if (results[i][j] == next_guess[k]) {
          break;
        }
        if (k == (len_next - 1)) {
          return false;
        }
      }
    }
      if ((results[i][j] >= 'A') && 
          (results[i][j] <= 'Z')) {
        for (int k = 0; k < len_next; ++k) {
          if ((results[i][j] + 32) == next_guess[k]) {
            break;
          }
          if (k == (len_next - 1)) {
            return false;
          }
        }
      }  
    }
  }
 return true; 
} 

// see wordle.h 
bool valid_hard_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess) {
  if (in_word(results, num_guesses, next_guess) 
      == false) {
   return false;
  }
  int counter = 0;
  int len_next = strlen(next_guess);
  for (int i = 0; i < len_next; ++i) {
   for (int j = 0; j < num_guesses; ++j) {
    counter = strlen(guesses[j]); 
    if (((results[j][i] >= 'A') && 
         (results[j][i] <= 'Z')) && 
        (guesses[j][i] != next_guess[i])) {
         return false; 
    } 
    for (int k = 0; k < counter; ++k) {
     if (next_guess[i] == guesses[j][k]) {
      if (results[j][k] == '.') {
       return false; 
      }
      else if (((results[j][k] >= 'a') && 
                (results[j][k] <= 'z')) && 
               (i == k)) {
       return false; 
      }
     }
    } 
   }
  }
 return true; 
}


// see wordle.h
int find_solution(char *guesses[], char *results[], int num_guesses,
                  char *word_list[], int num_words,
                  char *solutions[], int max_solutions) {
  int counter = 0; 
  for (int i = 0; i < num_words; ++i) {
   if (counter >= max_solutions) {
    return counter; 
   }
   if (valid_hard_guess(guesses, results, 
                        num_guesses, word_list[i]) 
       == true) {
     solutions[counter] = word_list[i];
     ++counter;
   }
  }
 return counter;
}
