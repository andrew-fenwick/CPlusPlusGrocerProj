//Andrew Fenwick - CS210: Project 3

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <list>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

//first to create a class connecting a food with quantity
class CornerGrocers {

//we need public and private
public:
    void SetName(string itemName);
    void SetQuantity(int itemQuantity);
    string GetName() const;
    int GetQuantity() const;
    void Print();

private:
    string name;
    int quantity;
};

//setters
void CornerGrocers::SetName(string itemName) {
    name = itemName;
}

void CornerGrocers::SetQuantity(int itemQuantity) {
    quantity = itemQuantity;
}

//getters
string CornerGrocers::GetName() const {
    return name;
}

int CornerGrocers::GetQuantity() const {
    return quantity;
}

void CornerGrocers::Print() {
    cout << name << ": " << quantity << endl;
}

//now the main function
int main()
{

    //this class will be used for option 1 with input
    CornerGrocers userInput;
    ofstream outFS("frequency.dat.txt");
    ifstream myfile;
    string food;
    int menuChoice;
    string userChoice;
    string inventoryQuant;
    bool loopStoppa = true;
    const int optionOne = 1, optionTwo = 2, optionThree = 3, optionFour = 4;

  //this vector will have the files dumped into it
    vector<string> totalFood;


    //this vector will be used to reference for counting loops
    vector<string> groceryItems = { "Apples", "Beets", "Broccoli", "Cantaloupe", "Cauliflower", "Celery", "Cranberries", "Cucumbers",
        "Garlic", "Limes", "Onions", "Peaches", "Pears", "Peas", "Potatoes", "Pumpkins", "Radishes", "Spinach", "Yams", "Zucchini" };


    //we need to open the given file


    myfile.open("proj3list.txt", ios::in);

    //ofstream outFS("myoutfile.txt");

//    outFS.open();



    //double check there are no issues with the text file
    if (!myfile.is_open()) {
        cout << "Could not open file proj3list.txt" << endl;
        return 1;
    }

    if (!outFS.is_open()) {
        cout << "Could not open file frequency.dat.txt." << endl;
        return 1;
    }

    //this loop will add each line from the file into the vector
    while (myfile.good()) {
        getline(myfile, food, '\n');

        totalFood.push_back(food);
    }

    myfile.close();
//the file is now closed


    //this will alphabetize the items in the vecotr
    sort(totalFood.begin(), totalFood.end());



    //this will count each item
    unordered_map<string, int> freq;
    for (auto& i : totalFood) {     
        freq[i]++;     
    }

    //this int will have the total number of different options, we will reference this sum for a loop later on
    unsigned int totalNumDiffItems = groceryItems.size();    


    //first we will write to our new file
    outFS << "---------------------------------" << endl;
    outFS << "Inventory Quantity - Numbered" << endl;
    outFS << endl;

    for (unsigned int j = 0; j < totalNumDiffItems; j++) {
        outFS << groceryItems[j] << ": " << freq[(groceryItems[j])] << endl;
    }
    outFS << endl;
    outFS << "---------------------------------" << endl;
    outFS << endl;

    outFS << "Inventory Quantity - Histogram" << endl;
    outFS << endl;
    for (unsigned int j = 0; j < totalNumDiffItems; j++) {
        outFS << groceryItems[j] << ": ";
        for (int k = 0; k < freq[(groceryItems[j])]; k++) outFS << '*';
        outFS << endl;
    }
    outFS << endl;
    outFS << "---------------------------------" << endl;
    outFS << endl;
       
    outFS.close();
    //now our out file is closed


    //Menu Display
    //the while loop will send the user to the start if an invalid input is entered

    while (!loopStoppa == false) {

        cout << "Welcome to Corner Grocer!" << endl;
        cout << endl;
        cout << "Enter [1] for item lookup" << endl;
        cout << "Enter [2] for list of each item with numbered quantity" << endl;
        cout << "Enter [3] for list of each item with quantity as histogram" << endl;
        cout << "Enter [4] to exit the program" << endl;
        cin >> menuChoice;
        cout << endl;



    //this first if statement will reject any combination of characters or strings entered
        if (!cin) 
        {
            cin.clear();  
            string input;
            getline(cin, input); 
            cout << "Invalid Entry" << endl;
            cout << endl;
            loopStoppa = true;
        }


        //option one will allow the user to search for a specific item
        //the userChoice is automatically given a capital letter at the start, since our text file has every food capitalized

        else if (menuChoice == optionOne) {
            cout << "Item lookup" << endl;
            cout << endl;
            cout << "Please enter which item you are looking for?" << endl;
            cin >> userChoice;
            string s = userChoice;
            s[0] = toupper(s[0]);
            transform(s.begin() + 1, s.end(), s.begin() + 1, tolower);
            cout << endl;
            userInput.SetName(s);
            userInput.SetQuantity(freq[s]);
            userInput.Print();
            loopStoppa == false;
            break;
            

        }

        //option two has a loop to go through every different item
        else if (menuChoice == optionTwo) {
            cout << endl;
            for (unsigned int j = 0; j < totalNumDiffItems; j++) {
                cout << groceryItems[j] << ": " << freq[(groceryItems[j])] << endl;
                loopStoppa == false;
            }
            break;
        }

        //option three has two loops. one will go through each item and one prints characters for the quantity
        else if (menuChoice == optionThree) {
            cout << endl;
            for (unsigned int j = 0; j < totalNumDiffItems; j++) {
                cout << groceryItems[j] << ": ";
                for (int k = 0; k < freq[(groceryItems[j])]; k++) cout << '*';
                cout << endl;
                loopStoppa == false;
              
            }
            break;
        }

        //option for prints a farewell message and ends the program
        else if (menuChoice == optionFour) {
            cout << "Have a nice day!" << endl;
            loopStoppa == false;
            break;
            return 0;

        }
        //any other input recieved will come to this else statement, printing 'invalid entry', and restarting the menu
        else {
            cout << "Invalid Entry." << endl;
            cout << endl;
        }
        

    }

  
}