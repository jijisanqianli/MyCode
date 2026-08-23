#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    void heapify(vector<pair<int, int>>& heap, int i);

    vector<int> topKFrequent_bucket(vector<int>& nums, int k) {
        unordered_map<int, int> num_freq;
        vector<int> result;
        result.reserve(k);
        for (int i = 0; i < nums.size(); i++) {
            num_freq[nums[i]]++;
        }
        vector<vector<int>> bucket=vector<vector<int>>(nums.size()+1);
        for (auto& p : num_freq) {
            bucket[p.second].push_back(p.first);
        }
        for (int i = bucket.size() - 1; i >= 0 && result.size() < k; i--) {
            for (int j = 0; j < bucket[i].size() && result.size() < k; j++) {
                result.push_back(bucket[i][j]);
            }
        }
        return result;
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> num_freq;
        for (int i = 0; i < nums.size(); i++) {
            num_freq[nums[i]]++;
        }
        vector<pair<int, int>> small_heap;
        small_heap.reserve(k);
        for (auto& p : num_freq) {
            if (small_heap.size() < k) {
                small_heap.push_back(p);
                if (small_heap.size() == k) {
                    for (int i = k / 2 - 1; i >= 0; i--) {
                        heapify(small_heap, k, i);
                    }
                }
            }else if (p.second > small_heap[0].second) {
                small_heap[0] = p;
                heapify(small_heap, k,0);
            }
        }
        vector<int> result;
        for (auto& p : small_heap) {
            result.push_back(p.first);
        }
        return result;
    }

    void heapify(vector<pair<int, int>>& heap, int k, int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < k && heap[left].second < heap[smallest].second) smallest = left;
        if (right < k && heap[right].second < heap[smallest].second) smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(heap,k, smallest);
        }
    }
};
