-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Checking for report about theft of duck
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;

-- Deduction: check interviews mentioning bakery!
--| 295 | 2021 | 7     | 28  | Humphrey Street      | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery. |

-- Checking interviews with bakery mentioned in the transcript
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Deduction: Withdrew money from ATM on Leggett Street. Left the bakery parking lot within 10 minutes of the theft (10:15-10:25 am). Planned to take earliest flight out of Fiftyville on 29 July 2021
--| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- Checking for Leggett Street ATM withdrawals.
SELECT atm_transactions.id, name, amount FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE atm_location = 'Leggett Street' AND month = 7 AND day = 28 AND transaction_type = 'withdraw';

-- Deduction: Suspect is one of these 8 people
-- | 267 | Bruce   | 50     |
-- | 336 | Diana   | 35     |
-- | 269 | Brooke  | 80     |
-- | 264 | Kenny   | 20     |
-- | 288 | Iman    | 20     |
-- | 246 | Luca    | 48     |
-- | 266 | Taylor  | 60     |
-- | 313 | Benista | 30     |

-- Checking for Cars and owner leaving bakery parking lot
SELECT bakery_security_logs.id, name, people.license_plate FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE day = 28 AND month = 7 AND activity = 'exit' AND hour = 10 AND minute < 25;

-- Deduction: Suspect is one of these 8 people
-- | 260 | Vanessa | 5P2BI95       |
-- | 261 | Bruce   | 94KL13X       |
-- | 262 | Barry   | 6P58WS2       |
-- | 263 | Luca    | 4328GD8       |
-- | 264 | Sofia   | G412CB7       |
-- | 265 | Iman    | L93JTIZ       |
-- | 266 | Diana   | 322W7JE       |
-- | 267 | Kelsey  | 0NTHK55       |

-- From combining the previous 2 we can see that suspect is either Bruce, Diana, Iman or Luca.

-- Searching for earliest flights out of Fiftyville on 29 July 2021
SELECT * FROM flights WHERE month = 7 AND day = 29 ORDER BY hour ASC, minute ASC;

-- Deduction: Suspect got on flight id: 36 at 8:20 on 29 July 2021 from Fiftyville Regional Airport to LaGuardia Airport
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
-- | 23 | 8                 | 11                     | 2021 | 7     | 29  | 12   | 15     |
-- | 53 | 8                 | 9                      | 2021 | 7     | 29  | 15   | 20     |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      |

-- Searching for passengers on flight 36
SELECT flight_id, name, passengers.passport_number, seat FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = 36;

-- Deduction: Suspect is either Bruce or Lucas
-- | 36        | Doris  | 7214083635      | 2A   |
-- | 36        | Sofia  | 1695452385      | 3B   |
-- | 36        | Bruce  | 5773159633      | 4A   |
-- | 36        | Edward | 1540955065      | 5C   |
-- | 36        | Kelsey | 8294398571      | 6C   |
-- | 36        | Taylor | 1988161715      | 6D   |
-- | 36        | Kenny  | 9878712108      | 7A   |
-- | 36        | Luca   | 8496433585      | 7B   |

-- Searching for caller and receiver of less than 1 minute call on 28 July
SELECT phone_calls.id, name, receiver FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE month = 7 AND day = 28 AND duration < 60;

-- Deduction: caller is Bruce and receiver is Luca
-- | 221 | Sofia   | (996) 555-8899 |
-- | 224 | Kelsey  | (892) 555-8872 |
-- | 233 | Bruce   | (375) 555-8161 |
-- | 251 | Kelsey  | (717) 555-1342 |
-- | 254 | Taylor  | (676) 555-6554 |
-- | 255 | Diana   | (725) 555-3243 |
-- | 261 | Carina  | (910) 555-3251 |
-- | 279 | Kenny   | (066) 555-9701 |
-- | 281 | Benista | (704) 555-2131 |