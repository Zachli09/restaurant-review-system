#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string login();
bool alreadyReviewed(string username, string restaurant);
void reviewRestaurant(string username);
void seeReviews();
void seeAverage();

int main()
{
    string currentUser = login();

    int choice;

    do
    {
        cout << endl;
        cout << "1. Review a restaurant" << endl;
        cout << "2. See all reviews" << endl;
        cout << "3. See average score for a restaurant" << endl;
        cout << "4. Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            reviewRestaurant(currentUser);
        else if (choice == 2)
            seeReviews();
        else if (choice == 3)
            seeAverage();
        else if (choice == 4)
            cout << "Program ended" << endl;
        else
            cout << "Invalid choice" << endl;

    } while (choice != 4);

    return 0;
}
string login()
{
    string username, password;
    string fileUser, filePass;

    while (true)
    {
        cout << "Enter username: ";
        cin >> username;

        cout << "Enter password: ";
        cin >> password;

        ifstream file("users.txt");

        while (file >> fileUser >> filePass)
        {
            if (username == fileUser && password == filePass)
            {
                file.close();
                cout << "Login successful" << endl;
                return username;
            }
        }

        file.close();
        cout << "Invalid login, try again" << endl;
    }
}
bool alreadyReviewed(string username, string restaurant)
{
    ifstream file("reviews.txt");

    string fileUser, fileRestaurant;
    int rating;

    while (file >> fileUser >> fileRestaurant >> rating)
    {
        if (fileUser == username && fileRestaurant == restaurant)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}
void reviewRestaurant(string username)
{
    string restaurant;
    int stars;

    cout << "Enter restaurant name: ";
    cin >> restaurant;

    if (alreadyReviewed(username, restaurant))
    {
        cout << "You already reviewed this restaurant" << endl;
        return;
    }

    cout << "Enter your star rating (0 to 5): ";
    cin >> stars;

    while (stars < 0 || stars > 5)
    {
        cout << "Invalid rating. Try again: ";
        cin >> stars;
    }

    ofstream file("reviews.txt", ios::app);
    file << username << " " << restaurant << " " << stars << endl;
    file.close();

    cout << "Review added." << endl;
}
void seeReviews()
{
    ifstream file("reviews.txt");

    string username, restaurant;
    int rating;

    if (!(file >> username >> restaurant >> rating))
    {
        cout << "No reviews found" << endl;
        file.close();
        return;
    }

    file.clear();
    file.seekg(0);

    while (file >> username >> restaurant >> rating)
    {
        cout << "Restaurant: " << restaurant << endl;
        cout << "User: " << username << endl;
        cout << "Rating: " << rating << endl;
        cout << endl;
    }

    file.close();
}
void seeAverage()
{
    ifstream file("reviews.txt");

    string wantedRestaurant;
    string username, restaurant;
    int rating;

    int total = 0;
    int count = 0;

    cout << "Enter restaurant name: ";
    cin >> wantedRestaurant;

    while (file >> username >> restaurant >> rating)
    {
        if (restaurant == wantedRestaurant)
        {
            total += rating;
            count++;
        }
    }

    file.close();

    if (count == 0)
    {
        cout << "No reviews for this restaurant." << endl;
    }
    else
    {
        double average = (double)total / count;
        cout << "Average rating for " << wantedRestaurant << ": " << average << endl;
    }
}