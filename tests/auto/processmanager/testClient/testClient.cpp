/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

const int kBufSize = 100;

ssize_t writeline(char *buffer, int len)
{
    char *b = buffer;
    while ( len > 0 ) {
        ssize_t r = write(STDOUT_FILENO, b, len);
        if (r < 0)
            return r;
        b += r;
        len -= r;
    }
    return 0;
}

ssize_t readline(char *buffer, int max_len)
{
    int len = 0;
    char c = 0;
    while (len < max_len && c != '\r' && c != '\n') {
        ssize_t count = read(STDIN_FILENO, &c, 1);
        if (count <= 0)
            return count;
        *buffer++ = c;
        len++;
    }
    *buffer = 0;
    return len;
}

static char tough[] = "tough\n";

int
main(int argc, char **argv)
{
    for (int i = 1 ; i < argc ; i++) {
        if (!strcmp(argv[i], "-noterm")) {
            struct sigaction action;
            memset(&action, 0, sizeof(action));
            action.sa_handler=SIG_IGN;
            if (sigaction(SIGTERM, &action, NULL) < 0) {
                perror("Unable ignore SIGTERM");
                return 1;
            }
            if (writeline(tough, strlen(tough)) < 0)
                return 3;
        }
    }
    char buffer[kBufSize+1];

    while (1) {
        ssize_t count = readline(buffer, kBufSize);
        if (count < 0)
            return 1;
        if (count == 0)
            return 0;

        if (strncmp("stop", buffer, 4) == 0)
            return 0;
        if (strncmp("crash", buffer, 5) == 0)
            return 2;

        ssize_t result = writeline(buffer, count);
        if (result < 0)
            return 2;
    }
}