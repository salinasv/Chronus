#include <basedir.h>
#include <stdio.h>

#include <glib.h>

#define CONFIG_FILE "account"
#define DATA_PREFIX "calendar"
#define PREFIX "Chronus"

struct xdgHandle *handle;

void xdg_init()
{
	handle = g_new(xdgHandle, 1);
	handle = xdgInitHandle(handle);
}

void xdg_uninit()
{
	xdgWipeHandle(handle);
	g_free(handle);
}

char* config_get_filename()
{
	char *basedir;
	char *path;

	basedir = xdgConfigHome(handle);

	path = g_build_filename(basedir, PREFIX, CONFIG_FILE, NULL);

	return path;
}

char* config_get_user()
{
	char *path;
	FILE *fd;
	char buffer[100];
	char *user;

	path = config_get_filename();

	/* TODO: Create the file if it doesn't exist */
	fd = fopen(path, "r");
	fgets(buffer, 100, fd);

	user = g_strdup(buffer);

	fclose(fd);

	return g_strstrip(user);

}

char* config_get_password()
{
	char *path;
	FILE *fd;
	char buffer[100];
	char *password;

	path = config_get_filename();

	/* TODO: Create the file if it doesn't exist */
	fd = fopen(path, "r");
	fgets(buffer, 100, fd);
	fgets(buffer, 100, fd);

	password = g_strdup(buffer);

	fclose(fd);

	return g_strstrip(password);
}

char* config_get_calendar_url()
{
	char *path;
	FILE *fd;
	char buffer[100];
	char *url;

	path = config_get_filename();

	/* TODO: Create the file if it doesn't exist */
	fd = fopen(path, "r");
	fgets(buffer, 100, fd);
	fgets(buffer, 100, fd);
	fgets(buffer, 100, fd);

	url = g_strdup(buffer);

	fclose(fd);

	return g_strstrip(url);
}
