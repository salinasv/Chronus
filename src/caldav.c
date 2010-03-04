#include <libcaldav-0.4.0/caldav.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "caldav.h"

DavData* dav_new(const char *user, const char *password, const char *url)
{
	DavData *data;

	data = g_new(DavData, 1);

	data->user = g_strdup(user);
	data->password = g_strdup(password);
	data->url = g_strdup(url);

	return data;
}

void dav_destroy(DavData *data)
{
	g_free(data->user);
	g_free(data->password);
	g_free(data->url);

	g_free(data);
}

/* I got this code directly from libcaldav's caldav-test.c
 * and patched it to use DavData*/
static char* dav_get_uri(DavData *data)
{
	char *pos;
	char *protocol = NULL;
	char *uri = NULL;
	char *newurl = NULL;
	char *url;

	url = data->url;

	if (!data->user)
		return url;
	if ((pos = strstr(url, "//")) != NULL) {
		uri = g_strdup(&(*(pos + 2)));
		protocol = g_strndup(url, pos + 2 - url);
	}
	else {
	    protocol = g_strdup("http://");
	}
	if (!data->password)
		newurl = g_strdup_printf("%s%s@%s", protocol, data->user, uri);
	else
		newurl = g_strdup_printf("%s%s:%s@%s", protocol, data->user, data->password, uri);
	g_free(uri);
	g_free(protocol);
	return newurl;
}

