-- find a report that matches the when/where of the crime
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND year = 2023 AND street = "Humphrey Street";
-- theft at 10:15, three witnesses
-- littering at 16:36, no known witnesses

-- find transcripts of witness interviews
SELECT transcript
FROM interviews
WHERE day = 28 AND month = 7 AND year = 2023;
-- thief inside 10m after theft left bakery in a car
-- thief withdrew from leggett atm before getting to bakery
-- thief made >1m call asking to take earliest flight out tomorrow, made other person purchase ticket
-- city might be paris?

-- failed attempt to find license plate
SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10 AND minute < 25 AND minute > 15;

-- find atm locations
SELECT atm_location
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2023;

-- find numbers used on this day at the leggett atm
SELECT account_number
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street";

-- find the types of the transactions
SELECT transaction_type
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street" AND account_number IN (
    SELECT account_number
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street"
);

-- find the names of the people with those accounts
SELECT name
FROM people
WHERE people.id IN (
    SELECT person_id
    FROM bank_accounts
    JOIN people ON bank_accounts.person_id = people.id
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28 AND month = 7 AND year = 2023 AND atm_location = "Leggett Street"
    )
)
ORDER BY name;
-- +---------+
-- |  name   |
-- +---------+
-- | Benista |
-- | Brooke  |
-- | Bruce   |
-- | Diana   |
-- | Iman    |
-- | Kaelyn  |
-- | Kenny   |
-- | Luca    |
-- | Taylor  |
-- +---------+


-- find the earliest flights the next day
SELECT flights.id, hour, minute
FROM flights
WHERE day = 29 AND month = 7 AND year = 2023
ORDER BY hour, minute;
--+----+------+--------+
--| id | hour | minute |
--+----+------+--------+
--| 36 | 8    | 20     |
--| 43 | 9    | 30     |
--| 23 | 12   | 15     |
--| 18 | 16   | 0      |
--+----+------+--------+

-- find the passengers on the earliest flight
SELECT name
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
)
ORDER BY name;
-- +--------+
-- |  name  |
-- +--------+
-- | Bruce  |
-- | Doris  |
-- | Edward |
-- | Kelsey |
-- | Kenny  |
-- | Luca   |
-- | Sofia  |
-- | Taylor |
-- +--------+

-- kenny, taylor, and bruce both made withdrawals on leggett street day of and flew out next day

-- check their license plates
SELECT license_plate, name
FROM people
WHERE name = "Kenny" OR name = "Taylor" OR name = "Bruce";
-- 30G67EN kenny
-- 1106N58 taylor
-- 94KL13X bruce

-- license plate time again - checking for license plates seen after 10:15 but before 10:25,
-- and would you look at that, bruce's plate is there!
SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 AND month = 7 AND year = 2023 AND hour = 10 AND minute < 25 AND minute > 15;
-- +---------------+
-- | license_plate |
-- +---------------+
-- | 5P2BI95       |
-- | 94KL13X       |
-- | 6P58WS2       |
-- | 4328GD8       |
-- | G412CB7       |
-- | L93JTIZ       |
-- | 322W7JE       |
-- | 0NTHK55       |
-- +---------------+

-- find flight 36's destination
SELECT city
FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.id = 36 AND day = 29 AND month = 7 AND year = 2023;
-- new york city

-- find the phone call that bruce made after leaving the bakery
SELECT receiver, duration
FROM phone_calls
WHERE caller IN (
    SELECT phone_number
    FROM people
    WHERE name = "Bruce"
) AND day = 28 AND month = 7 AND year = 2023
ORDER BY duration;
-- +----------------+----------+
-- |    receiver    | duration |
-- +----------------+----------+
-- | (375) 555-8161 | 45       |
-- | (704) 555-5790 | 75       |
-- | (344) 555-9601 | 120      |
-- | (022) 555-4052 | 241      |
-- +----------------+----------+
-- we can see that less than 1m call, so we know the 375 number is the accomplice

-- find the accomplice's name
SELECT name
FROM people
WHERE phone_number = "(375) 555-8161";
-- Robin
