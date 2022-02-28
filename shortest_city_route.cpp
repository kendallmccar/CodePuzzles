// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

// Find all routes, and identify the fastest route, between connected cities
// Route may not exist

class City {
public:
    City() = default;
    ~City() = default;
    std::map<City*, int> connected_cities_; // the value is the distance
    std::string name_;
};

class Route {
public:
    Route() : distance_(0) {}
    ~Route() = default;
    std::vector<City*> route_;
    int distance_;
    bool operator<(Route const& other) { return distance_ < other.distance_; }
};

class RouteFinder {
public:
    RouteFinder() = default;
    ~RouteFinder() = default;

    bool FindRoutes(City* start, City* end, Route in_progress_route) {
        // add start point to current in progress route
        in_progress_route.route_.push_back(start);
        // if the start and end are the same, the route is complete
        if (start->name_ == end->name_) {
            // add to the list of completed routes
            complete_routes_.push_back(std::move(in_progress_route));
            return true;
        }
        // else if the end is not reached, try routing through each connected city
        bool success = false;
        for (auto& pair : start->connected_cities_) {
            in_progress_route.distance_ += pair.second;
            // for each connected city, add the distance 
            success = (FindRoutes(pair.first, end, in_progress_route) || success);
        }
        // if routes were found, sort them from shortest to longest
        if (success)
            SortRoutes();
        // return true if any routes were found
        return success;
    }

    bool FindRoutes(City* start, City* end) {
        // clear all data from the previous run
        complete_routes_.clear();
        // start finding new routes
        Route r;
        return FindRoutes(start, end, r);
    }

    Route* GetShortestRoute() {
        if (!complete_routes_.empty())
            return &(complete_routes_.at(0));
        return NULL;
    }

    std::vector<Route> GetAllRoutes() {
        return complete_routes_;
    }

    void PrintAllRoutes() {
        // No route found
        if (complete_routes_.empty()) {
            std::cout << "No route" << std::endl;
            return;
        }
        // Print all routes, shortest first
        std::cout << "Shortest route: ";
        for (int i = 0; i < complete_routes_.size(); i++) {
            Route r = complete_routes_.at(i);
            for (int j = 0; j < r.route_.size() - 1; j++) {
                std::cout << r.route_.at(j)->name_ << " -> ";
            }
            std::cout << r.route_.at(r.route_.size() - 1)->name_ << " | Distance: " << r.distance_ << std::endl;
        }
    }

private:
    void SortRoutes() {
        std::sort(complete_routes_.begin(), complete_routes_.end());
    }

    std::vector<Route> complete_routes_;
};

void TestShortestCityRoute() {
    City a, b, c, d;
    a.connected_cities_[&b] = 2;
    a.connected_cities_[&c] = 3;
    a.name_ = "a";
    b.connected_cities_[&d] = 6;
    b.name_ = "b";
    c.connected_cities_[&d] = 7;
    c.name_ = "c";
    d.name_ = "d";

    RouteFinder route_finder;
    route_finder.FindRoutes(&a, &d);
    route_finder.PrintAllRoutes();
}