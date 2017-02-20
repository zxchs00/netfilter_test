#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    system("iptables -A OUTPUT -j NFQUEUE --queue-num 0");
    system("iptables -A INPUT -j NFQUEUE --queue-num 0");

    qRegisterMetaType<std::string>();
}

Widget::~Widget()
{
    system("iptables -D OUTPUT -j NFQUEUE --queue-num 0");
    system("iptables -D INPUT -j NFQUEUE --queue-num 0");
    delete ui;
}

void Widget::on_pushButton_clicked()
{

    // if you want to stop
    if(this->starting){
        ui->pushButton->setText("Start");
        hello->terminate();
        noye->~MyFil();
        free(noye);
    }

    // if you want to start
    else{
        ui->pushButton->setText("Stop");
        noye = new MyFil();
        noye->moveToThread(hello);
        hello->start();

        connect(this,SIGNAL(start_filtering(std::string)),noye,SLOT(run(std::string)));

        hello->start();
        emit start_filtering(ui->filt->text().toStdString());
    }

    // status setting
    QLineEdit* input = ui->filt;
    this->starting = !(this->starting);
    input->setDisabled(this->starting);
}
