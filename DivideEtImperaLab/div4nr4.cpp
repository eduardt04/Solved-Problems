#include <fstream>
#include <cmath>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("input.in");
ofstream fout("output.out");

struct Point {
    int x, y;
    Point(int a, int b) : x(a), y(b) {};
};
/* punctele sortate dupa x si dupa y */
vector<Point> p_x, p_y;

bool xcompare(const Point &a, const Point &b) {
    return a.x < b.x;
}

bool ycompare(const Point &a, const Point &b) {
    return a.y < b.y;
}

float distance(const Point &a, const Point &b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

float small_Case(vector<Point> v, int n) {
    float dmin = INT_MAX;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++) 
            dmin = min(dmin, distance(v[i], v[j]));
    return dmin;
}

float checkClose(vector<Point> checks, int size, float d) {
    float dmin = d;
    for(int i = 0; i < size; i++)
        for(int j = i + 1; j < size && (checks[j].y - checks[i].y) < dmin; j++ )
            dmin = min(dmin, distance(checks[i], checks[j]));
    return dmin;
}

float smallest_Dist(vector<Point> vx, vector<Point> vy, int n) {
    if(n <= 3) {
        return small_Case(vx, n);
    }

    int mid = n/2;
    Point axis_point = vx[mid];
    
    vector<Point> left_side, right_side;
    for(int i = 0; i < n; i++)
        if(vy[i].x <= axis_point.x)
            left_side.push_back(vy[i]);
        else right_side.push_back(vy[i]);
    
    float smallest_dist_left = smallest_Dist(vx, left_side, mid);
    float smallest_dist_right = smallest_Dist(vector<Point>(vx.begin() + mid, vx.end()), right_side, n - mid);
    float dmin = min(smallest_dist_left, smallest_dist_right);

    vector<Point> checks;
    for(int i = 0; i < n; i++)
        if(abs(vy[i].x - axis_point.x) < dmin)
            checks.push_back(vy[i]);

    return min(dmin, checkClose(checks, checks.size(), dmin));
}

int main() {
    int n, i, x, y;
    fin>>n;
    for(i = 1; i <= n; i++) {
        fin>>x>>y;
        p_x.push_back(Point(x, y));
        p_y.push_back(Point(x, y));
    }
    sort(p_x.begin(), p_x.end(), xcompare);
    sort(p_y.begin(), p_y.end(), ycompare);
    fout<<smallest_Dist(p_x, p_y, n);       
    return 0;
}