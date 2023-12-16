#include "lib/plannerscene.h"

PlannerScene::PlannerScene(QObject *parent)
    : QGraphicsScene{parent}
{

}

void PlannerScene::addActivity(ActivityItem *activityItem)
{
//    //    const auto tableWidth = static_cast<int>(this->width());
//    const auto tableHeight = static_cast<int>(this->height());
//    auto currentIndex = m_decks.size();

//    //    auto offset = m_decks.size() == 0 ? 0 : 20;
//    const auto offset = 20;

//    //    adding to the right
//    const auto yPos = (deckItem->height() * currentIndex) % tableHeight;
//    const auto xPos = deckItem->width() * ((deckItem->height() * currentIndex) / tableHeight);
//    deckItem->setPos(xPos + currentIndex * offset, yPos);

    const auto yPos = activityItem->activity().start().hour()*60 + activityItem->activity().start().minute();

    activityItem->setPos(0, yPos);
    m_activities.push_back(activityItem->activity());
}
