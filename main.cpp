#include <bits/stdc++.h>

int main() {
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> field(n);
    for (auto &s: field) {
        std::cin >> s;
    }
    std::pair<int, int> start;
    std::cin >> start.first >> start.second;
    --start.first, --start.second;  // [0, n), [0, m)

    const int MOVES = 4;
    const std::vector<int> dx{1, 0, -1, 0};
    const std::vector<int> dy{0, -1, 0, 1};

    std::vector<std::vector<int>> used(n, std::vector<int> (m));
    auto can_go = [&n, &m, &field, &used](std::pair<int, int> v) {
        return 0 <= v.first && v.first < n &&
               0 <= v.second && v.second < m &&
               field[v.first][v.second] == '0' &&
               !used[v.first][v.second];
    };
    std::function<void(std::pair<int, int>)> dfs = [&dfs, &dx, &dy, &used, &can_go](std::pair<int, int> v) {
        used[v.first][v.second] = 1;
        for (int dir = 0; dir < MOVES; ++dir) {
            std::pair<int, int> next = {v.first + dx[dir],
                                        v.second + dy[dir]};
            if (can_go(next)) {
                dfs(next);
            }
        }
    };
    dfs(start);

    auto print_used = [&used]() {
        for (const auto &v: used) {
            for (const int &x: v) {
                std::cout << x << " ";
            }
            std::cout << "\n";
        }
    };

    auto go = [](int x, int y) {
        std::cout << x << " " << y << "\n";
        exit(0);
    };
    for (int i = 0; i < n; ++i) {
        if (used[i][0]) {
            go(i, 0);
        }
        if (used[i][m - 1]) {
            go(i, m - 1);
        }
    }
    for (int j = 0; j < m; ++j) {
        if (used[0][j]) {
            go(0, j);
        }
        if (used[n - 1][j]) {
            go(n - 1, j);
        }
    }
    std::cout << "-1 -1\n";
}
