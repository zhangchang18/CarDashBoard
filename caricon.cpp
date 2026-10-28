#include "caricon.h"
#include "ui_caricon.h"
#include<QChartView>
#include<QDateTime>
#include<QDate>
Caricon::Caricon(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Caricon)
{
    ui->setupUi(this);
    chart = new QChart;
    m_line= new QLineSeries;
    m_avg=new QLineSeries;
    axisX=new QDateTimeAxis;
    axisY=new QValueAxis;
    area=new QAreaSeries;
    m_line->setName("我的");
    QPen greenPen(QColor(76,175,80));
    greenPen.setWidth(2);

    m_line->setPen(greenPen);
    m_line->setPointsVisible(true);
    m_line->setPointLabelsVisible(true);
    m_line->setPointLabelsFormat("@yPoint");
    m_line->setPointLabelsColor(QColor(60, 64, 70));
    QFont labelFont = font();
    labelFont.setPointSize(9);
    m_line->setPointLabelsFont(labelFont);
    m_avg = new QLineSeries;
    m_avg->setName("同车型均值");
    QPen bluePen(QColor(58, 110, 235));
    bluePen.setWidth(2);
    m_avg->setPen(bluePen);

    axisY->setTickCount(6);
    axisY->setLabelFormat("%d");
    axisY->setGridLineColor(QColor(235, 238, 242));
    axisY->setLineVisible(false);
    axisY->setLabelsColor(QColor(120, 126, 134));
    labelFont.setPointSize(10);
    axisY->setLabelsFont(labelFont);
    chart->addAxis(axisY,Qt::AlignLeft);

    axisX->setFormat("MM-dd");
    axisX->setTickCount(7);
    axisX->setGridLineVisible(false);
    axisX->setLineVisible(false);
    axisX->setLabelsColor(QColor(120, 126, 134));
    axisX->setLabelsFont(labelFont);
    chart->addAxis(axisX,Qt::AlignBottom);

    QStringList dates;
    dates << "10-07" << "10-08" << "10-09" << "10-10"
                             << "10-11" << "10-12" << "10-13";

    QVector<double> values;
    values << 5.5 << 4.0 << 3.8 << 4.0 << 4.1 << 4.0 << 4.1;

    m_line->clear();
    m_avg->clear();

    qint64 minTime = 0, maxTime = 0;
    for (int i = 0; i < dates.size(); ++i)
    {
        QDate d = QDate::fromString(dates.at(i), "MM-dd");
        qint64 t = QDateTime(d, QTime(0, 0)).toMSecsSinceEpoch();
        if (i == 0) { minTime = t; maxTime = t; }
        minTime = qMin(minTime, t);
        maxTime = qMax(maxTime, t);

        m_line->append(t, values.at(i));
    }

    m_avg->append(minTime, 5.9);
    m_avg->append(maxTime, 5.9);

    // 区域在构造时绑定 m_line，并且最后添加，避免盖住折线
    area=new QAreaSeries(m_line);
    QLinearGradient grad(0, 0, 0, 1);
    grad.setCoordinateMode(QGradient::ObjectBoundingMode);
    grad.setColorAt(0.0, QColor(76, 175, 80, 80));
    grad.setColorAt(1.0, QColor(76, 175, 80, 0));
    area->setBrush(grad);
    area->setPen(Qt::NoPen);

    // 先加折线，再加区域，最后再统一 attach
    chart->addSeries(m_line);
    chart->addSeries(m_avg);
    chart->addSeries(area);

    m_line->attachAxis(axisY);
    m_avg->attachAxis(axisY);
    m_line->attachAxis(axisX);
    m_avg->attachAxis(axisX);
    area->attachAxis(axisX);
    area->attachAxis(axisY);

    chart->legend()->setVisible(false);
    ui->graphicsView->setChart(chart);

    // 关键：范围放到所有系列和轴都挂好之后
    axisY->setRange(0, 10);
    axisX->setMin(QDateTime::fromMSecsSinceEpoch(minTime));
    axisX->setMax(QDateTime::fromMSecsSinceEpoch(maxTime));
}

Caricon::~Caricon()
{
    delete ui;
}
