-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Checking for report about theft of duck
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;

-- Deduction: check interviews mentioning bakery!
--| 295 | 2021 | 7     | 28  | Humphrey Street      | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery. |

-- Checking interviews with bakery mentioned in the transcript
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- Deduction: Withdrew money from ATM on Leggett Street. Left the bakery parking lot within 10 minutes of the theft (10:15-10:25 am). Planned to take earliest flight out of Fiftyville on 29/7/2021
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

-- Searching for earliest flights out of Fiftyville on 29/7/2021