#include "card.hpp"

string suit(Suit s){
		switch(s) {
			case Clubs: return "Clubs";
			case Diamonds: return "Diamonds";
			case Spades: return "Spades";
			case Hearts: return "Hearts";

		}
}

string rank(Rank r){
		switch(r){
			case Ace: return "Ace";
			case Two: return "Two";
			case Three: return "Three";
			case Four: return "Four";
			case Five: return "Five";
			case Six: return "Six";
			case Seven: return "Seven";
			case Eight: return "Eight";
			case Nine: return "Nine";
			case Ten: return "Ten";
			case Jack: return "Jack";
			case Queen: return "Queen";
			case King: return "King";
		} 
}
