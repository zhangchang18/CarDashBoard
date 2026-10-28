#include "map.h"
#include "ui_map.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPainter>
#include <QWheelEvent>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground);

    // 1. 创建场景，把地图图片放进去
    scene = new QGraphicsScene(this);
    mapItem = scene->addPixmap(QPixmap(":/background/main/map.png"));

    // 2. 场景关联到视图
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);                // 抗锯齿，放大更平滑
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);           // 按住鼠标可拖动地图
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // 缩放时以鼠标位置为中心

    // 3. 初始把整张地图缩放到正好显示在视图内，作为缩放基准 1.0
    ui->graphicsView->fitInView(mapItem, Qt::KeepAspectRatio);
    currentScale = 1.0;
    updateZoomLabel();

    // 4. 监听视图的滚轮事件，实现滚轮缩放
    ui->graphicsView->viewport()->installEventFilter(this);
}

Map::~Map()
{
    delete ui;
}

void Map::applyZoom(qreal factor)
{
    qreal next = currentScale * factor;
    if (next < 0.2) next = 0.2;   // 最小缩小到 20%
    if (next > 8.0) next = 8.0;   // 最大放大到 800%

    // 比例没有变化时不做任何操作
    if (qFuzzyCompare(next, currentScale))
        return;

    ui->graphicsView->scale(factor, factor);
    currentScale = next;
    updateZoomLabel();
}

void Map::updateZoomLabel()
{
    ui->label_zoom->setText(QString("%1%").arg(qRound(currentScale * 100)));
}

void Map::on_pushButton_zoomin_clicked()
{
    applyZoom(1.25);   // 每次放大 25%
}

void Map::on_pushButton_zoomout_clicked()
{
    applyZoom(0.8);    // 每次缩小 20%
}

void Map::on_pushButton_back_clicked()
{
    emit backToHome();
}

bool Map::eventFilter(QObject *watched, QEvent *event)
{
    // 鼠标滚轮缩放地图
    if (watched == ui->graphicsView->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *w = static_cast<QWheelEvent *>(event);
        if (w->angleDelta().y() > 0)
            applyZoom(1.25);   // 向上滚动放大
        else
            applyZoom(0.8);    // 向下滚动缩小
        return true;           // 事件已被处理，不再继续传递
    }
    return QWidget::eventFilter(watched, event);
}
