#include  "backtrack.h"

//这道题重点在于Hierholzer算法而不是回溯算法

class Solution {
    bool findRoute(vector<string>& result, unordered_map<string, map<string, int>>& ticketMap, int ticketCount) {
        if (ticketCount == 0) return true;
        map<string, int>& end_list=ticketMap[result.back()];
        for (auto& end : end_list) {
            if (end.second > 0) {
                end.second--;
                result.push_back(end.first);
                if (findRoute(result, ticketMap, ticketCount - 1)) return true;
                result.pop_back();
                end.second++;
            }
        }
        return false;
    }

    void findRouteHierholzer(vector<string>& result, unordered_map<string, map<string, int>>& ticketMap,string& start) {
        if (ticketMap[start].empty()) {
            result.push_back(start);
            return;
        }
        auto it = ticketMap[start].begin();
        string next = it->first;
        it->second--;
        if (it->second == 0) ticketMap[start].erase(it);
        findRouteHierholzer(result, ticketMap, next);
        findRouteHierholzer(result,ticketMap,start);
    }

    void findRouteHierholzerBest(vector<string>& result, unordered_map<string, map<string, int>>& ticketMap,string& start) {
        auto& destinations=ticketMap[start];
        while (!destinations.empty()) {
            auto it = destinations.begin();
            string next = it->first;
            if (--(it->second) == 0) destinations.erase(it);
            findRouteHierholzer(result, ticketMap, next);
        }
        result.push_back(start);
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        vector<string> result;
        unordered_map<string, map<string, int>> ticketMap;
        int ticketCount=tickets.size();
        for (auto& ticket : tickets) {
            ticketMap[ticket[0]][ticket[1]]++;
        }
        result.push_back("JFK");
        findRoute(result, ticketMap, ticketCount);
        return result;
    }

    vector<string> findItineraryHierholzer(vector<vector<string>>& tickets) {
        vector<string> result;
        unordered_map<string, map<string, int>> ticketMap;
        for (auto& ticket : tickets) {
            ticketMap[ticket[0]][ticket[1]]++;
        }
        string start = "JFK";
        findRouteHierholzer(result,ticketMap,start);
        reverse(result.begin(), result.end());
        return result;
    }
};
