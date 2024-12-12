#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Point {
    double x;
    double y;
};

double findClosestPair(vector<Point> &points, int left, int right) {
    auto distance = [](const Point &a, const Point &b) {
        return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    };
    if (right - left <= 3) {
        // Brute force
        double minDist = numeric_limits<double>::max();
        for (int i = left; i <= right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                minDist = min(minDist, distance(points[i], points[j]));
            }
        }
        return minDist;
    }

    int mid = (left + right) / 2;
    double minLeft = findClosestPair(points, left, mid);
    double minRight = findClosestPair(points, mid + 1, right);
    double minDist = min(minLeft, minRight);

    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - points[mid].x) < minDist) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), [](const Point &a, const Point &b) {
        return a.y < b.y;
    });

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }

    return minDist;
}

int main() {
    int numTests;
    cin >> numTests;

    while (numTests--) {
        int numPoints;
        cin >> numPoints;

        vector<Point> points(numPoints);
        for (int i = 0; i < numPoints; ++i) cin >> points[i].x >> points[i].y;

        sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
            return a.x < b.x;
        });

        double minDistance = findClosestPair(points, 0, points.size() - 1);
        cout << setprecision(6) << fixed << minDistance << endl;
    }
    return 0;
}