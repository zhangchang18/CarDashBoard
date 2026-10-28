#ifndef THEME_H
#define THEME_H

#include <QWidget>
#include<QList>
#include<QLabel>
namespace Ui {
class Theme;
}

class Theme : public QWidget
{
    Q_OBJECT

public:
    explicit Theme(QWidget *parent = nullptr);
    ~Theme();

    bool eventFilter(QObject *watch,QEvent *event) override;

signals:
    void sendThemePath(QString Path);

private slots:
    void on_pushButton_changetheme_clicked();

private:
    Ui::Theme *ui;
    QList<QString> imgPaths;
    QList<QLabel *> list_labels;
    int imgIndex=0;
};

#endif // THEME_H
