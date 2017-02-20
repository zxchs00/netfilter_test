#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QLineEdit>

#include "myfil.h"

Q_DECLARE_METATYPE(std::string)

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
signals:
    void start_filtering(std::string fil);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    bool starting = false;
    QThread* hello = new QThread();
    MyFil* noye;
};

#endif // WIDGET_H
