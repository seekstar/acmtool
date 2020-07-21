int week[10010][14][33]; //0 is Sunday, 1 is Monday, 2 is Tuesday
int have[10010][14];

inline bool IsLeap(int n) {
    return (n % 4 == 0 && n % 100 != 0) || n % 400 == 0;
}
const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
inline int Have(int year, int month) {
    return month != 2 ? days[month] : (IsLeap(year) ? 29 : 28);
}
inline bool Valid(int y, int m, int d) {
    return 1600 <= y && y <= 9999 && 1 <= m && m <= 12 && 1 <= d && d <= have[y][m];
}
int Week(int order[], char ys[], char ms[], char ds[]) {
    int y = order[ys[3]] * 1000 + order[ys[2]] * 100 + order[ys[1]] * 10 + order[ys[0]];
    int m = order[ms[1]] * 10 + order[ms[0]];
    int d = order[ds[1]] * 10 + order[ds[0]];
    return Valid(y, m, d) ? week[y][m][d] : -1;
}
void Init() {
	int last = 0;
    for (int year = 1; year <= 10000; ++year) {
        for (int month = 1; month <= 12; ++month) {
            have[year][month] = Have(year, month);
            for (int day = 1; day <= have[year][month]; ++day) {
                last = week[year][month][day] = Add(last + 1, 7);
            }
        }
    }
}

