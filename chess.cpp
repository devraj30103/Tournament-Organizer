#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <iomanip>
using namespace std;

struct Player {
    string name;
    int score = 0;
    bool eliminated = false;
};

void shufflePlayers(vector<Player>& players) {
    random_device rd;
    mt19937 g(rd());
    shuffle(players.begin(), players.end(), g);
}

void displayScoreboard(const vector<Player>& players) {
    cout << "\n?? Scoreboard:\n";
    cout << left << setw(20) << "Player" << "Score\n";
    cout << "--------------------------\n";
    for (const auto& p : players) {
        if (!p.eliminated)
            cout << left << setw(20) << p.name << p.score << "\n";
    }
}

void knockoutTournament(vector<Player> players) {
    cout << "\n--- Knockout Tournament ---\n";
    int round = 1;

    while (players.size() > 1) {
        cout << "\n?? Round " << round++ << ":\n";
        shufflePlayers(players);
        vector<Player> winners;

        for (size_t i = 0; i < players.size(); i += 2) {
            if (i + 1 < players.size()) {
                cout << players[i].name << " vs " << players[i + 1].name << "\n";
                string winner;
                cout << "Enter winner: ";
                getline(cin, winner);

                if (winner == players[i].name) {
                    winners.push_back(players[i]);
                    winners.back().score++;
                } else if (winner == players[i + 1].name) {
                    winners.push_back(players[i + 1]);
                    winners.back().score++;
                } else {
                    cout << "Invalid input. Randomly choosing winner.\n";
                    winners.push_back(players[i]);
                    winners.back().score++;
                }
            } else {
                cout << players[i].name << " gets a BYE.\n";
                players[i].score++;
                winners.push_back(players[i]);
            }
        }

        players = winners;
        displayScoreboard(players);
    }

    cout << "\n?? Tournament Winner: " << players[0].name << " with " << players[0].score << " points\n";
}

bool compareByScore(const Player& a, const Player& b) {
    return a.score > b.score;
}

void swissTournament(vector<Player>& players, int rounds) {
    cout << "\n--- Swiss Tournament (" << rounds << " Rounds) ---\n";

    for (int r = 1; r <= rounds; ++r) {
        cout << "\n?? Round " << r << " Pairings:\n";
        sort(players.begin(), players.end(), compareByScore);

        vector<bool> paired(players.size(), false);

        for (size_t i = 0; i < players.size(); ++i) {
            if (paired[i]) continue;

            size_t j = i + 1;
            while (j < players.size() && paired[j]) ++j;

            if (j < players.size()) {
                cout << players[i].name << " vs " << players[j].name << "\n";
                string winner;
                cout << "Enter winner (or 'draw'): ";
                getline(cin, winner);

                if (winner == players[i].name) players[i].score++;
                else if (winner == players[j].name) players[j].score++;
                else if (winner == "draw") {
                    // 0.5 logic can be added later
                    cout << "Draw (no points awarded)\n";
                } else {
                    cout << "Invalid. No points.\n";
                }

                paired[i] = paired[j] = true;
            } else {
                cout << players[i].name << " gets a BYE.\n";
                players[i].score++;
                paired[i] = true;
            }
        }

        displayScoreboard(players);
    }

    // Print final standings
    sort(players.begin(), players.end(), compareByScore);
    cout << "\n?? Final Standings:\n";
    displayScoreboard(players);
    cout << "\n?? Winner: " << players[0].name << " with " << players[0].score << " points\n";
}

int main() {
    int n;
    cout << "Enter number of players: ";
    cin >> n;
    cin.ignore();

    vector<Player> players(n);
    cout << "Enter player names:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Player " << i + 1 << ": ";
        getline(cin, players[i].name);
    }

    int choice;
    cout << "\nChoose Tournament Format:\n";
    cout << "1. Knockout\n2. Swiss\nEnter choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        knockoutTournament(players);
    } else if (choice == 2) {
        int rounds;
        cout << "Enter number of Swiss rounds: ";
        cin >> rounds;
        cin.ignore();
        swissTournament(players, rounds);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}

