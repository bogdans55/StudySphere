#include "lib/deckrating.h"

DeckRating::DeckRating()
    : m_userRatings(),
    m_timesRated(0u),
    m_rating(0.0)
{}

void DeckRating::addNewRating(unsigned int grade)
{
    m_userRatings.append(grade);
    m_timesRated++;
    m_rating = (m_rating * (m_timesRated-1) + grade) / m_timesRated;
}
