#ifndef DECKRATING_H
#define DECKRATING_H

#include <QVector>

class DeckRating
{
private:
    QVector<unsigned> m_userRatings;
    unsigned m_timesRated;
    double m_rating;
public:
    DeckRating();
    ~DeckRating() {}

    inline QVector<unsigned> userRatings() const {return m_userRatings;}
    inline unsigned timesRated() const {return m_timesRated;}
    inline double rating() const {return m_rating;}

    void addNewRating(unsigned grade);
};

#endif // DECKRATING_H
