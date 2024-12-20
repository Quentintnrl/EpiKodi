#include "MusicAddOn.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

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

void MusicAddOn::fetchSongYear(const std::string& artist, const std::string& title, const std::string& file) {
    // Build the query URL
    std::string url = "https://musicbrainz.org/ws/2/recording/";

    // Make the GET request with search parameters
    auto response = cpr::Get(cpr::Url{url},
                             cpr::Parameters{
                                 {"query", "artist:" + artist + " AND recording:" + title},
                                 {"fmt", "json"}});

    if (response.status_code == 200) {
        try {
            // Parse the JSON response
            auto json = nlohmann::json::parse(response.text);

            // Check if recordings exist
            if (json.contains("recordings") && !json["recordings"].empty()) {
                // Get the first matching recording
                const auto& recording = json["recordings"][0];

                // Extract and print the title, artist, and year
                std::string songTitle = recording["title"];
                std::string songArtist = recording["artist-credit"][0]["name"];
                std::string year = recording.contains("first-release-date")
                                   ? recording["first-release-date"]
                                   : "Unknown";

                std::cout << "Title: " << songTitle << std::endl;
                std::cout << "Artist: " << songArtist << std::endl;
                std::cout << "Year: " << year << std::endl;
                fill_config(std::filesystem::current_path().string() + MUSICS_CONFIG_PATH + "years.json", year, songTitle, file);
            } else {
                std::cout << "No matching song found." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        }
    } else {
        std::cerr << "HTTP Request failed with status code: " << response.status_code << std::endl;
    }
}

MusicAddOn::MusicAddOn(std::string name) : AddOn(name) {}

void MusicAddOn::run() {
    std::string musicsPath = std::filesystem::current_path().string() + MUSICS_DIR;
    std::vector<std::string> musics;
    std::vector<std::string> musicsFilesPath;
    for (const auto &entry : std::filesystem::directory_iterator(musicsPath)) {
        //add it if the name doesn't start with a .
        if (entry.path().filename().string()[0] != '.') {
            musics.push_back(entry.path().filename().string().substr(0, entry.path().filename().string().find_last_of('.')));
            musicsFilesPath.push_back(entry.path().filename().string());
        }
    }
    for (std::size_t i = 0; i < musics.size(); i++) {
        const std::string artist = musics[i].substr(0, musics[i].find_first_of('-'));
        const std::string title = musics[i].substr(musics[i].find_first_of('-') + 1, musics[i].find_last_of('.'));
        std::cout << "Fetching song year for: " << artist << "-" << title << std::endl;
        fetchSongYear(artist, title, musicsFilesPath[i]);
    }
    while (_run) {
    }
}

void MusicAddOn::fill_config(const std::string configPath, const std::string target, const std::string movie, const std::string moviePath) {
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
    movieElement["path"] = "/musics/" + moviePath;
    // movieElement["file_path"] = "/json/pages/musics/";
    year.push_back(movieElement);
    for (auto &element : content) {
        if (element["name"] == target) {
            element["content"] = year;
            element["file_path"] = "/json/pages/musics/";
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
    std::cout << config.dump(4) << std::endl;
    fileOut.close();
}

extern "C" {
    AddOn *createAddOn(const std::string &AddOnName) {
        return new MusicAddOn(AddOnName);
    }
}