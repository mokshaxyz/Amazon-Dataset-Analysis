


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>

using namespace std;

// Custom function to convert string to integer
int stringToInt(const string& str) {
    int result;
    stringstream ss(str);
    ss >> result;
    return result;
}

// Define a struct to represent each row of data
struct SalesData {
    int item_id;
    int user_id;
    int rating;
    string timestamp;
    string model_attr;
    string category;
    string brand;
    int year;
    string user_attr; // Represent gender
};

// Function to parse CSV file and populate data structures
vector<SalesData> parseCSV(const string& filename) {
    vector<SalesData> data;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Unable to open file." << endl;
        return data;
    }

    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        SalesData row;
        string item;
        size_t pos = 0, start = 0;

        // Parse each element of the line
        for (int i = 0; i < 8; ++i) {
            pos = line.find(',', start);
            item = line.substr(start, pos - start);
            start = pos + 1;

            switch (i) {
                case 0:
                    row.item_id = stringToInt(item);
                    break;
                case 1:
                    row.user_id = stringToInt(item);
                    break;
                case 2:
                    row.rating = stringToInt(item);
                    break;
                case 3:
                    row.timestamp = item;
                    break;
                case 4:
                    row.model_attr = item;
                    break;
                case 5:
                    row.category = item;
                    break;
                case 6:
                    row.brand = item;
                    break;
                case 7:
                    row.year = stringToInt(item);
                    break;
            }
        }

        // Read the last field and categorize by gender
        row.user_attr = (row.user_id % 2 == 0) ? "Male" : "Female"; // Just an example condition, you should replace this with your logic

        // Add parsed data to vector
        data.push_back(row);
    }

    // Close the file
    file.close();

    return data;
}

// Function to calculate yearly sales
vector<pair<int, int>> calculateYearlySales(const vector<SalesData>& data) {
    vector<pair<int, int>> yearlySales; // Vector to store yearly sales (year, total sales)

    // Iterate through data to calculate yearly sales
    for (const auto& entry : data) {
        // Check if the year already exists in the vector
        bool found = false;
        for (auto& yearlySale : yearlySales) {
            if (yearlySale.first == entry.year) {
                yearlySale.second++;
                found = true;
                break;
            }
        }
        if (!found) {
            yearlySales.emplace_back(entry.year, 1);
        }
    }

    // Bubble sort for sorting years
    for (size_t i = 0; i < yearlySales.size() - 1; ++i) {
        for (size_t j = 0; j < yearlySales.size() - i - 1; ++j) {
            if (yearlySales[j].first > yearlySales[j + 1].first) {
                pair<int, int> temp = yearlySales[j];
                yearlySales[j] = yearlySales[j + 1];
                yearlySales[j + 1] = temp;
            }
        }
    }

    return yearlySales;
}

// Function to identify peak buying times
pair<int, int> findPeakMonth(const vector<SalesData>& data, int year) {
    vector<int> monthSales(12, 0); // Vector to store sales for each month (0 to 11)

    // Iterate through data to calculate sales for each month of the specified year
    for (const auto& entry : data) {
        if (entry.year == year) {
            int month = stringToInt(entry.timestamp.substr(5, 2)) - 1; // Extract month from timestamp (1 to 12 -> 0 to 11)
            monthSales[month]++;
        }
    }

    // Find the peak month
    int maxSales = -1;
    int peakMonth = -1;
    for (int i = 0; i < 12; ++i) {
        if (monthSales[i] > maxSales) {
            maxSales = monthSales[i];
            peakMonth = i + 1; // Convert back to month number (0 to 11 -> 1 to 12)
        }
    }

    return make_pair(peakMonth, maxSales);
}

// Function to find the most sold product category in a year
string findMostSoldProduct(const vector<SalesData>& data, int year) {
    unordered_map<string, int> categorySales;

    // Count sales for each product category in the specified year
    for (const auto& entry : data) {
        if (entry.year == year) {
            categorySales[entry.category]++;
        }
    }

    // Find the most sold product category
    string mostSoldCategory;
    int maxSales = -1;
    for (const auto& pair : categorySales) {
        if (pair.second > maxSales) {
            maxSales = pair.second;
            mostSoldCategory = pair.first;
        }
    }

    return mostSoldCategory;
}

// Function to calculate average rating for each year
vector<double> calculateAverageRatings(const vector<SalesData>& sales_data) {
    vector<double> avg_ratings(2024, 0); 
    vector<int> counts(2024, 0);

    for (const auto& entry : sales_data) {
        avg_ratings[entry.year] += entry.rating;
        counts[entry.year]++;
    }

    vector<double> yearly_avg_ratings(2024);
    for (int i = 0; i < 2024; ++i) {
        if (counts[i] != 0) {
            yearly_avg_ratings[i] = avg_ratings[i] / counts[i];
        }
    }

    return yearly_avg_ratings;
}

int main() {
    // Parse CSV file
    vector<SalesData> sales_data = parseCSV("amazon_electronic_clean_dataset_without_index.csv");

    // Check if data is empty
    if (sales_data.empty()) {
        cout << "Error: No data found or unable to parse the CSV file." << endl;
        return 1; // Exit with an error code
    }

    // Analyze data by gender
    unordered_map<int, int> totalPurchasesByYearMale;
    unordered_map<int, int> totalPurchasesByYearFemale;
    unordered_map<int, string> topBrandByYearMale;
    unordered_map<int, string> topBrandByYearFemale;
    unordered_map<int, string> topCategoryByYearMale;
    unordered_map<int, string> topCategoryByYearFemale;

    // Iterate through data to calculate total purchases and identify top brands and categories for each gender in each year
    for (const auto& entry : sales_data) {
        int year = entry.year;
        if (entry.user_attr == "Male") {
            totalPurchasesByYearMale[year]++;
            if (topBrandByYearMale[year].empty() || entry.brand > topBrandByYearMale[year]) {
                topBrandByYearMale[year] = entry.brand;
            }
            if (topCategoryByYearMale[year].empty() || entry.category > topCategoryByYearMale[year]) {
                topCategoryByYearMale[year] = entry.category;
            }
        } else if (entry.user_attr == "Female") {
            totalPurchasesByYearFemale[year]++;
            if (topBrandByYearFemale[year].empty() || entry.brand > topBrandByYearFemale[year]) {
                topBrandByYearFemale[year] = entry.brand;
            }
            if (topCategoryByYearFemale[year].empty() || entry.category > topCategoryByYearFemale[year]) {
                topCategoryByYearFemale[year] = entry.category;
            }
        }
    }

    // Collect the years with data for both genders
    vector<int> years;
    for (const auto& entry : totalPurchasesByYearMale) {
        years.push_back(entry.first);
    }

    // Bubble sort for sorting years
    for (size_t i = 0; i < years.size() - 1; ++i) {
        for (size_t j = 0; j < years.size() - i - 1; ++j) {
            if (years[j] > years[j + 1]) {
                int temp = years[j];
                years[j] = years[j + 1];
                years[j + 1] = temp;
            }
        }
    }

    // Print analysis results
    cout << "Yearly Gender Analysis:\n";
    for (const auto& year : years) {
        cout << "Year: " << year << endl;
        cout << "Total Purchases by Males: " << totalPurchasesByYearMale[year] << endl;
        cout << "Total Purchases by Females: " << totalPurchasesByYearFemale[year] << endl;
        double percentageChange = ((totalPurchasesByYearFemale[year] - totalPurchasesByYearMale[year]) / static_cast<double>(totalPurchasesByYearMale[year])) * 100.0;
        cout << "Percentage Change: " << percentageChange << "%" << endl;
        cout << "Top Brand Purchased by Males: " << topBrandByYearMale[year] << endl;
        cout << "Top Brand Purchased by Females: " << topBrandByYearFemale[year] << endl;
        cout << "Top Category Purchased by Males: " << topCategoryByYearMale[year] << endl;
        cout << "Top Category Purchased by Females: " << topCategoryByYearFemale[year] << endl;
        cout << endl;
    }

    // Calculate yearly sales
    vector<pair<int, int>> yearlySales = calculateYearlySales(sales_data);

    // Output yearly sales with peak month and most sold product category
    cout << "Yearly Sales Analysis:" << endl;
    for (const auto& yearlyPair : yearlySales) {
        int year = yearlyPair.first;
        int totalSales = yearlyPair.second;
        cout << "Year: " << year << ", Total Sales: " << totalSales << endl;

        // Find peak buying month and sales in peak month
        pair<int, int> peakMonthInfo = findPeakMonth(sales_data, year);
        cout << "Peak Buying Month: " << peakMonthInfo.first << ", Sales in Peak Month: " << peakMonthInfo.second << endl;

        // Find most sold product category
        string mostSoldCategory = findMostSoldProduct(sales_data, year);
        cout << "Most Sold Product Category: " << mostSoldCategory << endl;

        cout << endl;
    }

    // Analyze brand preference
    unordered_map<string, int> brandSales;

    // Iterate through the data and count the frequency of product sales for each brand
    for (const auto& entry : sales_data) {
        brandSales[entry.brand]++;
    }

    // Convert unordered_map to vector for sorting
    vector<pair<string, int>> sortedBrands(brandSales.begin(), brandSales.end());

    // Bubble sort for sorting brands based on their sales counts
    for (size_t i = 0; i < sortedBrands.size() - 1; ++i) {
        for (size_t j = 0; j < sortedBrands.size() - i - 1; ++j) {
            if (sortedBrands[j].second < sortedBrands[j + 1].second) {
                pair<string, int> temp = sortedBrands[j];
                sortedBrands[j] = sortedBrands[j + 1];
                sortedBrands[j + 1] = temp;
            }
        }
    }

    // Output the top brands and their sales counts
    cout << "Brand Preference Analysis:" << endl;
    int count = 0;
    for (const auto& pair : sortedBrands) {
        cout << pair.first << ": " << pair.second << " units" << endl;
        if (++count == 5) break; // Output top 5 brands
    }

    // Analyze product performance
    unordered_map<string, int> categorySales;

    // Iterate through the data and count the frequency of each product category
    for (const auto& entry : sales_data) {
        categorySales[entry.category]++;
    }

    // Find the top-selling product category
    int maxSales = 0;
    string topCategory;
    for (const auto& pair : categorySales) {
        if (pair.second > maxSales) {
            maxSales = pair.second;
            topCategory = pair.first;
        }
    }

    // Output the top-selling product category
    cout << "Top Selling Product Category: " << topCategory << " (" << maxSales << " units sold)" << endl;

    // Calculate average rating for each year
    vector<double> avg_ratings(2024, 0); 
    vector<int> counts(2024, 0);

    for (const auto& entry : sales_data) {
        avg_ratings[entry.year] += entry.rating;
        counts[entry.year]++;
    }

    vector<double> yearly_avg_ratings(2024);
    for (int i = 0; i < 2024; ++i) {
        if (counts[i] != 0) {
            yearly_avg_ratings[i] = avg_ratings[i] / counts[i];
        }
    }

    // Print average ratings
    cout << "Average ratings for each year:" << endl;
    for (int year = 0; year < 2024; ++year) {
        if (yearly_avg_ratings[year] != 0) {
            // Print average rating for this year
            cout << "Year " << year << ": " << yearly_avg_ratings[year] << endl;
        }
    }

    return 0;
}

