#ifndef CARD_H
#define CARD_H

#include <string>

using std::string;

enum Suit
{
	Clubs,
	Diamonds,
	Spades,
	Hearts,
};

enum Rank
{
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
};

class Card{
public:
		Card (Suit s, Rank r) : rank(r), suit(s){}

		Suit get_suit(){return suit;}

		Rank get_rank(){
			return rank;
		}

		static string const (Suit s);
		static string const (Rank r);

private:
		Suit suit;
		Rank rank;

};

#endif