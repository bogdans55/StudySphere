#ifndef STUDYSESSION_H
#define STUDYSESSION_H

#include<QString>
#include<iostream>
#include <QVector>
#include<time.h>

#include "lib/deck.h"
#include "lib/user.h"
#include "lib/card.h"

class StudySession
{
private:
    User m_user;
    Deck m_deck;
    unsigned m_currentCardIndex;
    time_t m_timeStarted;
    time_t m_timeEnded;
    QVector<unsigned> m_cardSequence;
public:
    StudySession(const User &user, const Deck &deck);
    ~StudySession();

    inline User user() const {return m_user;}
    inline Deck deck() const {return m_deck;}
    inline unsigned currentCardIndex() const {return m_currentCardIndex;}
    inline time_t timeStarted() const {return m_timeStarted;}
    inline time_t timeEnded() const {return m_timeEnded;}
    inline QVector<unsigned> cardSequence(){return m_cardSequence;}

    void startSession();
    void endSession();
    QVector<unsigned> chooseCardSequence(Deck &deck, unsigned num_cards);
    void nextCard();
    Card getCurrentCard();
    void saveStatus();
};


#endif // STUDYSESSION_H
