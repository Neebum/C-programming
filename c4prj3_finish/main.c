#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

<<<<<<< HEAD
void actScore(deck_t ** hands, size_t n_hands, int * win_arr){
  size_t bt_hd_idex = 0;
  int comp_res = 0;
  int tie_flag = 0;

  for(size_t j=1; j<n_hands; j++){
    comp_res = compare_hands(hands[bt_hd_idex],hands[j]);
    if(comp_res == -1){
      bt_hd_idex = j;
      tie_flag = 0;
    }
    if(comp_res == 0){
      tie_flag = 1;
    }
  }
  if(tie_flag){
    win_arr[n_hands]++;
  }else{
    win_arr[bt_hd_idex]++;
  }
}

void freeFutCards(future_cards_t * fc){
  for(size_t i=0; i<fc->n_decks; i++){
    free((fc->decks[i]).cards);
  }
  free(fc->decks);
  free(fc);
}

void freeAll(future_cards_t * fc, deck_t ** hands, size_t n_hands, deck_t * rem_deck, int * win_arr){
  freeFutCards(fc);
  for(size_t i=0; i<n_hands; i++){
    free_deck(hands[i]);
  }
  free(hands);
  free_deck(rem_deck);
  free(win_arr);
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if((argc==1) || (argc>3)){
    fprintf(stderr, "Wrong number of Arguments");
    return EXIT_FAILURE;
  }

  int n_trails;
  deck_t ** hands;
  deck_t * rem_cards;
  size_t n_hands = 0;
  FILE * f = NULL;
  int * win_arr = NULL;

  future_cards_t * fc = (future_cards_t *)malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;
=======
int win_hand(deck_t ** deck_array,int n_hands){
  int w[n_hands+1];
  for(int u=0;u<n_hands+1;u++) w[u]=0;  
  int v=0;
  for(int i =0;i<n_hands-1;i++){
    for (int j=i+1;j<n_hands;j++){
      // print_hand(deck_array[i]);
      //            print_hand(deck_array[j]);
      // printf("\n");
      v=compare_hands(deck_array[i],deck_array[j]);
      if(v>0) w[i]++;
      else if (v<0) w[j]++;
      else w[n_hands]++;  
    }
  }
  unsigned largest= 0;
  for(int x=0;x<n_hands+1;x++){
    if(w[x] > w[largest])largest=x;
  }
   int count=0;  
    if(w[n_hands]>0){ 
      for(int x=0;x<n_hands+1;x++){
      	if(w[x] == w[largest]) count++;
	 }
     }
    if(count>1) return n_hands;
  return  largest;  
}
>>>>>>> 8526260b53a4d61e0ef67d597b2ddafc3221357c

  if(argc == 2){
    n_trails = 10000;
  }else{
    n_trails = atoi(argv[2]);
  }

  f = fopen(argv[1],"r");
  hands = read_input(f, &n_hands, fc);
  rem_cards = build_remaining_deck(hands, n_hands);
  win_arr = (int *)realloc(win_arr, (n_hands+1)*sizeof(*win_arr));
  for(size_t k=0; k<n_hands+1; k++){
    win_arr[k] = 0;
  }

  for(int i=0; i<n_trails; i++){
    shuffle(rem_cards);
    future_cards_from_deck(rem_cards, fc);
    actScore(hands, n_hands, win_arr);
  }
  for(size_t h=0; h<n_hands; h++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n", h, win_arr[h], n_trails, 100*(float)win_arr[h]/(float)n_trails);
  }
<<<<<<< HEAD
  printf("And there were %u ties\n", win_arr[n_hands]);
  freeAll(fc, hands, n_hands, rem_cards, win_arr);
  fclose(f);
=======
>>>>>>> 8526260b53a4d61e0ef67d597b2ddafc3221357c
  return EXIT_SUCCESS;
}
