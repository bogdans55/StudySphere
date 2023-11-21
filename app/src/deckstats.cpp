#include "lib/deckstats.h"

#include <QDate>

DeckStats::DeckStats()
    : m_profficiency(0.0),
    m_timesUsed(0u),
    m_creationDate(QDate::currentDate())
{}
