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

    inline QVector<unsigned> getUserRatings() const {return m_userRatings;}
    inline unsigned getTimesRated() const {return m_timesRated;}
    inline double getRating() const {return m_rating;}

    void addNewRating(unsigned grade);
};

#endif // DECKRATING_H
