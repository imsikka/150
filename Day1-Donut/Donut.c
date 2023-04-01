#include <stdio.h>
#include <math.h>
#include <graphics.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int i, j;
    float theta, phi, x, y, z, r1 = 2, r2 = 5;
    float sintheta, costheta, sinphi, cosphi, dist;
    int max_x = getmaxx(), max_y = getmaxy();
    float screen_x, screen_y, scale_x = max_x / 2, scale_y = max_y / 2;
    int mid_x = max_x / 2, mid_y = max_y / 2;
    float surface_normal, light_source_x = 0, light_source_y = 0, light_source_z = -50;
    float dx1, dy1, dx2, dy2, dx3, dy3;
    float normal_x, normal_y, normal_z, length;

    for (phi = 0; phi <= 2 * M_PI; phi += 0.1)
    {
        for (theta = 0; theta <= 2 * M_PI; theta += 0.1)
        {
            sintheta = sin(theta);
            costheta = cos(theta);
            sinphi = sin(phi);
            cosphi = cos(phi);
            x = r2 + r1 * costheta * cosphi;
            y = r1 * sintheta;
            z = r2 + r1 * costheta * sinphi + 50;

            dx1 = x - (r2 + r1 * cos(phi) * cos(theta));
            dy1 = y - (r1 * sin(theta));
            dx2 = x - (r2 + r1 * cos(phi + 0.1) * cos(theta));
            dy2 = y - (r1 * sin(theta));
            dx3 = x - (r2 + r1 * cos(phi) * cos(theta + 0.1));
            dy3 = y - (r1 * sin(theta + 0.1));

            normal_x = dy1 * dx2 - dy2 * dx1;
            normal_y = dx1 * dy3 - dx3 * dy1;
            normal_z = dx1 * dx2 + dy1 * dy2 + dx3 * dy3;
            length = sqrt(normal_x * normal_x + normal_y * normal_y + normal_z * normal_z);

            normal_x /= length;
            normal_y /= length;
            normal_z /= length;

            surface_normal = normal_x * light_source_x + normal_y * light_source_y + normal_z * light_source_z;

            if (surface_normal > 0)
            {
                screen_x = mid_x + scale_x * x / z;
                screen_y = mid_y + scale_y * y / z;

                putpixel(screen_x, screen_y, WHITE);
            }
        }
    }

    getch();
    closegraph();
    return 0;
}
