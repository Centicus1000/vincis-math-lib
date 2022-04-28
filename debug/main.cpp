#include "vml/cardgame.h"

#include <array>
#include <iostream>

int main() {
    
    using namespace vml::cardgame;
    
    Deck deck{};
    deck.shuffle();
    
    std::cout << deck << std::endl;

    Hand hand{};
    hand.draw(deck, 4);

    std::cout << deck << std::endl;
    std::cout << hand << std::endl;
}

