-- Log of SQL queries executed to solve the mystery

-- Get information about the tables of the database
.tables

-- Get information about the atributes of crime_scene_reports
.schema crime_scene_reports

-- Since the description seems useful, select it, knowing all the other informations
SELECT description
  FROM crime_scene_reports
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND street = 'Humphrey Street';

/*
Accurate description:
    Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    Interviews were conducted today with three witnesses who were present at the time –
    each of their interview transcripts mentions the bakery.
*/

-- Get information about the atributes of interviews, following the description's hint
.schema interviews

-- Since the transcripts seem useful, select them, knowing all the other informations
SELECT name, transcript
  FROM interviews
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND transcript LIKE '%bakery%';  -- Each of their interview transcripts mentions the bakery

/*
Accurate interviews:
    Name: Ruth
    Transcript: Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
    If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

    Name: Eugene
    Transcript: I don't know the thief's name, but it was someone I recognized.
    Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

    Name: Raymond
    Transcript: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
    In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
    The thief then asked the person on the other end of the phone to purchase the flight ticket.
*/

-- Get information about the atributes of bakery_security_logs, following Ruth's hint
.schema bakery_security_logs

-- Since the license plates seem useful, select them, knowing all the other informations
SELECT license_plate
  FROM bakery_security_logs
 WHERE minute BETWEEN 5 AND 25  -- Sometime within ten minutes of the theft, that happened at 10h15am
   AND hour = 10
   AND day = 28
   AND month = 7
   AND year = 2021
   AND activity = 'exit';  -- Cars that left the parking lot

/*
Possible suspects license plates:
    +---------------+
    | license_plate |
    +---------------+
    | 5P2BI95       |
    | 94KL13X       |
    | 6P58WS2       |
    | 4328GD8       |
    | G412CB7       |
    | L93JTIZ       |
    | 322W7JE       |
    | 0NTHK55       |
    +---------------+
*/

-- Get information about the atributes of atm_transactions, following Eugene's hint
.schema atm_transactions

-- Since the account numbers seem useful, select them, knowing all the other informations
SELECT account_number
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location = 'Leggett Street'  -- The ATM on Leggett Street
   AND transaction_type = 'withdraw';  -- Saw the thief there withdrawing some money

/*
Possible suspects accounts numbers:
    +----------------+
    | account_number |
    +----------------+
    | 28500762       |
    | 28296815       |
    | 76054385       |
    | 49610011       |
    | 16153065       |
    | 25506511       |
    | 81061156       |
    | 26013199       |
    +----------------+
*/

-- Get information about the atributes of bank_accounts, that allows to get to a person's id knowing their account number
.schema bank_accounts

-- Since the person ids seem useful, select them through implicit join, knowing the suspects' account numbers
SELECT person_id
  FROM bank_accounts, atm_transactions
 WHERE bank_accounts.account_number = atm_transactions.account_number
   AND day = 28
   AND month = 7
   AND year = 2021
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';

/*
Possible suspects ids:
    +-----------+
    | person_id |
    +-----------+
    | 467400    |
    | 395717    |
    | 449774    |
    | 686048    |
    | 458378    |
    | 396669    |
    | 438727    |
    | 514354    |
    +-----------+
*/

-- Get information about the atributes of phone_calls, following Raymond's hint
.schema phone_calls

-- Since the callers' phone numbers seem useful, select them, knowing all the other informations
SELECT caller
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND duration < 60;

/*
Possible suspects phone numbers:
    +----------------+
    |     caller     |
    +----------------+
    | (130) 555-0289 |
    | (499) 555-9472 |
    | (367) 555-5533 |
    | (499) 555-9472 |
    | (286) 555-6063 |
    | (770) 555-1861 |
    | (031) 555-6622 |
    | (826) 555-1652 |
    | (338) 555-6650 |
    +----------------+
*/

-- Get information about the atributes of flights, airports and passengers, following another Raymond's hint
.schema flights
.schema airports
.schema passengers

-- Since the passport numbers seem useful, select them through nested queries and join, knowing all the other informations
SELECT passport_number
  FROM passengers
 WHERE flight_id =
       -- Get the id of the flight the thief was in
       (SELECT flights.id
          FROM flights
          JOIN airports
            ON flights.origin_airport_id = airports.id
         WHERE day = 29  -- Take the earliest flight out of Fiftyville tomorrow, and the theft happened day 28
           AND month = 7
           AND year = 2021
           AND city = 'Fiftyville'  -- Flights leaving Fiftyville, since join was on origin_airport_id
         ORDER BY hour, minute  -- Order by the first flights chronologically
         LIMIT 1);  -- Get only the first flight out of Fiftyville that day


/*
Possible suspects passport numbers:
    +-----------------+
    | passport_number |
    +-----------------+
    | 7214083635      |
    | 1695452385      |
    | 5773159633      |
    | 1540955065      |
    | 8294398571      |
    | 1988161715      |
    | 9878712108      |
    | 8496433585      |
    +-----------------+
*/

-- Get information about the atributes of people, since all informations about the thief were gathered
.schema people

-- To get to the thief's name, select their name from people's table, combining all informations found
SELECT name AS thief
  FROM people

 WHERE id IN
       (SELECT person_id
          FROM bank_accounts, atm_transactions
         WHERE bank_accounts.account_number = atm_transactions.account_number
           AND day = 28
           AND month = 7
           AND year = 2021
           AND atm_location = 'Leggett Street'
           AND transaction_type = 'withdraw')

   AND phone_number IN
       (SELECT caller
          FROM phone_calls
         WHERE day = 28
           AND month = 7
           AND year = 2021
           AND duration < 60)

   AND passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id =
               (SELECT flights.id
                  FROM flights
                  JOIN airports
                    ON flights.origin_airport_id = airports.id
                 WHERE day = 29
                   AND month = 7
                   AND year = 2021
                   AND city = 'Fiftyville'
                 ORDER BY hour, minute
                 LIMIT 1))

   AND license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE minute BETWEEN 5 AND 25
           AND hour = 10
           AND day = 28
           AND month = 7
           AND year = 2021
           AND activity = 'exit');

/*
Thief:
    +-------+
    | thief |
    +-------+
    | Bruce |
    +-------+
*/

-- To get to the city the thief escaped to, select the city from the destination airport of the flight the thief was in
SELECT city AS city_escaped
  FROM airports, flights
 WHERE airports.id = flights.destination_airport_id
   AND day = 29
   AND month = 7
   AND year = 2021
   AND origin_airport_id IN
       (SELECT id
          FROM airports
         WHERE city = 'Fiftyville')
 ORDER BY hour, minute
 LIMIT 1;

/*
City the thief escaped to:
    +---------------+
    | city_escaped  |
    +---------------+
    | New York City |
    +---------------+
*/

-- To get to the accomplice's name, select the phone number that received the call (that Raymond alluded to) from the thief
SELECT name AS accomplice
  FROM people
  JOIN phone_calls
    ON people.phone_number = phone_calls.receiver
 WHERE caller =
       (SELECT phone_number
          FROM people
         WHERE name = 'Bruce')  -- Already found as the thief
           AND day = 28
           AND month = 7
           AND year = 2021
           AND duration < 60;

/*
Accomplice:
    +-------------+
    | accomplice  |
    +-------------+
    | Robin       |
    +-------------+
*/
