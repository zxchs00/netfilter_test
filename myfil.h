#ifndef MYFIL_H
#define MYFIL_H

#include <QObject>

class MyFil : public QObject
{
    Q_OBJECT
public:
    explicit MyFil(QObject *parent = 0);
    ~MyFil();
signals:

public slots:
    void run(std::string fil);

private:
    static u_int32_t print_pkt (struct nfq_data *tb);
    static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,struct nfq_data *nfa, void *data);
};

#endif // MYFIL_H
