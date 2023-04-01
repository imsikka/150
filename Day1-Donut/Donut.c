#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define PI 3.14159265358979323846

char framebuffer[HEIGHT][WIDTH];

void clear_framebuffer() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            framebuffer[i][j] = ' ';
        }
    }
}

void plot(int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        framebuffer[y][x] = c;
    }
}

void render_frame(double theta) {
    int i, j;
    double sin_theta = sin(theta);
    double cos_theta = cos(theta);

    clear_framebuffer();

    for (i = 0; i < 360; i += 5) {
        double sin_i = sin(i * PI / 180.0);
        double cos_i = cos(i * PI / 180.0);

        for (j = 0; j < 360; j += 5) {
            double sin_j = sin(j * PI / 180.0);
            double cos_j = cos(j * PI / 180.0);

            double x = cos_j * (2 + cos_i);
            double y = sin_j * (2 + cos_i);
            double z = sin_i;

            double new_x = cos_theta * x + sin_theta * z;
            double new_z = -sin_theta * x + cos_theta * z;
            double new_y = y;

            int xp = (int)(WIDTH / 2 + 20 * new_x / (5 + new_z));
            int yp = (int)(HEIGHT / 2 + 10 * new_y / (5 + new_z));

            plot(xp, yp, '.');
        }
    }

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            putchar(framebuffer[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    double theta = 0;

    while (1) {
        render_frame(theta);

        theta += 0.05;
        if (theta > 2 * PI) {
            theta -= 2 * PI;
        }

        usleep(30000);
    }

    return 0;
}

