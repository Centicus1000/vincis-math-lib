#include "vml/cardgame.h"

#include <array>
#include <random>
#include <algorithm>
#include <iterator>

using namespace vml::cardgame;

Card::Card(Suit _suit, int _rank) : suit(_suit), rank(_rank)
{}

std::ostream& ::vml::cardgame::operator<<(std::ostream& os, const Card& c)
{
    if (c.rank==0) return os << "xx";
    switch (c.suit) {
        case HEARTS:    os << "♥︎"; break;
        case TILES:     os << "♦︎"; break;
        case CLUBS:     os << "♣︎"; break;
        case SPADES:    os << "♠︎"; break;
    };
    switch (c.rank) {
        case  1: return os << "A";
        case 13: return os << "K";
        case 12: return os << "Q";
        case 11: return os << "J";
        default: return os << c.rank;
    }
}

bool ::vml::cardgame::operator< (const Card& first, const Card& second)
{
    if (first.suit == second.suit)
        return first.rank < second.rank;
    return first.suit < second.suit;
}

Deck::Deck()
{
    std::array<Suit, 4> suits{ HEARTS, TILES, CLUBS, SPADES };
    
    for (Suit s : suits)
        for (int r{1}; r <= 13; r++)
            emplace_back(s, r);
    
    top = begin();
}

void Deck::shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle( top, end(), g);
}

Deck::size_type Deck::left() const
{
    return end() - top;
}

Card Deck::draw()
{
    if (left() <= 0) return Card(HEARTS, 0);
    
    Card copy{ *top };
    
    Card& ref{ *top };
    ref.rank = 0;
    
    top++;
    
    return copy;
}

Card& Deck::peak(size_type index = 0)
{
    return at(index);
}
const Card& Deck::peak(size_type index = 0) const
{
    return at(index);
}

std::ostream& ::vml::cardgame::operator<<(std::ostream& os, const Deck& d)
{
    for (const Card& c : d) os << c << ", ";
    return os;
}


Hand::Hand() {}

Hand::size_type Hand::size() const{ return size(); }

void Hand::sort(){ sort(); }

void Hand::draw(Deck& deck, int num = 1)
{
    for(int i{0}; i < num; i++) push_back(deck.draw());
}

Card Hand::deal(size_type index)
{
    iterator it{ begin() };
    std::advance(it, index);
    
    Card copy{ *it };
    erase(it);
    
    return copy;
}

std::ostream& ::vml::cardgame::operator<<(std::ostream& os, const Hand& h)
{
    for (const Card& c : h) os << c << ", ";
    return os;
}
