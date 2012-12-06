#ifndef ERROR_H
#define ERROR_H

#define handle_error(S) { if (S != APR_SUCCESS) { goto error; } }
#define handle_and_display_error(S) { if (S != APR_SUCCESS) { char buf[256]; apr_strerror(S, buf, sizeof(buf)); printf("Error: %s\n", buf); goto error; } }

#endif
