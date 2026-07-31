#include <iostream>
#include <vector>

using namespace std;

// Calculate how many balls land at each position recursively
void calculate_balls(int depth, long long num_balls, int pos, int target_depth, vector<long long>& counts) {
    if (depth == target_depth) {
        counts[pos] = num_balls;
        return;
    }

    if (num_balls == 0) return;

    // Left subtree gets (num_balls + 1) / 2 balls
    // Right subtree gets num_balls / 2 balls
    long long left_balls = (num_balls + 1) / 2;
    long long right_balls = num_balls / 2;

    calculate_balls(depth + 1, left_balls, pos * 2, target_depth, counts);
    calculate_balls(depth + 1, right_balls, pos * 2 + 1, target_depth, counts);
}

int main() {
    int D;
    long long n;
    cin >> D >> n;

    // Number of leaf nodes
    int num_leaves = (1 << (D - 1));

    // Find where the nth ball lands
    int final_pos = 1;
    long long temp_n = n;

    for (int level = 0; level < D - 1; level++) {
        if (temp_n % 2 == 1) {
            final_pos = final_pos * 2;
            temp_n = (temp_n + 1) / 2;
        } else {
            final_pos = final_pos * 2 + 1;
            temp_n = temp_n / 2;
        }
    }

    cout << final_pos << endl;

    // Calculate how many balls land at each leaf
    vector<long long> ball_counts(num_leaves * 2, 0); // Use larger array for indexing
    calculate_balls(0, n, 1, D - 1, ball_counts);

    // Output leaf states (odd count = on, even count = off)
    int first_leaf = (1 << (D - 1));
    for (int i = 0; i < num_leaves; i++) {
        if (i > 0) cout << " ";
        cout << (ball_counts[first_leaf + i] % 2);
    }
    cout << endl;

    return 0;
}
