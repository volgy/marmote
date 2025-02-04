#include "lwip/stats.h"
#include "sampleserver.h"
#include "lwip/tcp.h"

unsigned char appdata[20];

struct server_state
{
    char *file;                     /* Pointer to first unsent byte in buf. */
    char *buf;                                          /* File read buffer */

    u32_t left;                           /* Number of unsent bytes in buf. */
    int buf_len;                          /* Size of file read buffer, buf. */
    u8_t retries;
};


/*..........................................................................*/
static void conn_err(void *arg, err_t err)
{
    struct server_state *hs;

    LWIP_UNUSED_ARG(err);

    if (!arg)
    	return;

    hs = arg;

	if (hs->buf)
		mem_free(hs->buf);

	mem_free(hs);
}


/*..........................................................................*/
static void close_conn(struct tcp_pcb			*pcb,
						struct server_state		*hs)
{
    err_t err;
//    DEBUG_PRINT("Closing connection 0x%08x\n", pcb);

    tcp_arg(pcb, NULL);
    tcp_sent(pcb, NULL);
    tcp_recv(pcb, NULL);

    if (hs->buf)
        mem_free(hs->buf);
    mem_free(hs);
    err = tcp_close(pcb);
//    if (err != ERR_OK)
//        DEBUG_PRINT("Error %d closing 0x%08x\n", err, pcb);
}


/*..........................................................................*/
static void send_data(struct tcp_pcb		*pcb,
					struct server_state		*hs)
{
    err_t err;
    u16_t len;

	/* We cannot send more data than space available in the send buffer */
	if (tcp_sndbuf(pcb) < hs->left)
		len = tcp_sndbuf(pcb);
	else
	{
		len = hs->left;
		LWIP_ASSERT("hs->left did not fit into u16_t!", (len == hs->left));
	}

	if (len > (2*pcb->mss))
		len = 2*pcb->mss;

	do {
//            DEBUG_PRINT("Sending %d bytes\n", len);

            /* If the data is being read from a buffer in RAM, we need to copy
            * it into the PCB. If it's in flash, however, we can avoid the
            * copy since the data is obviously not going to be overwritten
            * during the life of the connection.
            */
//            err = tcp_write(pcb, hs->file, len, (hs->file < (char *)0x20000000) ? 0 : 1);
// Always copy
		err = tcp_write(pcb, hs->file, len, TCP_WRITE_FLAG_COPY);

		if (err == ERR_MEM)
			len /= 2;
	} while (err == ERR_MEM && len > 1);

	if (err != ERR_OK)
		return;

	hs->file += len;
	hs->left -= len;

//    DEBUG_PRINT("tcp_output\n");
	tcp_output(pcb);

//    DEBUG_PRINT("send_data end.\n");
}


/*..........................................................................*/
static err_t server_poll(void				*arg,
						struct tcp_pcb		*pcb)
{
    struct server_state *hs = arg;

//    DEBUG_PRINT("server_poll 0x%08x\n", pcb);

    if (hs == NULL)
    {
        tcp_abort(pcb);
        return ERR_ABRT;
    }

    ++hs->retries;
    if (hs->retries == 4) {
    	tcp_abort(pcb);
        return ERR_ABRT;
	}

        /* If this connection has a file open, try to send some more data. If
        * it has not yet received a GET request, don't do this since it will
        * cause the connection to close immediately. */

    send_data(pcb, hs);

    return ERR_OK;
}


/*..........................................................................*/
static err_t server_sent(void				*arg,
						struct tcp_pcb		*pcb,
						u16_t				len)
{
    struct server_state *hs;

//    DEBUG_PRINT("server_sent 0x%08x\n", pcb);

    LWIP_UNUSED_ARG(len);

    if (arg == NULL)
        return ERR_OK;

    hs = arg;

    hs->retries = 0;

    if (hs->left > 0)
    {
      /* Temporarily disable send notifications */
      tcp_sent(pcb, NULL);

      send_data(pcb, hs);

      /* Reenable notifications. */
      tcp_sent(pcb, server_sent);

      return ERR_OK;
    }



    //test begin

          appdata[0] = 'I';
          appdata[1] = 'S';
          appdata[2] = 'I';
          appdata[3] = 'S';
          appdata[4] = ' ';
          appdata[5] = ':';
          appdata[6] = ')';
          appdata[7] = ' ';
/*
          appdata[0] = 0xAA;
          appdata[1] = 0xAA;
          appdata[2] = 0xAA;
          appdata[3] = 0xAA;
          appdata[4] = 0xAA;
          appdata[5] = 0xAA;
          appdata[6] = 0xAA;
          appdata[7] = 0xAA;
*/
          hs->file = (char *)appdata;
          hs->left = 8;
          send_data(pcb, hs);
          // Tell TCP that we wish be to informed of data that has been
          //   successfully sent by a call to the http_sent() function.
          tcp_sent(pcb, server_sent);

    //test end




    return ERR_OK;
}


/*..........................................................................*/
static err_t server_recv(void				*arg,
						struct tcp_pcb		*pcb,
						struct pbuf			*p,
						err_t				err)
{
    char *data;
    struct server_state *hs = arg;

//    DEBUG_PRINT("server_recv 0x%08x\n", pcb);

    if (err != ERR_OK)
        return ERR_OK; //TODO: is this return value OK?

    if (p == NULL)
    {
    	//TODO: is this OK?
        close_conn(pcb, hs);
        return ERR_OK;
    }

    /* Inform TCP that we have taken the data. */
    tcp_recved(pcb, p->tot_len);

    data = p->payload;

// Generate output data
/*
                if (file) {
                    hs->file = file->data;
                    LWIP_ASSERT("File length must be positive!",
                                (file->len >= 0));
                    hs->left = file->len;
                    hs->retries = 0;
                    pbuf_free(p);
                }
                else {
                    hs->file = NULL;
                    hs->left = 0;
                    hs->retries = 0;
                }
*/

	/*Tell TCP that we wish be to informed of data that has been
	* successfully sent by a call to the server_sent() function.
	*/
//	tcp_sent(pcb, server_sent);

    /* Start sending the headers and file data. */
//	send_data(pcb, hs);

    pbuf_free(p);

// If you wanna close the connection
//    close_conn(pcb, hs);

    return ERR_OK;
}


/*..........................................................................*/
static err_t server_accept(void					*arg,
							struct tcp_pcb		*pcb,
							err_t				err)
{
    struct server_state *hs;

    LWIP_UNUSED_ARG(arg);
    LWIP_UNUSED_ARG(err);

//    DEBUG_PRINT("server_accept 0x%08x\n", pcb);

    /* Allocate memory for the structure that holds the state of the
    connection. */
    hs = (struct server_state *)mem_malloc(sizeof(struct server_state));

    if (hs == NULL)
    {
//        DEBUG_PRINT("server_accept: Out of memory\n");
        return ERR_MEM;
    }

    /* Initialize the structure. */
    hs->file = NULL;
    hs->buf = NULL;
    hs->buf_len = 0;
    hs->left = 0;
    hs->retries = 0;


    /* Tell TCP that this is the structure we wish to be passed for our
    callbacks. */
    tcp_arg(pcb, hs);

    /* Tell TCP that we wish to be informed of incoming data by a call
    to the server_recv() function. */
    tcp_recv(pcb, server_recv);

    tcp_err(pcb, conn_err);

    tcp_poll(pcb, server_poll, 4);

//test begin

      appdata[0] = 'I';
      appdata[1] = 'S';
      appdata[2] = 'I';
      appdata[3] = 'S';
      appdata[4] = ' ';
      appdata[5] = ':';
      appdata[6] = ')';
      appdata[7] = ' ';
/*
      appdata[0] = 0xAA;
      appdata[1] = 0xAA;
      appdata[2] = 0xAA;
      appdata[3] = 0xAA;
      appdata[4] = 0xAA;
      appdata[5] = 0xAA;
      appdata[6] = 0xAA;
      appdata[7] = 0xAA;
*/
      hs->file = (char *)appdata;
      hs->left = 8;
      send_data(pcb, hs);
      // Tell TCP that we wish be to informed of data that has been
      //   successfully sent by a call to the http_sent() function.
      tcp_sent(pcb, server_sent);

//test end

    return ERR_OK;
}


/*..........................................................................*/
void server_init(u16_t port)
{
    struct tcp_pcb *pcb;

//    DEBUG_PRINT("server_init\n");

    pcb = tcp_new();
    tcp_bind(pcb, IP_ADDR_ANY, port);
    pcb = tcp_listen(pcb);
    tcp_accept(pcb, server_accept);
}
