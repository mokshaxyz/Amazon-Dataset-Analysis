Collaborators : 
Moksha - worked on 3 trends , parsecv fucntion , report , compiling the code , testing of code .
Shanaya Bajaj - Worked on 1 trend , report , parsecv function
Naisha Sheth : worked on 1 trend , report.

Sales Data Analysis
This project analyzes sales data from a CSV file. The data includes information about items sold, users who purchased them, ratings, timestamps, product categories, brands, and more. The analysis focuses on yearly sales, peak buying times, most sold product categories, gender-based analysis, brand preferences, and product performance.

Additionally, text files containing the code for each individual trend analysis and a report with a full detailed analysis are included in the project.

Table of Contents
Introduction
Getting Started
Data Structure
Functions
Running the Analysis
Additional Files
Contact
Introduction
This project is designed to parse and analyze sales data from an e-commerce dataset. The primary goals are to understand sales trends over the years, identify peak buying periods, determine the most popular product categories, and analyze purchasing behavior based on gender.

In addition to the main program, the project includes text files with the code for each individual trend analysis and a detailed report summarizing the findings.

Getting Started
Prerequisites
C++ compiler (e.g., GCC, Clang)
Standard Library support for C++11 or later
Files
final.cpp: Contains the main function and calls to other functions for analysis.

amazon_electronic_clean_dataset_without_index.csv: The dataset file containing sales data.

year.txt: Contains code for yearly sales analysis.

gender.txt: Contains code for peak gender analysis.

brand.txt: Contains code for most bought brands.

productperfomance.txt - most sold category analysis

rating.txt - average ratings of products bought yearly.

Dataset Report: Contains a detailed report of the analysis.

Compilation

To compile the code, run the following command in your terminal:
g++ -o final final.cpp

Execution
To run the compiled program, use:

./final
Ensure that the CSV file is in the same directory as the executable.

Data Structure
SalesData Struct
The SalesData struct represents each row of data in the CSV file. It includes the following fields:

item_id: Unique identifier for the item
user_id: Unique identifier for the user
rating: Rating given by the user
timestamp: Purchase timestamp
model_attr: Model attribute of the item
category: Product category
brand: Brand of the item
year: Year of purchase
user_attr: User attribute (e.g., gender, derived from user_id)
Functions
stringToInt
Converts a string to an integer. This is used to convert CSV fields that are read as strings into integers.

parseCSV
Parses the CSV file and populates a vector of SalesData structs. This function handles reading the file, skipping the header, and extracting the relevant fields from each row.

calculateYearlySales
Calculates the total sales for each year and returns a vector of pairs, where each pair contains a year and the corresponding total sales.

findPeakMonth
Identifies the peak buying month for a given year and returns a pair containing the peak month and the number of sales in that month.

findMostSoldProduct
Finds the most sold product category for a given year and returns the name of that category.

analyzeDataByGender
Analyzes sales data by gender, calculating total purchases and identifying top brands and categories for each gender in each year.

analyzeBrandPreference
Analyzes brand preferences based on sales data and prints the top 5 brands by sales volume.

analyzeProductPerformance
Analyzes the performance of different product categories and identifies the top-selling category.

Running the Analysis
The main analysis includes parsing the CSV file and performing various data analyses such as yearly sales, peak buying times, most sold product categories, and more. The results are printed to the console.


