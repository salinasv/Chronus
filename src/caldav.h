#ifndef CALDAV_H
#define CALDAV_H

typedef struct _DavData
{
	char *user;
	char *password;
	char *url;
}DavData;

/**
 * Creates a new DavData object.
 *
 * @param user 		The user to be used to authenticate.
 * @param password 	The password to be used to authenticate.
 * @param url 		The calendar provided url.
 */
DavData* dav_new(const char *user, const char *password, const char *url);

/**
 * Destroy a DavData object.
 *
 * @param data 	The object to be destroyed.
 */
void dav_destroy(DavData *data);

#endif /* CALDAV_H */
