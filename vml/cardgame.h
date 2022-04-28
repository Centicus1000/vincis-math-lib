#ifndef vml_cardgame_h
#define vml_cardgame_h

#include <iostream>
#include <vector>
#include <list>

namespace vml {

namespace cardgame {

enum Suit{ HEARTS, TILES, CLUBS, SPADES };

struct Card
{
    Suit suit;
    int rank;
    
    Card(Suit, int);
    friend std::ostream& operator<< (std::ostream&, const Card& c);
};


class Deck : private std::vector<Card>
{
    iterator top;
public:
    
    Deck();
    
    void shuffle();
    
    size_type left() const;
    
    Card draw();
    
    Card& peak(size_type);
    const Card& peak(size_type) const;
    
    friend std::ostream& operator<< (std::ostream&, const Deck&);
};

bool operator< (const Card&, const Card&);

class Hand : private std::list<Card>
{
public:
    Hand();
    
    size_type size() const;
    
    void sort();
    
    void draw(Deck&, int);
    
    Card deal(size_type);
    
    friend std::ostream& operator<< (std::ostream&, const Hand&);
};

} /* namespace cardgame */

} /* namespace vml */

#endif /* vml_cardgame_h */
