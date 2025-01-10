#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <gumbo.h>

// Callback function to write HTTP response data to a string
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Function to perform HTTP GET request using libcurl
std::string getHTML(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string htmlContent;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlContent);
        
        res = curl_easy_perform(curl);
        
        if(res != CURLE_OK) {
            std::cerr << "Curl failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return htmlContent;
}

// Recursive function to search for product information in the HTML
void searchForProducts(GumboNode* node, std::ofstream& csvFile) {
    if (node->type != GUMBO_NODE_ELEMENT) return;

    GumboElement* element = &node->v.element;

    // Check for product names (example class for product titles)
    if (element->tag == GUMBO_TAG_H2) {
        for (int i = 0; i < element->children.length; ++i) {
            GumboNode* child = (GumboNode*)element->children.data[i];
            if (child->type == GUMBO_NODE_TEXT) {
                std::string productName = child->v.text.text;
                // Assuming price and rating are extracted similarly
                std::string productPrice = "Price not found";
                std::string productRating = "Rating not found";
                
                // Write data to CSV file
                csvFile << "\"" << productName << "\",\"" << productPrice << "\",\"" << productRating << "\"\n";
            }
        }
    }

    // Recursively check other nodes
    for (int i = 0; i < element->children.length; ++i) {
        searchForProducts((GumboNode*)element->children.data[i], csvFile);
    }
}

int main() {
    std::string url = "https://www.example.com/products"; // Replace with a real URL
    std::string htmlContent = getHTML(url);

    // Parse HTML content using Gumbo
    GumboOutput* output = gumbo_parse(htmlContent.c_str());

    // Open CSV file for writing
    std::ofstream csvFile("products.csv");
    if (!csvFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }

    // Write header row for CSV
    csvFile << "Product Name,Price,Rating\n";

    // Start searching for product information
    searchForProducts(output->root, csvFile);

    // Clean up Gumbo output
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    // Close CSV file
    csvFile.close();

    std::cout << "Data extraction complete. CSV file saved as 'products.csv'." << std::endl;

    return 0;
}
