#ifndef APP_H
#define APP_H

#include "../Server/Server.h"

typedef enum {
    TRY_AGAIN, APP_OK
} EN_appError_t;

EN_appError_t startApp(void);

#endif
