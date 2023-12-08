#ifndef DECKSTATS_H
#define DECKSTATS_H

#include <QDate>

class DeckStats
{
private:
    double m_profficiency;
    unsigned m_timesUsed;
    QDate m_creationDate;
public:
    DeckStats();
    ~DeckStats() {}

    inline double profficiency() const {return m_profficiency;}
    inline unsigned int timesUsed() const {return m_timesUsed;}
    inline QDate creationDate() const {return m_creationDate;}

//    TODO
//    void calculate();
//    void update();
};

#endif // DECKSTATS_H
