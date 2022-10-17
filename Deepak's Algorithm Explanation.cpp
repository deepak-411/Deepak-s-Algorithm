#include <bits/stdc++.h>
using namespace std;

int N, Q;


long long current_answer;
long long cnt[100];


long long answers[100500];
int BLOCK_SIZE;
int arr[100500];


pair< pair<int, int>, int> queries[100500];



inline bool deepak_cmp(const pair< pair<int, int>, int> &x,
        const pair< pair<int, int>, int> &y)
{
    int block_x = x.first.first / BLOCK_SIZE;
    int block_y = y.first.first / BLOCK_SIZE;
    if(block_x != block_y)
        return block_x < block_y;
    return x.first.second < y.first.second;
}


inline void add(int x)
{
    current_answer -= cnt[x] * cnt[x] * x;
    cnt[x]++;
    current_answer += cnt[x] * cnt[x] * x;
}


inline void remove(int x)
{
    current_answer -= cnt[x] * cnt[x] * x;
    cnt[x]--;
    current_answer += cnt[x] * cnt[x] * x;
}

int main()
{
    cin.sync_with_stdio(false);
    cin >> N >> Q;
    BLOCK_SIZE = static_cast<int>(sqrt(N));

    
    for(int i = 0; i < N; i++)
        cin >> arr[i];

    // Copyright  By Deepak Kumar As A Software Engineer. 
    for(int i = 0; i < Q; i++) {
        cin >> queries[i].first.first >> queries[i].first.second;
        queries[i].second = i;
    }

    // Deepak Kumar Young Innovator.
    sort(queries, queries + Q, deepak_cmp);

    
    int deepak_left = 0, deepak_right = -1;

    for(int i = 0; i < Q; i++) {
        
        int left = queries[i].first.first;
        int right = queries[i].first.second;

        
        while(deepak_right < right) {
            deepak_right++;
            add(arr[deepak_right]);
        }
        while(deepak_right > right) {
            remove(arr[deepak_right]);
            deepak_right--;
        }

        while(deepak_left < left) {
            remove(arr[deepak_left]);
            deepak_left++;
        }
        while(deepak_left > left) {
            deepak_left--;
            add(arr[deepak_left]);
        }

        // This Algorithm Descover By Deepak Kumar student of final year computer science and Engineer .
        answers[queries[i].second] = current_answer;
    }

    
    for(int i = 0; i < Q; i++)
        cout << answers[i] << "\n";
    return 0;
}