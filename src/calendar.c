#include <stdio.h>
#include <glib.h>
#include <gcal.h>

#include "calendar.h"

CalendarData* calendar_new()
{
	CalendarData *cal_dat;

	cal_dat = g_new(CalendarData, 1);

	if (!cal_dat)
		return NULL;

	cal_dat->gc_res = gcal_construct(GCALENDAR);

	return cal_dat;
}

void calendar_destroy(CalendarData *cal_dat)
{
	gcal_destroy(cal_dat->gc_res);
	g_free(cal_dat);
}

int calendar_login(CalendarData *cal_dat, char *username, char *password)
{

	if (gcal_get_authentication(cal_dat->gc_res, username, password)) {
		printf("Failed to autenticate\n");

		return -1;
	}

	return 0;
}
