#ifndef CARICON_H
#define CARICON_H

#include <QWidget>
#include<QChart>
#include<QLineSeries>
#include<QValueAxis>
#include<QDateTimeAxis>
#include<QAreaSeries>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Caricon;
}

class Caricon : public QWidget
{
    Q_OBJECT

public:
    explicit Caricon(QWidget *parent = nullptr);
    ~Caricon();
signals:

private:
    Ui::Caricon *ui;
    QChart *chart;
    QLineSeries *m_line;
    QLineSeries *m_avg;
    QValueAxis *axisY;
    QDateTimeAxis *axisX;
    QAreaSeries *area;

};

#endif // CARICON_H
