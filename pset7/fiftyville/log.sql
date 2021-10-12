-- Keep a log of any SQL queries you execute as you solve 
-- the mystery.


SELECT * FROM interviews WHERE
year = 2020 AND
month = 7 AND
day = 28;

-- theft took place:
-- July 28, 2020
-- on Chamberlin Street
-- Get first flight leaving Fiftyville on the 29th



SELECT * FROM flights WHERE
year = 2020 AND
month = 7 AND
day = 29 AND
origin_airport_id = (
SELECT id FROM airports
WHERE city = "Fiftyville")
ORDER BY hour LIMIT 1;

-- To get the purp use...
SELECT * FROM people WHERE id IN 
(SELECT person_id FROM bank_accounts WHERE
account_number IN
(SELECT account_number FROM atm_transactions WHERE
atm_location = "Fifer Street" AND
year = 2020 AND
month = 7 AND
day = 28)) AND license_plate IN
(SELECT license_plate FROM courthouse_security_logs
WHERE year = 2020 AND
month = 7 AND
day = 28 AND
hour = 10 AND
minute >= 15 AND
minute <= 25)
AND phone_number IN (
SELECT caller FROM phone_calls WHERE
year = 2020 AND
month = 7 AND
day = 28 AND
duration < 60) AND
passport_number IN
(SELECT passport_number FROM passengers
WHERE flight_id = 36);

-- To get accomplice check who the theif called
SELECT * FROM people 
WHERE phone_number = "(375) 555-8161";
