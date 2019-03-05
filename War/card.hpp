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


class StandardCard {
public:
  StandardCard(Rank r, Suit s)
    : rank(r), suit(s)
  { }

  Rank get_rank() const { return rank; }
  Suit get_suit() const { return suit; }

private:
  Rank rank;
  Suit suit;
};

bool operator==(StandardCard a, StandardCard b);
bool operator!=(StandardCard a, StandardCard b);

bool operator<(StandardCard a, StandardCard b);
bool operator>(StandardCard a, StandardCard b);
bool operator<=(StandardCard a, StandardCard b);
bool operator>=(StandardCard a, StandardCard b);


class JokerCard
{
public:
  JokerCard(Color c)
    : color(c)
  { }

  Color get_color() const { return color; }

private:
  Color color;
};

union PlayingCardData
{
  PlayingCardData(Rank r, Suit s)
    : sc(r, s)
  { }

  PlayingCardData(Color c)
    : jc(c)
  { }

  StandardCard sc;
  JokerCard jc;
};

enum PlayingCardKind
{
  Standard,
  Joker,
};


class PlayingCard
{
public:
  PlayingCard(Rank r, Suit s)
    : tag(Standard), data(r, s)
  { }

  PlayingCard(Color c)
    : tag(Joker), data(c)
  { }

  bool is_standard() const { 
    return tag == Standard;
  }

  bool is_joker() const { 
    return tag == Joker;
  }

  StandardCard get_as_standard() const {
    assert(is_standard());
    return data.sc;
  }

  Rank get_rank() const {
    assert(is_standard());
    return data.sc.get_rank();
  }

  Suit get_suit() const { 
    assert(is_standard());
    return data.sc.get_suit();
  }

  JokerCard get_as_joker() const {
    assert(is_joker());
    return data.jc;
  }

  Color get_color() const { 
    assert(is_joker());
    return data.jc.get_color();
  }

private:
  PlayingCardKind tag;
  PlayingCardData data;
};

struct PlayingCard 
  : std::variant<StandardCard, JokerCard>
{ };

struct Deck : std::deque<PlayingCard> {
  using std::deque<PlayingCard>::deque;
};

std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Rank r);
std::ostream& operator<<(std::ostream& os, Color r);
std::ostream& operator<<(std::ostream& os, StandardCard c);
std::ostream& operator<<(std::ostream& os, JokerCard c);
std::ostream& operator<<(std::ostream& os, PlayingCard c);
std::ostream& operator<<(std::ostream& os, Deck const& d);



#endif