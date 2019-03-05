#include "card.hpp"

#include <ctime>
#include <iostream>
#include <algorithm>
#include <random>

int
main(int argc, char* argv[])
{
  Deck d {
    PlayingCard{Ace, Spades},
    PlayingCard{Two, Spades},
    PlayingCard{Three, Spades},
    PlayingCard{Four, Spades},
    PlayingCard{Five, Spades},
    PlayingCard{Six, Spades},
    PlayingCard{Seven, Spades},
    PlayingCard{Eight, Spades},
    PlayingCard{Nine, Spades},
    PlayingCard{Ten, Spades},
    PlayingCard{Jack, Spades},
    PlayingCard{Queen, Spades},
    PlayingCard{King, Spades},

    PlayingCard{Ace, Clubs},
    PlayingCard{Two, Clubs},
    PlayingCard{Three, Clubs},
    PlayingCard{Four, Clubs},
    PlayingCard{Five, Clubs},
    PlayingCard{Six, Clubs},
    PlayingCard{Seven, Clubs},
    PlayingCard{Eight, Clubs},
    PlayingCard{Nine, Clubs},
    PlayingCard{Ten, Clubs},
    PlayingCard{Jack, Clubs},
    PlayingCard{Queen, Clubs},
    PlayingCard{King, Clubs},

    PlayingCard{Ace, Diamonds},
    PlayingCard{Two, Diamonds},
    PlayingCard{Three, Diamonds},
    PlayingCard{Four, Diamonds},
    PlayingCard{Five, Diamonds},
    PlayingCard{Six, Diamonds},
    PlayingCard{Seven, Diamonds},
    PlayingCard{Eight, Diamonds},
    PlayingCard{Nine, Diamonds},
    PlayingCard{Ten, Diamonds},
    PlayingCard{Jack, Diamonds},
    PlayingCard{Queen, Diamonds},
    PlayingCard{King, Diamonds},

    PlayingCard{Ace, Hearts},
    PlayingCard{Two, Hearts},
    PlayingCard{Three, Hearts},
    PlayingCard{Four, Hearts},
    PlayingCard{Five, Hearts},
    PlayingCard{Six, Hearts},
    PlayingCard{Seven, Hearts},
    PlayingCard{Eight, Hearts},
    PlayingCard{Nine, Hearts},
    PlayingCard{Ten, Hearts},
    PlayingCard{Jack, Hearts},
    PlayingCard{Queen, Hearts},
    PlayingCard{King, Hearts},

    PlayingCard{Black},
    PlayingCard{Red}
  };

  std::cout << d << '\n';


  return 0;
}
