-- Keep a log of any SQL queries you execute as you solve the mystery.

.tables
.schema

-- 查看当天犯罪记录
SELECT *
FROM crime_scene_reports
WHERE year = 2021
AND month = 7
AND day = 28
AND street = "Humphrey Street";

-- 查看当天三位目击者关于小偷的采访记录
SELECT *
FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE "%thief%";

-- 停车不到10分钟出去的人
SELECT name
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15
AND minute <= 25
AND activity = "exit")
ORDER BY name;

-- 在Leggett Street取钱的人
SELECT name
FROM people, bank_accounts
WHERE people.id = bank_accounts.person_id
AND account_number IN
(SELECT account_number
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = "Leggett Street"
AND transaction_type = "withdraw")
ORDER BY name;

-- 买转天最早的机票的人
SELECT name
FROM people
WHERE passport_number IN
(SELECT passport_number
FROM passengers
WHERE flight_id IN
(SELECT id
FROM flights
WHERE year = 2021
AND month = 7
AND day = 29
AND origin_airport_id IN
(SELECT id
FROM airports
WHERE city = "Fiftyville")
ORDER BY hour
LIMIT 1))
ORDER BY name;

-- 当天打了不到一分钟的电话的人
SELECT name
FROM people
WHERE phone_number IN
(SELECT caller
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60)
ORDER BY name;
