#include <basedir.h>
#include <basedir_fs.h>
#include <errno.h>
#include <stdio.h>

#include <sys/stat.h>

#include <glib.h>

#define CONFIG_FILE "account"
#define DATA_PREFIX "calendar"
#define PREFIX "Chronus"

struct xdgHandle *handle;

void xdg_init()
{
	const char *basedir;
	char *path;
	struct stat buf;
	mode_t process_mask;

	handle = g_new(xdgHandle, 1);
	handle = xdgInitHandle(handle);

	/* check if we have the required path */
	basedir = xdgConfigHome(handle);
	path = g_build_filename(basedir, PREFIX, NULL);
	printf("Config dir:%s\n", path);

	if (stat(path, &buf)) {
		xdgMakePath(path, S_IRWXU | S_IRWXG);
		printf("Creating Config dir: %s\n", path);
	}

	g_free(path);

	basedir = xdgDataHome(handle);
	path = g_build_filename(basedir, PREFIX, NULL);
	printf("Data dir:%s\n", path);

	if (stat(path, &buf)) {
		xdgMakePath(path, S_IRWXU | S_IRWXG);
		printf("Creating Data dir: %s\n", path);
	}

	g_free(path);
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

	fd = fopen(path, "r");

	/* TODO: Create the file if it doesn't exist */
	if (!fd) {
		printf("There is not config file %d\n", errno);
		return NULL;
	}

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

char* data_get_path(const char *filename)
{
	char *basedir;
	char *path;

	basedir = xdgDataHome(handle);
	path = g_build_filename(basedir, PREFIX, filename, NULL);
	
	return path;
}

void data_write_new_file(char *filename, char *data)
{
	FILE *fd;
	char *path;

	path = data_get_path(filename);
	fd = fopen(path, "w+");
	g_free(path);

	
	if (!fd) {
		printf("Error opening file. %d\n", errno);
		return;
	}

	if (!fputs(data, fd))
		printf("Error writing file.\n");

	fclose(fd);
}
