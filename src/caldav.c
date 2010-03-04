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

void dav_error(char *module, CALDAV_RESPONSE res)
{
	caldav_error *error = NULL;

	error = caldav_get_error(error);
	printf("Error in %s:\n(%ld) %s\n", module?module:"", error->code, error->str);
	caldav_free_error(error);
}

int dav_is_valid_server(DavData *data)
{
	char *uri;
	int valid;

	uri = dav_get_uri(data);
	valid = caldav_enabled_resource(uri);

	g_free(uri);
	
	return valid;
}

char* dav_get_displayname(DavData *data)
{
	char *uri;
	response result;
	CALDAV_RESPONSE res = UNKNOWN;

	uri = dav_get_uri(data);

	res = caldav_get_displayname(&result, uri);
	g_free(uri);

	if (res != OK) {
		dav_error("displayname", res);
		return NULL;
	}

	return result.msg;
}	
