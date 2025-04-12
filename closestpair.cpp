#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Point {
    double x, y;
};

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareX(Point a, Point b) { return a.x < b.x; }
bool compareY(Point a, Point b) { return a.y < b.y; }

pair<Point, Point> bruteForce(vector<Point>& points, int left, int right, double& minDist) {
    pair<Point, Point> res;
    minDist = 1e9;
    for (int i = left; i < right; i++) {
        for (int j = i + 1; j <= right; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
                res = {points[i], points[j]};
            }
        }
    }
    return res;
}

pair<Point, Point> stripClosest(vector<Point>& strip, double& d) {
    pair<Point, Point> res;
    sort(strip.begin(), strip.end(), compareY);
    for (int i = 0; i < strip.size(); i++) {
        for (int j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; j++) {
            double dist = distance(strip[i], strip[j]);
            if (dist < d) {
                d = dist;
                res = {strip[i], strip[j]};
            }
        }
    }
    return res;
}

pair<Point, Point> closestPairUtil(vector<Point>& points, int left, int right, double& d) {
    if (right - left <= 3) {
        return bruteForce(points, left, right, d);
    }

    int mid = (left + right) / 2;
    Point midPoint = points[mid];

    double dl, dr;
    pair<Point, Point> pl = closestPairUtil(points, left, mid, dl);
    pair<Point, Point> pr = closestPairUtil(points, mid + 1, right, dr);

    pair<Point, Point> bestPair;
    if (dl < dr) {
        d = dl;
        bestPair = pl;
    } else {
        d = dr;
        bestPair = pr;
    }

    vector<Point> strip;
    for (int i = left; i <= right; i++) {
        if (abs(points[i].x - midPoint.x) < d)
            strip.push_back(points[i]);
    }

    pair<Point, Point> stripPair = stripClosest(strip, d);
    if (distance(stripPair.first, stripPair.second) < d) {
        bestPair = stripPair;
        d = distance(stripPair.first, stripPair.second);
    }

    return bestPair;
}

pair<Point, Point> closestPair(vector<Point>& points, double& minDist) {
    sort(points.begin(), points.end(), compareX);
    return closestPairUtil(points, 0, points.size() - 1, minDist);
}

int main() {
    vector<Point> points = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
    double minDist;
    pair<Point, Point> result = closestPair(points, minDist);
    cout << "Closest pair: (" << result.first.x << ", " << result.first.y << ") and ("
         << result.second.x << ", " << result.second.y << ")\n";
    cout << "Distance: " << minDist << endl;
    return 0;
}
