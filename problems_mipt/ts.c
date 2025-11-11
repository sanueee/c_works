#include <stdio.h>

struct point_t {
    int x, y;
};
struct triangle_t {
    struct point_t pts[3];
};

int double_area(struct triangle_t* tr);

int main() {
    struct triangle_t t;
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &t.pts[i].x, &t.pts[i].y);
    }
    printf("%d", double_area(&t));
    return 0;
}

int double_area(struct triangle_t* tr) {
    // tr->pts[0].x tr->pts[1].x tr->pts[2].x tr->pts[0].y tr->pts[1].y tr->pts[2].y
    int det = tr->pts[0].x * (tr->pts[1].y - tr->pts[2].y) +
              tr->pts[1].x * (tr->pts[2].y - tr->pts[0].y) +
              tr->pts[2].x * (tr->pts[0].y - tr->pts[1].y);
    return (det >= 0) ? det: -det;
}