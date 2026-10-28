#ifndef MAP_H
#define MAP_H

#include <QWidget>

class QGraphicsScene;
class QGraphicsPixmapItem;

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    // 事件过滤器：处理鼠标滚轮缩放地图
    bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void backToHome();   // 返回主页

private slots:
    void on_pushButton_zoomin_clicked();   // 放大按钮
    void on_pushButton_zoomout_clicked();  // 缩小按钮
    void on_pushButton_back_clicked();     // 返回按钮

private:
    void applyZoom(qreal factor);   // 按倍数缩放地图
    void updateZoomLabel();         // 刷新缩放比例显示

private:
    Ui::Map *ui;
    QGraphicsScene *scene;             // 场景，用来存放地图
    QGraphicsPixmapItem *mapItem;      // 场景里的地图图片
    qreal currentScale = 1.0;          // 当前缩放比例（以“正好显示”为 1.0）
};

#endif // MAP_H
