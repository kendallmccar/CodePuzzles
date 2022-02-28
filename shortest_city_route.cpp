// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_set>
#include <vector>

// Find all routes, and identify the fastest route, between connected cities
// Route may not exist, circular loops exist
// If multiple routes are fastest, one is chosen at random

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
    std::unordered_set<City*> visited_cities_;
    int distance_;
    bool operator<(Route const& other) { return distance_ < other.distance_; }
};

class RouteFinder {
public:
    RouteFinder() : start_city_(NULL), end_city_(NULL) {}
    ~RouteFinder() = default;

    void FindRoutes(City* current, int distance, Route in_progress_route) {
        // add the distance to get to current city
        in_progress_route.distance_ += distance;
        // add start point to current in progress route
        in_progress_route.route_.push_back(current);
        // add current city to visited set
        in_progress_route.visited_cities_.insert(current);
        // if the start and end are the same, the route is complete
        if (current->name_ == end_city_->name_) {
            // add to the list of completed routes
            complete_routes_.push_back(std::move(in_progress_route));
            return;
        }
        // else if the end is not reached, try routing through each connected city
        for (auto& pair : current->connected_cities_) {
            // find routes through each connected city that hasn't been visited
            if (in_progress_route.visited_cities_.count(pair.first) < 1)
                FindRoutes(pair.first, pair.second, in_progress_route);
        }
    }

    bool FindRoutes(City* start, City* end) {
        // no routes between null start or destination
        if (start == NULL || end == NULL)
            return false;
        // update start and end data
        start_city_ = start;
        end_city_ = end;
        // clear all data from the previous run
        complete_routes_.clear();
        // start finding new routes
        Route r;
        FindRoutes(start, 0, r);
        if (complete_routes_.size() > 0) {
            SortRoutes();
            return true;
        }
        return false;
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
        // Not run
        if (start_city_ == NULL || end_city_ == NULL) {
            std::cout << "No route finding has occurred yet" << std::endl;
            return;
        }
        // No route found
        if (complete_routes_.empty()) {
            std::cout << "No route between " << start_city_->name_ << " and " << end_city_->name_ << std::endl;
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

    City* start_city_;
    City* end_city_;
    std::vector<Route> complete_routes_;
};

void TestCityRoute() {
    City a, b, c, d, e;
    a.connected_cities_[&b] = 2;
    a.connected_cities_[&c] = 3;
    a.name_ = "a";
    b.connected_cities_[&a] = 2;
    b.connected_cities_[&c] = 2;
    b.connected_cities_[&d] = 6;
    b.name_ = "b";
    c.connected_cities_[&a] = 3;
    c.connected_cities_[&b] = 2;
    c.connected_cities_[&d] = 7;
    c.name_ = "c";
    d.connected_cities_[&b] = 3;
    d.connected_cities_[&c] = 7;
    d.name_ = "d";
    e.name_ = "e"; // orphan

    RouteFinder route_finder;
    route_finder.FindRoutes(&a, &d);
    route_finder.PrintAllRoutes();
    route_finder.FindRoutes(&a, &e);
    route_finder.PrintAllRoutes();
}