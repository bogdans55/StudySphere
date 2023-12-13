#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <QString>
#include <QTime>


class Activity
{
public:
    Activity();
    Activity(QString m_activityText, QTime m_start, QTime m_end);
    ~Activity();

    //Getters
    inline QString activityText() const {return m_activityText;}
    inline QTime start() const {return m_start;}
    inline QTime end() const {return m_end;}
 //   inline Day day() const {return m_day;}

//    QVariant toVariant() const override;
//    void fromVariant(const QVariant &variant) override;


private:
    QString m_activityText;
    QTime m_start;
    QTime m_end;
//    Day m_day;
};



#endif // ACTIVITY_H
