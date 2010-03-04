#ifndef IO_H
#define IO_H

/**
 * Init the XDG subsystem.
 */
void xdg_init();

/**
 * Uninit the XDG subsytem.
 */
void xdg_uninit();

/*
 * Brings the username to be used from $XDG_CONFIG_DIR/Chronus/account
 * This file must have this format:
 * username
 * password
 *
 * TODO: change this to xml and support more than one account.
 *
 * @return The username. User must free this string.
 */
char* config_get_user();

/**
 * Brings the password from $XDG_CONFIG_DIR/Chronus/account
 *
 * @return The user password. User must free this string.
 */
char* config_get_password();

/**
 * Brings the calendar url from $XDG_CONFIG_DIR/Chronus/account
 *
 * @return The user calendar url. User must free this string.
 */
char* config_get_calendar_url();

#endif /* IO_H */
