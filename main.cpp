#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <functional>

struct input_exception : std::runtime_error {
    explicit input_exception(const std::string &s) : std::runtime_error(s) {}
};

struct solver {
    const int MAX_SIZE = 100'000;
    const int MOVES = 4;
    const std::vector<int> dx{1, 0, -1, 0};
    const std::vector<int> dy{0, -1, 0, 1};

    int n{}, m{};
    std::vector<std::string> field;
    std::pair<int, int> start;
    std::vector<std::vector<int>> used;

    solver() = default;

    void read() {
        std::cin >> n >> m;
        if (n < 1 || m < 1 ||
            n * 1LL * m > MAX_SIZE) {
            throw input_exception("invalid size of field: "
                                  "n = " + std::to_string(n) +
                                  ", m = " + std::to_string(m) +
                                  " when should be n, m is natural and "
                                  "1 <= n * m <= " + std::to_string(MAX_SIZE));
        }

        field.resize(n);
        for (auto &s: field) {
            std::cin >> s;
            if (s.size() != m) {
                throw input_exception("field size is not n x m");
            }
            for (const auto &c: s) {
                if (c != '0' && c != '1') {
                    throw input_exception("field has unexpected symbol: " + std::string(1, c));
                }
            }
        }

        std::cin >> start.first >> start.second;
        if (!(1 <= start.first && start.first <= n) ||
            !(1 <= start.second && start.second <= m)) {
            throw input_exception("invalid coordinates of start cell: "
                                  "x = " + std::to_string(start.first) +
                                  ", y = " + std::to_string(start.second) +
                                  " when should be 1 <= x <= n, 1 <= y <= m");
        }
        --start.first, --start.second;  // [0, n), [0, m)
        if (field[start.first][start.second] != '0') {
            throw input_exception("start cell is not empty");
        }
    }

    bool can_go(std::pair<int, int> v) {
        return 0 <= v.first && v.first < n &&
               0 <= v.second && v.second < m &&
               field[v.first][v.second] == '0' &&
               !used[v.first][v.second];
    };

    void dfs(std::pair<int, int> v) {
        used[v.first][v.second] = 1;
        for (int dir = 0; dir < MOVES; ++dir) {
            std::pair<int, int> next = {v.first + dx[dir],
                                        v.second + dy[dir]};
            if (can_go(next)) {
                dfs(next);
            }
        }
    }

    void solve() {
        used.resize(n);
        for (auto &v: used) {
            v.assign(m, 0);
        }
        dfs(start);

        auto go = [&](int x, int y) {
            if (!(0 <= x && x < n) ||
                !(0 <= y && y < m)) {
                throw std::logic_error("bad output coordinates: " + std::to_string(x) + " " + std::to_string(y));
            }
            std::cout << x + 1 << " " << y + 1 << "\n";  // [1, n], [1, m]
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
};

int main(int argc, char *argv[]) {
    try {
        std::string input_file, output_file;
        if (argc == 1) {
            input_file = "tests/normal_test.in";
            output_file = "tests/normal_test.out";
        } else if (argc == 3) {
            input_file = argv[1];
            output_file = argv[2];
        } else {
            throw input_exception("Usage: ./program <input-file> <output-file>");
        }

        if (!freopen(input_file.c_str(), "r", stdin)) {
            throw std::runtime_error("Unable to open file '" + input_file + "'");
        }
        if (!freopen(output_file.c_str(), "w", stdout)) {
            throw std::runtime_error("Unable to open file '" + output_file + "'");
        }

        solver my_solver;
        my_solver.read();
        my_solver.solve();
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
}
