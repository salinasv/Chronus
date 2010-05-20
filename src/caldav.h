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
 *
 * @return 			A DavData object.
 */
DavData* dav_new(const char *user, const char *password, const char *url);

/**
 * Destroy a DavData object.
 *
 * @param data 	The object to be destroyed.
 */
void dav_destroy(DavData *data);

/**
 * Brings the Calendar's displayname.
 *
 * @param data 	The DavData used to get name.
 *
 * @return 		The Calendar display name in a string. The user must free it.
 */
char* dav_get_displayname(DavData *data);

/**
 * Test the server uri and report if it's valid or not.
 *
 * @param data 	DavData object with the uri info.
 *
 * @return 1 if data have a valid uri
 */
int dav_is_valid_server(DavData *data);

/**
 * Brings the Calendar data
 *
 * @param data 	The DavData used to get the calendar data.
 *
 * @return 		The calendar data in a string. The user must free it.
 */
char* dav_getall_object(DavData *data);

#endif /* CALDAV_H */
