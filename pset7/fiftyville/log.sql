-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Checking for report about theft of duck
SELECT * FROM crime_scene_reports WHERE month = 7 AND day = 28;

-- Important result: check interviews mentioning bakery!
--| 295 | 2021 | 7     | 28  | Humphrey Street      | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery. |

-- Checking interviews with bakery mentioned in the transcript
SELECT * FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE '%bakery%';

-- 