///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:a
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 

// 
//  
// Name: Moaz Mahran 
// login ID:mkgmahra
///////////////////////////////////////////////////////////////////////////// 

#include "wordle.h"
#include "cs136-trace.h"
#include <stdbool.h>
#include <string.h>


bool member(char c, const char *word) {
  for (int i = 0; word[i]; ++i) {
    if (c == word[i]) {
      return true;
    }
  }
  return false;
}


// see wordle.h
bool evaluate_guess(const char *secret, const char *guess, char *result) {
  for (int i = 0; secret[i]; ++i) {
    if (secret[i] == guess[i]) {
      result[i] = secret[i] - 32;
    } else if (member(guess[i], secret)) {
      result[i] = guess[i]; 
    } else {
      result[i] = '.'; 
    }
  }
  return !strcmp(secret, guess);
}


// see wordle.h
int find_in_list(const char *guess, char *word_list[], int num_words) {
  for (int i = 0; i < num_words; ++i) {
    if (strcmp(guess, word_list[i]) == 0) {
      return i;
    }
  }
  return -1;
}


// see wordle.h
void available_letters(char *guesses[], char *results[], int num_guesses,
                       char *alphabet) {
  
  for (int i = 0; i < 26; ++i) {
    alphabet[i] = i + 'a';
  }
  for (int i = 0; i < num_guesses; ++i) {
    for(int j = 0; guesses[i][j]; ++j) {
      if (results[i][j] == '.') {
        alphabet[guesses[i][j] - 'a'] = '.';
      } else {
        alphabet[guesses[i][j] - 'a'] -= 32;
      }
      
    }
  }
}


// see wordle.h
//guesses = previous guesses
//results = ..p..A
//num_guesses = length guesses
//next_guess = curr_guess
bool valid_hard_guess(char *guesses[], char *results[], int num_guesses,
                      const char *next_guess) {
  for (int i = 0; i < num_guesses; ++i) {
    for (int j = 0; j < 5; ++j) {
      if (results[i][j] == '.' && member(guesses[i][j], next_guess)) {
        return false;
      } else if (results[i][j] >= 'A' && results[i][j] <= 'Z' &&
                 next_guess[j] != guesses[i][j]) {
        return false;
      } else if (results[i][j] >= 'a' && results[i][j] <= 'z' &&
                 next_guess[j] == guesses[i][j]) {
        return false;
      } else if (results[i][j] >= 'a' && results[i][j] <= 'z' &&
                 !member(results[i][j], next_guess)) {
        return false;
      }
    }
  }
  return true;
}


// see wordle.h
int find_solution(char *guesses[], char *results[], int num_guesses,
                  char *word_list[], int num_words,
                  char *solutions[], int max_solutions) {
  int n_solutions = 0;
  for (int i = 0; i < num_words && n_solutions < max_solutions; ++i) {
    if (valid_hard_guess(guesses, results, num_guesses, word_list[i])) {
      solutions[n_solutions] = word_list[i];
     
      ++n_solutions;
    }
  }
  return n_solutions;
}
