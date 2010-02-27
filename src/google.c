#include <stdio.h>
#include <gcal.h>

int google_login(char *username, char *password)
{
	struct gcal_resource *gc_res;

	gc_res = gcal_construct(GCALENDAR);

	if (gcal_get_authentication(gc_res, username, password)) {
		printf("Failed to autenticate\n");
		
		return -1;
	}

	return 0;
}
