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

char* config_get_user()
{
	char *basedir;
	char *path;
	FILE *fd;
	char buffer[100];
	char *user;

	basedir = xdgConfigHome(handle);

	path = g_build_filename(basedir, PREFIX, CONFIG_FILE, NULL);

	printf("path: %s\n", path);

	/* TODO: Create the file if it doesn't exist */
	fd = fopen(path, "r");
	fgets(buffer, 100, fd);

	user = g_strdup(buffer);

	fclose(fd);

	return g_strstrip(user);

}

char* config_get_password()
{
	char *basedir;
	char *path;
	FILE *fd;
	char buffer[100];
	char *user;

	basedir = xdgConfigHome(handle);

	path = g_build_filename(basedir, PREFIX, CONFIG_FILE, NULL);

	printf("path: %s\n", path);

	/* TODO: Create the file if it doesn't exist */
	fd = fopen(path, "r");
	fgets(buffer, 100, fd);
	fgets(buffer, 100, fd);

	user = g_strdup(buffer);

	fclose(fd);

	return g_strstrip(user);
}

char* config_get_calendar_url()
{
	char *basedir;
	char *path;
	FILE *fd;
	char buffer[100];
	char *url;

	basedir = xdgConfigHome(handle);

	path = g_build_filename(basedir, PREFIX, CONFIG_FILE, NULL);

	printf("path: %s\n", path);

	/* TODO: Create the file if it doesn't exist */
	fd = fopen(path, "r");
	fgets(buffer, 100, fd);
	fgets(buffer, 100, fd);
	fgets(buffer, 100, fd);

	url = g_strdup(buffer);

	fclose(fd);

	return g_strstrip(url);
}
