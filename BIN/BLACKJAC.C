#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#define BELL '\a'
#define DEALER 0
#define PLAYER 1
#define ACELOW 0
#define ACEHIGH 1

int askedForName = 0 /* False initially */
/* Prototypes */ void dispTitle(void);
void initCardsScreen(int cards[52], int playerPoints[2],
int dealerPoints[2], int total[2],
int * numCards);
int dealCard(int * numCards, int cards[52]);
void dispCard(int cardDrawn, int points[2]);
void totalIt(int points[2], int total[2], int who);
void dealerGetsCard(int *numCards, int cards[52],
int dealerPoints[2]);
void playerGetsCard(int *numCards, int cards[52],
int playerPoints[2]);
char getAns(char mesg[]);
void findWinner(int total[2]);
/* C uses main here */
main()
{
int numCards;
int cards[52], playerPoints[2], dealerPoints[2], total[2];
char ans;
do{ initCardsScreen(cards, playerPoints, dealerPoints, total, &numCards;
dealerGetsCard(&numCards, cards, dealerPoints);
printf("\n");
playerGetsCard(&numCards, cards, playerPoints);
do {
ans = getAns("Hit or Stand (H/S)?");
if (ans == 'H')
{ playerGetsCards(&numCards, cards, playerPoints);
}