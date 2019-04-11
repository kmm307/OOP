#ifndef CARD_H
#define CARD_H

#include <deque>
#include <iosfwd>

enum Suit
{
	Clubs,
	Spades,
	Hearts,
	Diamonds,
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

enum Color {
  Black,
  Red,
};




struct Card {
  
  virtual Color get_color() const = 0;
};


struct StandardCard : Card {
  StandardCard(Rank r, Suit s)
    : rank(r), suit(s)
  { }

  
  void print(std::ostream& os) const override;

  Color get_color() const override {
    return static_cast<Color>(suit > Diamonds);
  }

  Rank rank;
  Suit suit;
};

struct JokerCard : Card {
  JokerCard(Color c)
    : color(c)
  { }
  
  void print(std::ostream& os) const override;

  Color get_color() const override {
    return color;
  }
  
  Color color;
};


struct Deck : std::deque<Card*> {
  using std::deque<Card*>::deque;
};

std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Rank r);
std::ostream& operator<<(std::ostream& os, Color c);
std::ostream& operator<<(std::ostream& os, StandardCard const& c);
std::ostream& operator<<(std::ostream& os, JokerCard const& c);
std::ostream& operator<<(std::ostream& os, Card const& c);
std::ostream& operator<<(std::ostream& os, Deck const& d);
