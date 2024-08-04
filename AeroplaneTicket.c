#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_FLIGHTS 3
#define MAX_SEATS_PER_FLIGHT 50
#define BUSINESS_CLASS_SEATS 10
#define ECONOMY_CLASS_SEATS 40

typedef struct Flight
{
  char flightNumber[10];
  char departureCity[50];
  char arrivalCity[50];
  char departureTime[20];
  char arrivalTime[20];
  int availableBusinessSeats;
  int availableEconomySeats;
  struct Flight *next;
} Flight;

typedef struct Passenger
{
  char name[50];
  int age;
  char seatClass;
  int seatNumber;
  char flightNumber[10];
  struct Passenger *next;
} Passenger;

Flight *createFlight(char *flightNumber, char *departureCity, char *arrivalCity, char *departureTime, char *arrivalTime)
{
  Flight *newFlight = (Flight *)malloc(sizeof(Flight));
  if (newFlight == NULL)
  {
    printf("Memory allocation failed!\n");
    exit(1);
  }
  strcpy(newFlight->flightNumber, flightNumber);
  strcpy(newFlight->departureCity, departureCity);
  strcpy(newFlight->arrivalCity, arrivalCity);
  strcpy(newFlight->departureTime, departureTime);
  strcpy(newFlight->arrivalTime, arrivalTime);
  newFlight->availableBusinessSeats = BUSINESS_CLASS_SEATS;
  newFlight->availableEconomySeats = ECONOMY_CLASS_SEATS;
  newFlight->next = NULL;
  return newFlight;
}

void displayFlights(Flight *head, Passenger *passengers)
{
  if (head == NULL)
  {
    printf("No available flights to display.\n");
    return;
  }
  Flight *currentFlight = head;
  printf("\nAvailable Flights:\n");
  while (currentFlight != NULL)
  {
    int bookedBusinessSeats = 0;
    int bookedEconomySeats = 0;
    Passenger *currentPassenger = passengers;
    while (currentPassenger != NULL)
    {
      if (strcmp(currentPassenger->flightNumber, currentFlight->flightNumber) == 0)
      {
        if (currentPassenger->seatClass == 'B')
        {
          bookedBusinessSeats++;
        }
        else if (currentPassenger->seatClass == 'E')
        {
          bookedEconomySeats++;
        }
      }
      currentPassenger = currentPassenger->next;
    }
    int availableBusinessSeats = BUSINESS_CLASS_SEATS - bookedBusinessSeats;
    int availableEconomySeats = ECONOMY_CLASS_SEATS - bookedEconomySeats;
    printf("Flight Number: %s | Departure City: %s | Arrival City: %s | Departure Time: %s | Arrival Time: %s | Business Seats: %d | Economy Seats: %d\n",
           currentFlight->flightNumber, currentFlight->departureCity, currentFlight->arrivalCity, currentFlight->departureTime, currentFlight->arrivalTime,
           availableBusinessSeats, availableEconomySeats);
    currentFlight = currentFlight->next;
  }
  printf("\n");
}

void updateAvailableSeats(Flight *head, Passenger *passengers)
{
  Flight *currentFlight = head;
  while (currentFlight != NULL)
  {
    int bookedBusinessSeats = 0;
    int bookedEconomySeats = 0;
    Passenger *currentPassenger = passengers;
    while (currentPassenger != NULL)
    {
      if (strcmp(currentPassenger->flightNumber, currentFlight->flightNumber) == 0)
      {
        if (currentPassenger->seatClass == 'B')
        {
          bookedBusinessSeats++;
        }
        else if (currentPassenger->seatClass == 'E')
        {
          bookedEconomySeats++;
        }
      }
      currentPassenger = currentPassenger->next;
    }
    currentFlight->availableBusinessSeats = BUSINESS_CLASS_SEATS - bookedBusinessSeats;
    currentFlight->availableEconomySeats = ECONOMY_CLASS_SEATS - bookedEconomySeats;
    currentFlight = currentFlight->next;
  }
}

void displayTicketDetails(Passenger *head, Flight *flights)
{
  if (head == NULL)
  {
    printf("No booked tickets to display.\n");
    return;
  }
  Passenger *current = head;
  printf("\nTicket Details:\n");
  while (current != NULL)
  {
    Flight *currentFlight = flights;
    while (currentFlight != NULL && strcmp(currentFlight->flightNumber, current->flightNumber) != 0)
    {
      currentFlight = currentFlight->next;
    }
    if (currentFlight != NULL)
    {
      printf("Flight Number: %s | Departure City: %s | Arrival City: %s | Departure Time: %s | Arrival Time: %s | ",
             currentFlight->flightNumber, currentFlight->departureCity, currentFlight->arrivalCity, currentFlight->departureTime, currentFlight->arrivalTime);
    }
    printf("Name: %s | Age: %d | Seat Class: %c | Seat Number: %d\n",
           current->name, current->age, current->seatClass, current->seatNumber);
    current = current->next;
  }
  printf("\n");
}

bool bookSeat(Flight *head, Passenger **passengerList, char *flightNumber, char seatClass)
{
  Flight *currentFlight = head;
  while (currentFlight != NULL)
  {
    if (strcmp(currentFlight->flightNumber, flightNumber) == 0)
    {
      double price;
      double discount = 0.0;

      if (seatClass == 'B' && currentFlight->availableBusinessSeats > 0)
      {
        Passenger *newPassenger = (Passenger *)malloc(sizeof(Passenger));
        if (newPassenger == NULL)
        {
          printf("Memory allocation failed!\n");
          return false;
        }
        newPassenger->seatClass = 'B';
        newPassenger->seatNumber = BUSINESS_CLASS_SEATS - currentFlight->availableBusinessSeats + 1;
        currentFlight->availableBusinessSeats--;
        price = 500.0;
        printf("price for business class is $500\n");

        strcpy(newPassenger->flightNumber, flightNumber);
        printf("Enter Passenger Name: ");
        scanf("%s", newPassenger->name);

        printf("Enter Passenger Age: ");
        scanf("%d", &newPassenger->age);

        printf("Payment methods available:\n");
        printf("1. GPay\n");
        printf("2. PhonePe\n");
        printf("3. Paytm\n");
        printf("4. Debit Card\n");
        printf("5. Credit Card\n");
        printf("6. Online Banking\n");
        int paymentMethod;
        printf("Choose payment method (1-6): ");
        scanf("%d", &paymentMethod);

        switch (paymentMethod)
        {
        case 1:
        case 2:
        case 3:
          printf("Paid using GPay/PhonePe/Paytm.\n");
          discount = 0.07;
          break;
        case 4:
        case 5:
        case 6:
          printf("Paid using Debit Card/Credit Card/Online Banking.\n");
          discount = 0.12;
          break;
        default:
          printf("Invalid payment method.\n");
          free(newPassenger);
          return false;
        }

        double discountedPrice = price * (1.0 - discount);
        printf("Discount Applied: %.2f%%\n", discount * 100.0);
        printf("Total Price after Discount: $%.2f\n", discountedPrice);

        printf("Ticket booked successfully!\n");

        newPassenger->next = *passengerList;
        *passengerList = newPassenger;

        return true;
      }
      else if (seatClass == 'E' && currentFlight->availableEconomySeats > 0)
      {
        Passenger *newPassenger = (Passenger *)malloc(sizeof(Passenger));
        if (newPassenger == NULL)
        {
          printf("Memory allocation failed!\n");
          return false;
        }
        newPassenger->seatClass = 'E';
        newPassenger->seatNumber = ECONOMY_CLASS_SEATS - currentFlight->availableEconomySeats + 1;
        currentFlight->availableEconomySeats--;
        price = 100.0;
        printf("price for economy class is $100\n");

        strcpy(newPassenger->flightNumber, flightNumber);
        printf("Enter Passenger Name: ");
        scanf("%s", newPassenger->name);

        printf("Enter Passenger Age: ");
        scanf("%d", &newPassenger->age);

        printf("Payment methods available:\n");
        printf("1. GPay\n");
        printf("2. PhonePe\n");
        printf("3. Paytm\n");
        printf("4. Debit Card\n");
        printf("5. Credit Card\n");
        printf("6. Online Banking\n");
        int paymentMethod;
        printf("Choose payment method (1-6): ");
        scanf("%d", &paymentMethod);

        switch (paymentMethod)
        {
        case 1:
        case 2:
        case 3:
          printf("Paid using GPay/PhonePe/Paytm.\n");
          discount = 0.07;
          break;
        case 4:
        case 5:
        case 6:
          printf("Paid using Debit Card/Credit Card/Online Banking.\n");
          discount = 0.12;
          break;
        default:
          printf("Invalid payment method.\n");
          free(newPassenger);
          return false;
        }

        double discountedPrice = price * (1.0 - discount);
        printf("Discount Applied: %.2f%%\n", discount * 100.0);
        printf("Total Price after Discount: $%.2f\n", discountedPrice);

        printf("Ticket booked successfully!\n");

        newPassenger->next = *passengerList;
        *passengerList = newPassenger;

        return true;
      }
      else
      {
        printf("No available seats in the specified class.\n");
        return false;
      }
    }
    currentFlight = currentFlight->next;
  }
  printf("Invalid flight number.\n");
  return false;
}

void deleteTicket(Passenger **headRef, char *flightNumber, int seatNumber)
{
  Passenger *current = *headRef;
  Passenger *prev = NULL;

  while (current != NULL)
  {
    if (strcmp(current->flightNumber, flightNumber) == 0 && current->seatNumber == seatNumber)
    {
      if (current->seatClass == 'B')
      {
        current->seatClass = ' ';
      }
      else if (current->seatClass == 'E')
      {
        current->seatClass = ' ';
      }

      if (prev == NULL)
      {
        *headRef = current->next;
      }
      else
      {
        prev->next = current->next;
      }
      free(current);
      printf("Ticket deleted successfully.\n");
      printf("7 percent has been deducted. remaining amount will be sent to your original payment method\n");
      return;
    }
    prev = current;
    current = current->next;
  }

  printf("Ticket not found.\n");
}

bool checkLogin(char *username, char *password)
{
  return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void freeFlights(Flight *head)
{
  while (head != NULL)
  {
    Flight *temp = head;
    head = head->next;
    free(temp);
  }
}

void freePassengers(Passenger *head)
{
  while (head != NULL)
  {
    Passenger *temp = head;
    head = head->next;
    free(temp);
  }
}

int main()
{
  char username[50];
  char password[50];
  Flight *flights = NULL;
  Passenger *passengers = NULL;

  flights = createFlight("AI101", "Chennai", "Sri lanka", "09:00", "12:00");
  flights->next = createFlight("AI202", "Bengaluru", "Mumbai", "13:00", "16:00");
  flights->next->next = createFlight("AI303", "Gujarat", "Delhi", "18:00", "21:00");

  printf("Welcome to Airline Ticket Reservation System\n");
  printf("--------------------------------------------\n");
  printf("Please login to continue.\n");

  printf("Username: ");
  scanf("%s", username);
  printf("Password: ");
  scanf("%s", password);

  if (!checkLogin(username, password))
  {
    printf("Invalid credentials. Exiting program.\n");
    freeFlights(flights);
    return 1;
  }

  int choice;
  do
  {
    printf("\n1. Display Available Flights\n");
    printf("2. Book a Seat\n");
    printf("3. Display Ticket Details\n");
    printf("4. Delete a Ticket\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      updateAvailableSeats(flights, passengers);
      displayFlights(flights, passengers);
      break;
    case 2:
    {
      char flightNumber[10];
      char seatClass;
      printf("Enter Flight Number: ");
      scanf("%s", flightNumber);

      printf("Enter Seat Class (B for Business, E for Economy): ");
      scanf(" %c", &seatClass);

      if (bookSeat(flights, &passengers, flightNumber, seatClass))
      {
      }
    }
    break;
    case 3:
      displayTicketDetails(passengers, flights);
      break;
    case 4:
    {
      int seatNumber;
      char flightNumber[10];
      printf("Enter Flight Number: ");
      scanf("%s", flightNumber);
      printf("Enter Seat Number to delete ticket: ");
      scanf("%d", &seatNumber);
      deleteTicket(&passengers, flightNumber, seatNumber);
    }
    break;
    case 5:
      printf("Exiting program.\n");
      break;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  } while (choice != 5);

  freeFlights(flights);
  freePassengers(passengers);

  return 0;
}
