#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN "cls"
#elif _unix_
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

void heading() {
    cout << "____________________________________________________________" << endl;
    cout << "|                                                          |" << endl;
    cout << "|                        CINE-GO                           |" << endl;
    cout << "|                                                          |" << endl;
    cout << "____________________________________________________________" << endl;
}

class User;
class Manager;
class BookingPlatform;

class User {
public:
    string username;
    string password;
    vector<int> bookedTickets;

    User(string uname, string pwd) : username(uname), password(pwd) {}
    void bookTicket(int ticketId);
    void cancelTicket(int ticketId);
    void addReview(BookingPlatform &platform, int movieId, string review);

    friend void viewBookedTickets(User &user);
};

class Manager {
public:
    string username;
    string password;

    Manager(string uname, string pwd) : username(uname), password(pwd) {}
};

class Movie {
public:
    int id;
    string title;
    int numberOfTickets;
    double ticketCost;
    vector<int> shows;
    vector<string> reviews;

    Movie(int mid, string t, int numTickets, double cost)
        : id(mid), title(t), numberOfTickets(numTickets), ticketCost(cost) {}
};

class Show {
public:
    int id;
    int movieId;
    string datetime;

    Show(int sid, int mid, string dt) : id(sid), movieId(mid), datetime(dt) {}
};

class Ticket {
public:
    int id;
    int showId;
    string username;

    Ticket(int tid, int sid, string uname) : id(tid), showId(sid), username(uname) {}
};

class FoodItem {
public:
    string name;
    double price;

    FoodItem(string n, double p) : name(n), price(p) {}
};

class BookingPlatform {
private:
    vector<User> users;
    vector<Manager> managers;
    vector<Movie> movies;
    vector<Show> shows;
    vector<Ticket> tickets;
    vector<FoodItem> foodItems;
    int nextMovieId = 1;
    int nextShowId = 1;
    int nextTicketId = 1;
    bool userLoggedIn;
    bool managerLoggedIn;

public:
    void registerUser(string username, string password);
    void loginUser(string username, string password);
    void registerManager(string username, string password);
    void loginManager(string username, string password);
    void browseMovies();
    void bookTicket(string username, int showId);
    void cancelTicket(string username, int ticketId);
    //void buyFoodItem(string username, string foodItemName, int quantity);
    void addReview(string username, int movieId, string review);
    void addReviewToMovie(int movieId, string review);
    const vector<Manager>& getManagers() const {
        return managers;}

    bool isUserLoggedIn() const {
        return userLoggedIn;
    }

    bool isManagerLoggedIn() const {
        return managerLoggedIn;
    }

    void setUserLoggedIn(bool loggedIn) {
        userLoggedIn = loggedIn;
    }

    void setManagerLoggedIn(bool loggedIn) {
        managerLoggedIn = loggedIn;
    }

    void addMovie(string title, int numTickets, double cost) {
        movies.push_back(Movie(nextMovieId++, title, numTickets, cost));
    }

    void addShow(int movieId, string datetime) {
        shows.push_back(Show(nextShowId++, movieId, datetime));
    }

    void manageReviews() {
        for (const auto& movie : movies) {
            cout << "Reviews for movie: " << movie.title << endl;
            for (const auto& review : movie.reviews) {
                cout << "- " << review << endl;
            }
        }
    }


    void initializeMovies() {
        addMovie("Dilwale Dulhania Le Jayenge", 100, 300.00);
        addMovie("3 Idiots", 100, 250.00);
        addMovie("Dangal", 100, 280.00);
        addMovie("Sholay", 100, 220.00);
        addMovie("Lagaan", 100, 240.00);
        addMovie("Kabhi Khushi Kabhie Gham", 100, 260.00);
        addMovie("Taare Zameen Par", 100, 270.00);
        addMovie("Chak De! India", 100, 230.00);
        addMovie("Zindagi Na Milegi Dobara", 100, 290.00);
        addMovie("Bajrangi Bhaijaan", 100, 310.00);
    }

    void initializeShows() {
        // Shows for "Dilwale Dulhania Le Jayenge"
        addShow(1, "2024-06-16 10:00");
        addShow(1, "2024-06-16 14:00");

        // Shows for "3 Idiots"
        addShow(2, "2024-06-17 11:00");
        addShow(2, "2024-06-17 15:00");

        // Shows for "Dangal"
        addShow(3, "2024-06-18 12:00");
        addShow(3, "2024-06-18 16:00");

        // Shows for "Sholay"
        addShow(4, "2024-06-19 13:00");
        addShow(4, "2024-06-19 17:00");

        // Shows for "Lagaan"
        addShow(5, "2024-06-20 14:00");
        addShow(5, "2024-06-20 18:00");

        // Shows for "Kabhi Khushi Kabhie Gham"
        addShow(6, "2024-06-21 15:00");
        addShow(6, "2024-06-21 19:00");

        // Shows for "Taare Zameen Par"
        addShow(7, "2024-06-22 16:00");
        addShow(7, "2024-06-22 20:00");

        // Shows for "Chak De! India"
        addShow(8, "2024-06-23 17:00");
        addShow(8, "2024-06-23 21:00");

        // Shows for "Zindagi Na Milegi Dobara"
        addShow(9, "2024-06-24 18:00");
        addShow(9, "2024-06-24 22:00");

        // Shows for "Bajrangi Bhaijaan"
        addShow(10, "2024-06-25 19:00");
        addShow(10, "2024-06-25 23:00");
    }
};

// Function Implementations

void User::bookTicket(int ticketId) {
    bookedTickets.push_back(ticketId);
}

void User::cancelTicket(int ticketId) {
    auto it = find(bookedTickets.begin(), bookedTickets.end(), ticketId);
    if (it != bookedTickets.end()) {
        bookedTickets.erase(it);
    } else {
        throw runtime_error("Ticket not found.");
    }
}

void BookingPlatform::addReviewToMovie(int movieId, string review) {
    for (auto& movie : movies) {
        if (movie.id == movieId) {
            movie.reviews.push_back(review);
            return;
        }
    }
    throw runtime_error("Movie not found.");
}

void User::addReview(BookingPlatform &platform, int movieId, string review) {
    platform.addReviewToMovie(movieId, review);
}

void BookingPlatform::registerUser(string username, string password) {
    users.push_back(User(username, password));
    return;
}

void BookingPlatform::loginUser(string username, string password) {
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            cout << "User login successful!" << endl;
            return;
        }
    }
    throw runtime_error("Invalid username or password.");
}

void BookingPlatform::registerManager(string username, string password) {
    managers.push_back(Manager(username, password));
    return;
}

void BookingPlatform::loginManager(string username, string password) {
    for (auto& manager : managers) {
        if (manager.username == username && manager.password == password) {
            cout << "Manager login successful!" << endl;
            return;
        }
    }
    throw runtime_error("Invalid username or password.");
}

void BookingPlatform::browseMovies() {
    for (auto& movie : movies) {
        cout << "Movie ID: " << movie.id << " Title: " << movie.title
             << " Tickets Available: " << movie.numberOfTickets
             << " Ticket Cost: $" << movie.ticketCost << endl;
    }
}

void BookingPlatform::bookTicket(string username, int showId) {
    int numTickets;
    cout << "Enter the number of tickets you want to book: ";
    cin >> numTickets;

    // Find the show and the corresponding movie
    for (auto& show : shows) {
        if (show.id == showId) {
            for (auto& movie : movies) {
                if (movie.id == show.movieId) {
                    if (movie.numberOfTickets >= numTickets) {
                        double totalAmount = numTickets * movie.ticketCost;
                        movie.numberOfTickets -= numTickets;
                        for (auto& user : users) {
                            if (user.username == username) {
                                for (int i = 0; i < numTickets; ++i) {
                                    tickets.push_back(Ticket(nextTicketId++, showId, username));
                                    user.bookTicket(nextTicketId - 1);
                                }
                                cout << "Tickets booked successfully!" << endl;
                                cout << "Total amount to be paid: " << totalAmount << endl;
                                return;
                            }
                        }
                    } else {
                        cout << "Only " << movie.numberOfTickets << " tickets are available!" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "Show not found!" << endl;
}


void BookingPlatform::cancelTicket(string username, int ticketId) {
    int numTickets;
    cout << "Enter the number of tickets you want to cancel: ";
    cin >> numTickets;

    if (numTickets <= 0) {
        cout << "Invalid number of tickets!" << endl;
        return;
    }

    // Find the tickets and the corresponding show and movie
    auto it = find_if(tickets.begin(), tickets.end(),
                      [ticketId, &username](const Ticket& ticket) {
                          return ticket.id == ticketId && ticket.username == username;
                      });

    if (it != tickets.end()) {
        int showId = it->showId;
        int count = 0;

        // Count the number of tickets the user has for this show
        for (auto& ticket : tickets) {
            if (ticket.showId == showId && ticket.username == username) {
                count++;
            }
        }

        if (count >= numTickets) {
            int ticketsCancelled = 0;
            for (auto ticketIt = tickets.begin(); ticketIt != tickets.end();) {
                if (ticketIt->showId == showId && ticketIt->username == username) {
                    ticketIt = tickets.erase(ticketIt);
                    ticketsCancelled++;
                    if (ticketsCancelled == numTickets) {
                        break; // Stop cancelling tickets once the required number has been cancelled
                    }
                } else {
                    ++ticketIt;
                }
            }

            for (auto& user : users) {
                if (user.username == username) {
                    for (int i = 0; i < numTickets; ++i) {
                        user.cancelTicket(ticketId);
                    }
                    break;
                }
            }

            for (auto& movie : movies) {
                for (auto& show : shows) {
                    if (show.id == showId && show.movieId == movie.id) {
                        movie.numberOfTickets += numTickets;
                        cout << "Tickets cancelled successfully!" << endl;
                        return;
                    }
                }
            }
        } else {
            cout << "You only have " << count << " tickets for this show!" << endl;
        }
    } else {
        cout << "Ticket not found!" << endl;
    }
}




void BookingPlatform::addReview(string username, int movieId, string review) {
    for (auto& user : users) {
        if (user.username == username) {
            addReviewToMovie(movieId, review);
            cout << "Review added successfully!" << endl;
            return;
        }
    }
    cout << "User not found!" << endl;
}

void viewBookedTickets(User &user) {
    cout << "Booked tickets for user: " << user.username << endl;
    for (const auto& ticketId : user.bookedTickets) {
        cout << "Ticket ID: " << ticketId << endl;
    }
}

void clearScreen() {
    system(CLEAR_SCREEN);
}

// Function to display registration/login options
void displayRegistrationLoginOptions() {
    cout << "\nWelcome to the Booking Platform!\n";
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void displayUserMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Browse Movies\n";
    cout << "2. Book Ticket\n";
    cout << "3. Cancel Ticket\n";
    cout << "4. Add Review\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}


// Function to display manager menu
void displayManagerMenu() {
    cout << "\nManager Menu:\n";
    cout << "1. Browse Movies\n";
    cout << "2. Add Movie\n";
    cout << "3. Add Show\n";
    cout << "4. Manage Reviews\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}

// Function to handle user registration
void handleUserRegistration(BookingPlatform &platform) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    platform.registerUser(username, password);
    cout << "User registered successfully!" << endl;
}

// Function to handle user login
void handleUserLogin(BookingPlatform &platform) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    platform.loginUser(username, password);
    return;
}

// Function to handle manager registration
void handleManagerRegistration(BookingPlatform &platform) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    platform.registerManager(username, password);
    cout << "Manager registered successfully!" << endl;
}

// Function to handle manager login
void handleManagerLogin(BookingPlatform &platform) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    platform.loginManager(username, password);
    return;
}

int main(int argc, char* argv[]) {
    BookingPlatform platform;
    platform.initializeMovies(); // Initialize movies at compile time
    platform.initializeShows(); // Initialize shows at compile time
    int choice;

    while (true) {
        clearScreen();
        heading();
        displayRegistrationLoginOptions();
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            cout << "1. User Registration\n";
            cout << "2. Manager Registration\n";
            cout << "Enter your choice: ";
            cin >> choice;
            if (choice == 1) {
                handleUserRegistration(platform);
            } else if (choice == 2) {
                handleManagerRegistration(platform);
            } else {
                cout << "Invalid choice!" << endl;
            }
        } else if (choice == 2) {
            clearScreen();
            cout << "1. User Login\n";
            cout << "2. Manager Login\n";
            cout << "Enter your choice: ";
            int newChoice;
            cin >> newChoice;
            if (newChoice == 1) {
                handleUserLogin(platform);
                int userChoice; // Add a new variable to store user menu choice
                while (userChoice != 5) {
                        heading();// Change condition to userChoice
                    displayUserMenu();
                    cin >> userChoice; // Use userChoice variable for input
                    switch (userChoice) {
                        case 1:
                            platform.browseMovies();
                            break;
                        case 2: {
                            string username;
                            int showId;
                            cout << "Enter username: ";
                            cin >> username;
                            cout << "Enter show ID: ";
                            cin >> showId;
                            platform.bookTicket(username, showId);
                            break;
                        }
                        case 3: {
                            string username;
                            int ticketId;
                            cout << "Enter username: ";
                            cin >> username;
                            cout << "Enter ticket ID: ";
                            cin >> ticketId;
                            platform.cancelTicket(username, ticketId);
                            break;
                        }
                        case 4: {
                            string username, review;
                            int movieId;
                            cout << "Enter username: ";
                            cin >> username;
                            cout << "Enter movie ID: ";
                            cin >> movieId;
                            cout << "Enter review: ";
                            cin.ignore();
                            getline(cin, review);
                            platform.addReview(username, movieId, review);
                            break;
                        }
                        case 5:
                            platform.setUserLoggedIn(false); // Logout user
                            cout << "Logged out successfully!" << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                            break;
                    }
                }
            } else if (newChoice == 2) {
                handleManagerLogin(platform);
                while (choice != 5) {
                        heading();
                    displayManagerMenu();
                    cin >> choice;
                    switch (choice) {
                        case 1:
                            platform.browseMovies();
                            break;
                        case 2: {
                            string title;
                            int numTickets;
                            double cost;
                            cout << "Enter the title of the movie: ";
                            cin.ignore();
                            getline(cin, title);
                            cout << "Enter the number of tickets: ";
                            cin >> numTickets;
                            cout << "Enter the cost of a ticket: ";
                            cin >> cost;
                            platform.addMovie(title, numTickets, cost);
                            break;
                        }
                        case 3: {
                            int movieId;
                            string datetime;
                            cout << "Enter movie ID: ";
                            cin >> movieId;
                            cout << "Enter show datetime: ";
                            cin.ignore();
                            getline(cin, datetime);
                            platform.addShow(movieId, datetime);
                            break;
                        }
                        case 4:
                            platform.manageReviews();
                            break;
                        case 5:
                            platform.setManagerLoggedIn(false); // Logout manager
                            cout << "Logged out successfully!" << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                            break;
                    }
                }
            } else {
                cout << "Invalid choice!" << endl;
            }
        } else if (choice == 3) {
            // Exit the program
            return 0;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
