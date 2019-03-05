#include "card.hpp"
#include <iostream>


std::ostream&
operator<<(std::ostream& os, Suit s)
{
  switch (s) {
  case Clubs: return os << "C";
  case Spades: return os << "S";
  case Hearts: return os << "H";
  case Diamonds: return os << "D";
  }
}

std::ostream&
operator<<(std::ostream& os, Rank r)
{
  switch (r) {
  case Ace: return os << "A";
  case Two: return os << "2";
  case Three: return os << "3";
  case Four: return os << "4";
  case Five: return os << "5";
  case Six: return os << "6";
  case Seven: return os << "7";
  case Eight: return os << "8";
  case Nine: return os << "9";
  case Ten: return os << "T";
  case Jack: return os << "J";
  case Queen: return os << "Q";
  case King: return os << "K";
  }
}

std::ostream&
operator<<(std::ostream& os, Color c)
{
  return os << (c == Black ? "B" : "R");
}

std::ostream&
operator<<(std::ostream& os, StandardCard c)
{
  return os << c.get_suit() << c.get_rank();
}

std::ostream&
operator<<(std::ostream& os, JokerCard c)
{
  return os << c.get_color();
}

std::ostream&
operator<<(std::ostream& os, PlayingCard c)
{
  if (c.is_standard())
    return os << c.get_as_standard();
  else
    return os << c.get_as_joker();
}

std::ostream& 
operator<<(std::ostream& os, Deck const& d)
{
  int n = 0;
  for (PlayingCard c : d) {
    os << c << ' ';
    if (n == 12) {
      os << '\n';
      n = 0;
    }
    else {
      ++n;
    }
  }
  return os;
}
