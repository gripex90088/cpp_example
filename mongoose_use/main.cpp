/*
 * main.cpp
 *
 *  Created on: Sep 18, 2019
 *      Author: xuxing
 */

#include <iostream>
#include "mongoose.h"
#include "mg_http_server.h"

using namespace std;

static const char *s_http_port = "65534";

static void ev_handler(struct mg_connection *c, int ev, void *p)
{
	if (ev == MG_EV_HTTP_REQUEST) {
		struct http_message *hm = (struct http_message *) p;

		cout << (hm->body).p << endl;

		mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
	    mg_printf(c, "%.*s", (int)hm->message.len, hm->message.p);
	}
}

int main()
{
daemon(0, 0);
while(true) {
	struct mg_mgr mgr;
	struct mg_connection *c;

	mg_mgr_init(&mgr, NULL);
	c = mg_bind(&mgr, s_http_port, ev_handler);
	mg_set_protocol_http_websocket(c);

	for (;;)
		mg_mgr_poll(&mgr, 1000);

	mg_mgr_free(&mgr);
}


	return 0;

}
