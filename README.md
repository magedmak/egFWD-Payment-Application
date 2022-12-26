# Payment Application
## Introduction
This payment application is a simulation of a card payment system. It allows the user to input their card details, terminal details, and transaction details to make a payment. The application checks the validity of the inputted data and communicates with a server to determine the final transaction status. The transaction can be either approved or declined based on the inputted data and the server's records.

## Project Structure               
<object data="Solution Explorer.pdf" type="application/pdf" width="700px" height="700px">
    <embed src="Solution Explorer.pdf">
        <p>Please check the PDF: <a href="Solution Explorer.pdf">Solution Explorer</a>.</p>
    </embed>
</object>

## Features
- Input and verify card holder information (name, expiration date, primary account number).
- Input and verify terminal information (transaction date, transaction amount, maximum transaction amount).
- Check if card is expired or has exceeded the maximum transaction amount.
- Save transaction data and handle any errors that may occur during the process.
- End the application when desired.

## Components
The payment application consists of four main components:

1. Card: This component handles the input and validation of the card details, including the cardholder's name, expiration date, and primary account number (PAN).

2. Terminal: This component handles the input and validation of the terminal details, including the transaction date and amount. It also has the ability to set a maximum transaction amount.

3. Server: This component communicates with the card and terminal components to verify the inputted data and determine the transaction status. It also has a database of accounts and transactions, and it updates the account balance and saves the transaction details after a successful payment.

4. App: This component acts as the main entry point of the application. It controls the flow of the program and calls the functions of the other components.

## Demonstration Videos
- [card.c](https://drive.google.com/file/d/1DzpeB7fRVA9ni02tApA8KUu2frGgTCmN/view?usp=share_link)
- [terminal.c](https://drive.google.com/file/d/1s6CSPVfvCqQbNXg1ZmhrpcA-C35_tzIw/view?usp=share_link)
- [server.c](https://drive.google.com/file/d/1eSRU0snKd9s-Bf7WocSZNrigk6DIWOfo/view?usp=share_link)
- [app.c](https://drive.google.com/file/d/1wmKTeoiQDzB2SzlSPxBvgyWuoR_9Ocl8/view?usp=share_link)

## Usage
To use the payment application, the user needs to provide the following information:

- Cardholder's name: The user needs to input their full name as it appears on their card. The name should be between 20 and 24 characters long.

- Card expiration date: The user needs to input the expiration date of their card in the format "MM/YY". The date should be 5 characters long.

- Primary account number (PAN): The user needs to input their card's PAN, which is a unique 16-19 digit number.

- Transaction date: The user needs to input the date of the transaction in the format "DD/MM/YYYY". The date should be 10 characters long.

- Transaction amount: The user needs to input the amount of the transaction in dollars. The amount should be a positive number.

The application will then check the inputted data for errors and communicate with the server to determine the transaction status. If the transaction is approved, the app will update the account balance and save the transaction details. If the transaction is declined, the app will display an error message explaining the reason for the decline.

## Limitations
- The application can only handle transactions up to a maximum amount, which is currently set to $3000.

- The application can only handle a limited number of accounts and transactions, which is currently set to 255.

- The application does not currently have the ability to connect to a real server, so it uses a simulated server with a pre-populated database of accounts and transactions.

- The application does not currently have any security measures in place to protect the user's personal and financial information.

## Conclusion
This payment application is a simple simulation of a card payment system, designed for educational and demonstration purposes only. It is not intended for use in real-world financial transactions.

## Copyright
This payment application was developed as part of the egFWD scholarship program. Copyright (c) 2021 Maged Magdy. All rights reserved.

## Contact
For any inquiries or questions about the application, please contact the author at magedmagdy.engr@gmail.com.
