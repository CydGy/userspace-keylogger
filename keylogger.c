#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#include "kbduskeymap.h"

#define KEY_PRESS 1

int main (int argc, char **argv)
{
    int fd;
    struct input_event ev;
    int shiftKeyPressed = 0;

    if (argc < 2) {
        printf("usage: %s <device>\n", argv[0]);
        return 1;
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("Couldn't open input device");
        return 1;
    }

    setbuf(stdout, NULL);

    while (1) {
        read(fd, &ev, sizeof(struct input_event));

        if (ev.type == 1)
        {
            if (ev.code == 42 || ev.code == 54) {
                if (ev.value == KEY_PRESS)
                    shiftKeyPressed = 1;
                else
                    shiftKeyPressed = 0;
            }

            if (ev.value == KEY_PRESS) {
                if (shiftKeyPressed == 0)
                    printf("%s", keymap[ev.code]);
                else
                    printf("%s", keymapShiftActivated[ev.code]);
            }
        }

    }
}
