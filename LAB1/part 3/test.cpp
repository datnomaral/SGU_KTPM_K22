#include <iostream>
#include <sstream>
#include <vector>
#include <tuple>
#include <cmath>
#include <string>
using namespace std;

// === Hàm giải phương trình gốc ===
int solveQuartic(double a, double b, double c, double x[])
{
    if (a == 0 && b == 0 && c == 0)
    {
        return -1; // vô số nghiệm
    }
    if (a == 0 && b == 0)
    {
        return 0; // vô nghiệm
    }
    if (a == 0)
    {
        double y = -c / b;
        if (y < 0)
            return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }
    double delta = b * b - 4 * a * c;
    if (delta < 0)
        return 0;
    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);
    int count = 0;
    if (y1 >= 0)
    {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1)
    {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

// === Hàm chạy test case ===
bool runTest(double a, double b, double c, const string &expected)
{
    double x[4];
    int n = solveQuartic(a, b, c, x);
    stringstream ss;

    if (n == -1)
    {
        ss << "Infinite solutions.";
    }
    else if (n == 0)
    {
        ss << "No solution.";
    }
    else
    {
        ss << "The equation has " << n << " real solution(s): ";
        for (int i = 0; i < n; i++)
        {
            ss << round(x[i] * 100000) / 100000 << " "; // làm tròn 5 chữ số
        }
    }

    string result = ss.str();

    cout << "Input: (" << a << ", " << b << ", " << c << ")\n";
    cout << "Expected: " << expected << "\n";
    cout << "Actual:   " << result << "\n";

    if (result.find(expected) != string::npos)
    {
        cout << "Result: ✅ PASS\n\n";
        return true;
    }
    else
    {
        cout << "Result: ❌ FAIL\n\n";
        return false;
    }
}

// === Main test ===
int main()
{
    vector<tuple<double, double, double, string>> tests = {
    {0, 0, 0, "Infinite solutions."},
    {0, 0, 1, "No solution."},
    {0, 1, 1, "No solution."},
    {0, 1, 0, "The equation has 2 real solution(s):"},
    {0, 1, -10, "The equation has 2 real solution(s):"},
    {1, 2, 2, "No solution."},
    {1, -2, 1, "The equation has 2 real solution(s):"},
    {1, -5, 6, "The equation has 4 real solution(s):"},
    {1, -2, 1, "The equation has 2 real solution(s):"},
    {1, 0, 0, "The equation has 2 real solution(s):"},
    {1, -4, 4, "The equation has 2 real solution(s):"}
    };

    int passed = 0;
    for (int i = 0; i < tests.size(); i++)
    {
        auto [a, b, c, expected] = tests[i];
        if (runTest(a, b, c, expected))
        {
            passed++;
        }
    }

    cout << "Summary: " << passed << "/" << tests.size() << " test cases passed.\n";
    return 0;
}
