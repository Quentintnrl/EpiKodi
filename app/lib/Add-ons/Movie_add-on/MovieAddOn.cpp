#include "MovieAddOn.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Callback for handling HTTP responses
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* out) {
    size_t totalSize = size * nmemb;
    out->append((char*)contents, totalSize);
    return totalSize;
}

// Function to fetch data from the TMDb API
std::string fetchFromAPI(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(curl);
    }
    return response;
}

// Function to fetch movie details by name
void MovieAddOn::fetchMovieDetailsByName(const std::string& api_key, const std::string& movie_name, const std::string& moviePath) {
    // URL encode the movie name
    std::string encoded_name = movie_name;
    for (size_t i = 0; i < encoded_name.length(); ++i) {
        if (encoded_name[i] == ' ') {
            encoded_name[i] = '+';
        }
    }

    // Search API URL
    std::string search_url = "https://api.themoviedb.org/3/search/movie?api_key=" + api_key + "&query=" + encoded_name;

    // Fetch search results
    std::string search_response = fetchFromAPI(search_url);

    if (search_response.empty()) {
        std::cerr << "Failed to fetch search results." << std::endl;
        return;
    }

    try {
        json search_data = json::parse(search_response);

        // Check if any results are returned
        if (search_data["results"].empty()) {
            return;
        }

        // Get the first movie from the search results
        json first_movie = search_data["results"][0];
        int movie_id = first_movie["id"];
        std::string title = first_movie["title"];

        // Fetch movie details
        std::string details_url = "https://api.themoviedb.org/3/movie/" + std::to_string(movie_id) + "?api_key=" + api_key + "&append_to_response=credits,release_dates";
        std::string details_response = fetchFromAPI(details_url);

        if (details_response.empty()) {
            std::cerr << "Failed to fetch movie details." << std::endl;
            return;
        }

        json details_data = json::parse(details_response);

        // Print movie details
        // std::cout << "Title: " << details_data["title"].get<std::string>() << std::endl;
        // std::cout << "Year: " << details_data["release_date"].get<std::string>().substr(0, 4) << std::endl;
        fill_config(std::filesystem::current_path().string() + MOVIES_CONFIG_PATH + "years.json", details_data["release_date"].get<std::string>().substr(0, 4), movie_name, moviePath);
        return;

        // std::cout << "Genre: ";
        for (const auto& genre : details_data["genres"]) {
            // std::cout << genre["name"].get<std::string>() << ", ";
        }
        // std::cout << std::endl;

        // std::cout << "Actors: ";
        for (const auto& cast : details_data["credits"]["cast"]) {
            // std::cout << cast["name"].get<std::string>() << ", ";
        }
        // std::cout << std::endl;

        // std::cout << "Directors: ";
        for (const auto& crew : details_data["credits"]["crew"]) {
            if (crew["job"] == "Director") {
                // std::cout << crew["name"].get<std::string>() << ", ";
            }
        }
        // std::cout << std::endl;

        // std::cout << "Studios: ";
        for (const auto& company : details_data["production_companies"]) {
            // std::cout << company["name"].get<std::string>() << ", ";
        }
        // std::cout << std::endl;

        // std::cout << "Countries: ";
        for (const auto& country : details_data["production_countries"]) {
            // std::cout << country["name"].get<std::string>() << ", ";
        }
        // std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }
}

MovieAddOn::MovieAddOn(std::string name) : AddOn(name) {}

void MovieAddOn::run() {
    std::string moviesPath = std::filesystem::current_path().string() + MOVIES_DIR;
    std::vector<std::string> movies;
    std::vector<std::string> moviesFilesPath;
    for (const auto &entry : std::filesystem::directory_iterator(moviesPath)) {
        //add it if the name doesn't start with a .
        if (entry.path().filename().string()[0] != '.') {
            movies.push_back(entry.path().filename().string().substr(0, entry.path().filename().string().find_last_of('.')));
            moviesFilesPath.push_back(entry.path().filename().string());
        }
    }
    for (std::size_t i = 0; i < movies.size(); i++) {
        fetchMovieDetailsByName(API_KEY, movies.at(i), moviesFilesPath.at(i));
    }
    while (_run) {
    }
}

void MovieAddOn::fill_config(const std::string configPath, const std::string target, const std::string movie, const std::string moviePath) {
    //get the content of the file and put it in a json object
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open config file: " << configPath << std::endl;
        return;
    }
    json config;
    file >> config;
    json content = config["content"];
    bool targetExists = false;
    for (auto &element : content) {
        if (element["name"] == target) {
            targetExists = true;
            break;
        }
    }
    if (!targetExists) {
        auto element = json::object();
        element["name"] = target;
        element["type"] = "ToPage";
        auto size = json::array();
        size.push_back(720);
        size.push_back(75);
        element["size"] = size;
        element["button"] = "assets/medias/media.png";
        element["hover_button"] = "assets/medias/media_hover.png";
        auto year = json::array();
        element["content"] = year;
        content.push_back(element);
    }
    auto year = json::array();
    for (auto &element : content) {
        if (element["name"] == target) {
            year = element["content"];
            break;
        }
    }
    bool movieExists = false;
    for (auto &element : year) {
        if (element["name"] == movie) {
            movieExists = true;
            break;
        }
    }
    if (movieExists) {
        return;
    }
    auto movieElement = json::object();
    movieElement["name"] = movie;
    movieElement["type"] = "ToMedia";
    movieElement["button"] = "assets/medias/media.png";
    movieElement["hover_button"] = "assets/medias/media_hover.png";
    movieElement["year"] = target;
    auto size = json::array();
    size.push_back(720);
    size.push_back(75);
    movieElement["size"] = size;
    movieElement["path"] = moviePath;
    year.push_back(movieElement);
    for (auto &element : content) {
        if (element["name"] == target) {
            element["content"] = year;
            break;
        }
    }
    config["content"] = content;
    file.close();
    std::ofstream fileOut(configPath);
    if (!fileOut.is_open()) {
        std::cerr << "Failed to open config file: " << configPath << std::endl;
        return;
    }
    fileOut << config.dump(4);
    fileOut.close();
}

extern "C" {
    AddOn *createAddOn(const std::string &AddOnName) {
        return new MovieAddOn(AddOnName);
    }
}