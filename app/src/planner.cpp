#include "lib/planner.h"

Planner::Planner()
    :m_map()
{}

Planner::~Planner(){}

void Planner::addActivity(Activity activity, Day day){
    m_map[day].push_back(activity);
}

QVariant Planner::toVariant() const{}

void Planner::fromVariant(const QVariant &variant){}
