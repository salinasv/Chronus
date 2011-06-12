#include <stdio.h>
#include <glib.h>

#include "caldav.h"
#include "io.h"
#include "menu.h"

/**********************************************************
 * Util
 *********************************************************/

DavData* get_davData_object()
{
	DavData *data;
	char *user;
	char *password;
	char *url;

	user = config_get_user();
	password = config_get_password();
	url = config_get_calendar_url();
	
	data = dav_new(user,
			password,
			url);
	
	g_free(user);
	g_free(password);
	g_free(url);

	return data;
}

/**********************************************************
 * Dav Test
 *********************************************************/
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

void test_dav_getall_object(DavData *data)
{
	char *cal;

	cal = dav_getall_object(data);
	printf("CalendarData:\n%s\n", cal);

	g_free(cal);
}

void test_dav_api()
{
	DavData *data;

	printf("\n**Testing CALDAV support\n");

	data = get_davData_object();
	
	test_dav_valid(data);
	test_dav_displayname(data);
	test_dav_getall_object(data);

	dav_destroy(data);
}

/**********************************************************
 * IO Test
 *********************************************************/
void test_io_config_get_filename()
{
	char *file;

	file = config_get_filename();

	printf("Config Filename: %s\n", file);
	
	g_free(file);
}

void test_io_config_get_user()
{
	char *user;

	user = config_get_user();

	if (!user) {
		printf("Error getting the user.\n");
		return;
	}

	printf("user: %s\n", user);
	
	g_free(user);
}

void test_io_config_get_password()
{
	char *password;

	password = config_get_password();

	if (!password) {
		printf("Error getting the password.\n");
		return;
	}

	printf("password: %s\n", password);
	
	g_free(password);
}

void test_io_config_get_url()
{
	char *url;

	url = config_get_calendar_url();

	if (!url) {
		printf("Error getting the URL.\n");
		return;
	}

	printf("url: %s\n", url);
	
	g_free(url);
}

void test_io_data_write_new_file(DavData *dav_data)
{
	char *name;
	char *data;

	printf("Write new file.\n");

	name = dav_get_displayname(dav_data);
	data = dav_getall_object(dav_data);

	data_write_new_file(name, data);

}

void test_io_api()
{
	DavData *dav_data;

	printf("\n**Testing IO API\n");
	
	test_io_config_get_filename();
	test_io_config_get_user();
	test_io_config_get_password();
	test_io_config_get_url();

	dav_data = get_davData_object();

	test_io_data_write_new_file(dav_data);

	dav_destroy(dav_data);

}

int main()
{
	printf("*Testing API\n");

	xdg_init();

	test_io_api();
	test_dav_api();

	xdg_uninit();

	return 0;
}
