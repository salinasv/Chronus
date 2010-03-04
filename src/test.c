#include <stdio.h>
#include <glib.h>

#include "caldav.h"
#include "io.h"

void test_dav_displayname(DavData *data)
{
	char *name;

	name = dav_get_displayname(data);
	printf("CalendarName: %s\n", name);

	g_free(name);
}

void test_dav_valid(DavData *data)
{
	int valid;

	valid = dav_is_valid_server(data);
	printf("[%d]%s\n", valid, valid?"Valid server":"Invalid Server");
}

void test_dav_api()
{
	DavData *data;
	char *user;
	char *password;
	char *url;

	xdg_init();
	user = config_get_user();
	password = config_get_password();
	url = config_get_calendar_url();
	xdg_uninit();
	
	data = dav_new(user,
			password,
			url);
	
	g_free(user);
	g_free(password);
	g_free(url);
	
	test_dav_valid(data);
	test_dav_displayname(data);

	dav_destroy(data);
}

int main()
{
	printf("Testing CALDAV support\n");
	test_dav_api();

	return 0;
}
