#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

Point p0;
bool compare(Point a, Point b) {
    int o = orientation(p0, a, b);
    if (o == 0) {
        return (a.x - p0.x) * (a.x - p0.x) + (a.y - p0.y) * (a.y - p0.y) <
               (b.x - p0.x) * (b.x - p0.x) + (b.y - p0.y) * (b.y - p0.y);
    }
    return o == 2;
}

vector<Point> convexHull(vector<Point>& points) {
    int n = points.size();
    if (n < 3) return {};

    int ymin = points[0].y, minIdx = 0;
    for (int i = 1; i < n; i++) {
        int y = points[i].y;
        if (y < ymin || (y == ymin && points[i].x < points[minIdx].x)) {
            ymin = y;
            minIdx = i;
        }
    }
    swap(points[0], points[minIdx]);
    p0 = points[0];

    sort(points.begin() + 1, points.end(), compare);

    vector<Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int i = 2; i < n; i++) {
        while (hull.size() > 1 && orientation(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) != 2) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }
    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    vector<Point> hull = convexHull(points);
    cout << "Convex Hull points:\n";
    for (auto p : hull) cout << "(" << p.x << ", " << p.y << ")\n";
    return 0;
}