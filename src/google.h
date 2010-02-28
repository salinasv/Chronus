#ifndef GOOGLE_H
#define GOOGLE_H

typedef struct _CalendarData
{
	struct gcal_resource *gc_res;
}CalendarData;

CalendarData* calendar_new();
void calendar_destroy(CalendarData *cal_dat);
int calendar_login(CalendarData *cal_dat, char *username, char *password);

#endif /* GOOGLE_H */
