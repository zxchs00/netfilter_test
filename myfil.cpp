#include "myfil.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>        /* for NF_ACCEPT */
#include <errno.h>

#include <libnetfilter_queue/libnetfilter_queue.h>

MyFil::MyFil(QObject *parent) : QObject(parent)
{

}
MyFil::~MyFil(){

}

void MyFil::run(std::string fil){
    struct nfq_handle *h;
        struct nfq_q_handle *qh;
        struct nfnl_handle *nh;
        int fd;
        int rv;
        char buf[4096] __attribute__ ((aligned));
        h = nfq_open();
        if (!h) {
            printf("1");
            //exit(1);
        }
        if (nfq_unbind_pf(h, AF_INET) < 0) {
            printf("2");
            //exit(1);
        }
        if (nfq_bind_pf(h, AF_INET) < 0) {
            printf("3");
            //exit(1);
        }
        qh = nfq_create_queue(h,  0, &cb, NULL);
        if (!qh) {
            printf("4");
            //exit(1);
        }
        if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) {
            printf("5");
            //exit(1);
        }

        fd = nfq_fd(h);

        for (;;) {
            if ((rv = recv(fd, buf, sizeof(buf), 0)) >= 0) {
                nfq_handle_packet(h, buf, rv);
                continue;
            }
            if (rv < 0 && errno == ENOBUFS) {
                continue;
            }
            break;
        }
        nfq_destroy_queue(qh);

    #ifdef INSANE
        nfq_unbind_pf(h, AF_INET);
    #endif
        nfq_close(h);
        printf("6");
        //exit(0);
}

u_int32_t MyFil::print_pkt (struct nfq_data *tb)
{
    int id = 0;
    struct nfqnl_msg_packet_hdr *ph;

    ph = nfq_get_msg_packet_hdr(tb);
    if (ph) {
        id = ntohl(ph->packet_id);
    }
    return id;
}

int MyFil::cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data)
{
    u_int32_t id = print_pkt(nfa);

    return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
}
