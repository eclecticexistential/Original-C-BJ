#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#define BELL '\a'
#define DEALER 0
#define PLAYER 1
#define ACELOW 0
#define ACEHIGH 1
int askedForName = 0; /* False Initially */
void dispTitle(void);
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
main()
{
int numCards;
int cards[52], playerPoints[2], dealerPoints[2], total[2];
char ans;  /* For user's Hit/Stand or Yes/No response */
do{ initCardsScreen(cards, playerPoints, dealerPoints,
total, &numCards);
dealerGetsCard(&numCards, cards, dealerPoints);
printf("\n"); /* Prints a blank line */
playerGetsCard(&numCards, cards, playerPoints);
playerGetsCard(&numCards, cards, playerPoints);
do{
ans = getAns("Hit or stand (H/S)? ");
if (ans == 'H' )
{ playerGetsCard(&numCards, cards,
playerPoints);
}
} while (ans != 'S');
totalIt(playerPoints, total, PLAYER);
/* Player's total */
do {
dealerGetsCard(&numCards, cards, dealerPoints);
} while (dealerPoints[ACEHIGH] < 17);
/* 17: Dealer Stops */
totalIt(dealerPoints, total, DEALER);
/* Dealer's total */
findWinner(total);
ans = getAns("\nPlay again (Y/N)? ");
} while (ans == 'Y');
return;
}
void initCardsScreen(int cards[52], int playerPoints[2],
int dealerPoints[2], int total[2],
int *numCards)
{
int sub, val = 1; /* This' function's Work variables */
char firstName[15]; /* Holds user's first name */
*numCards = 52; /* Holds running total of number cards */
for (sub = 0; sub <= 51; sub ++) { /* Counts from 0 to 51 */
val = (val == 14) ? 1 : val; /* If val is 14 reset to 1 */
cards[sub] = val;
val++; }
for (sub = 0; sub <= 1; sub ++) /* Counts from 0 to 1 */
{playerPoints[sub]=dealerPoints[sub]=total[sub]=0; }
dispTitle();
if (askedForName == 0) /* Name asked for only once */
{ printf("\nWhat is your first name? ");
scanf(" %s", firstName);
askedForName = 1; /* Don't ask prompt again */
printf("Ok, %s, get ready for casino action!\n\n",
firstName);
getchar(); /* Discards newline. You can safely ignore compiler warning here. */
}
return;
}
void playerGetsCard(int *numCards, int cards[52],
int playerPoints[2])
{
int newCard;
newCard = dealCard(numCards, cards);
printf("You draw: ");
dispCard(newCard, playerPoints);
}
void dealerGetsCard(int *numCards, int cards[52],
int dealerPoints[2])
{
int newCard;
newCard = dealCard(numCards, cards);
printf("The dealer draws: ");
dispCard(newCard, dealerPoints);
}int dealCard(int * numCards, int cards[52]) {
int cardDrawn, subDraw;
time_t t; /* Gets time for a random value */
srand(time(&t)); /* Seeds random-number generator */
subDraw = (rand() % (*numCards)); /* From 0 to numcards */
cardDrawn = cards[subDraw];
cards[subDraw] = cards[*numCards - 1]; /* Puts top card in place of drawn one */
(*numCards) --;
return cardDrawn;
}
void dispCard(int cardDrawn, int points[2])
{
switch (cardDrawn) {
case(11) : printf("%s\n", "Jack");
points[ACELOW] += 10;
points[ACEHIGH] += 10;
break;
case(12) : printf("%s\n", "Queen");
points[ACELOW] += 10;
points[ACEHIGH] += 10;
break;
case(13) : printf("%s\n", "King");
points[ACELOW] += 10;
points[ACEHIGH] += 10;
break;
default : points [ACELOW] += cardDrawn;
if (cardDrawn == 1)
{ printf("%s\n", "Ace");
points[ACEHIGH] += 11;
}
else
{ points[ACEHIGH] += cardDrawn;
printf("%d\n", cardDrawn); }
}
return;
}
/* Figures the total for player or dealer to confirm who won.
This function takes into account whether the Ace equals 1 or 11. */
void totalIt(int points[2], int total[2], int who)
{
/* The following routine first looks to see if the total points count Ace
as 1 or as 11. If the total is more than 21, the total uses Ace as 1 only. */
if ((points[ACELOW] == points[ACEHIGH]) ||
(points[ACEHIGH] > 21))
{ total[who] = points[ACELOW]; } /* Keeps all aces as 1 */
else
{ total[who] = points[ACEHIGH]; } /* Keeps all aces as 11 */
if (who == PLAYER) /* Determines the message printed */
{printf("You have a total of %d\n\n", total[PLAYER]); }
else
{printf("The house stands with a total of %d\n\n",
total[DEALER]); }
return;
}
/* Prints the winning player. */
void findWinner(int total[2])
{
if (total[DEALER] == 21)
{printf("The house wins.\n");
return;}
if (total[DEALER] > 21 && (total[PLAYER] > 21))
{printf("%s", "Nobody wins. Boo!\n");
return; } if((total[DEALER]>=total[PLAYER])&&(total[DEALER]<21)) { printf("The house wins.\n"); return;} if((total[PLAYER] > 21) && (total[DEALER]< 21)) {printf("The house wins.\n"); return;}
printf("%s%c", "You win! Yay!\n", BELL);
return;
}
/* Gets the user's uppercase, single character response */
char getAns(char mesg[])
{
char ans;
printf("%s", mesg); /* Prints prompt message passed */
ans = getchar();
getchar(); /* Discards newline. You can safely ignore compiler warning. */
return toupper(ans);
}
/* Clears screen */
void dispTitle(void)
{
int i= 0;
while (i < 25 )
{ printf("\n");
i++; }
printf("\n\n*Step right up to the Blackjack tables*\n\n");
return;
}