-- Keep a log of any SQL queries you execute as you solve the mystery.

-- FIND THE SPECIFIC CRIME REPORT
WITH CTE_CRIME AS (
    SELECT *
      FROM crime_scene_reports
     WHERE year = 2023
       AND month = 7
       AND day = 28
       AND street LIKE 'Humphrey St%'
       AND description LIKE '%duck%'
)

-- FIND THE 3 WITNESSES
,CTE_WITNESS AS (
    SELECT *
      FROM interviews
     WHERE transcript LIKE '%bakery%'
       AND year = 2023
       AND month = 7
       AND day = 28
)

-- FIND PEOPLE IN THE BAKERY AT THE TIME OF THE CRIME
,CTE_BAKERY_SECURITY_TIME AS (
    SELECT license_plate
           ,activity
           ,datetime(year || '-' || substr('0' || month, -2, 2) || '-' || substr('0' || day, -2, 2) || ' ' || substr('0' || hour, -2, 2) || ':' || substr('0' || minute, -2, 2) || ':00') AS date_time
      FROM bakery_security_logs
)

,CTE_PEOPLE_LEAVING_BAKERY AS (
    SELECT *
      FROM CTE_BAKERY_SECURITY_TIME
     WHERE activity = 'exit'
       AND date_time BETWEEN datetime('2023-07-28 10:15:00') AND datetime('2023-07-28 10:25:00')
)

-- FIND PEOPLE WHO WITHDREW MONEY THAT MORNING
,CTE_WITHDREW_MONEY AS (
    SELECT *
      FROM atm_transactions
     WHERE year = 2023
       AND month = 7
       AND day = 28
       AND transaction_type = 'withdraw'
       AND atm_location = 'Leggett Street'
)

-- FIND PEOPLE ON THAT DAY WHO MADE A PHONE CALL OF LESS THAN A MINUTE
,CTE_PHONE_CALL AS (
    SELECT *
      FROM phone_calls
     WHERE duration <= 60
       AND year = 2023
       AND month = 7
       AND day = 28
)

-- FIND PEOPLE WHO TOOK THE EARLIEST FLIGHT THE NEXT DAY
,CTE_FLIGHTS AS (
    SELECT *
           ,datetime(year || '-' || substr('0' || month, -2, 2) || '-' || substr('0' || day, -2, 2) || ' ' || substr('0' || hour, -2, 2) || ':' || substr('0' || minute, -2, 2) || ':00') AS date_time
      FROM flights
     WHERE origin_airport_id = (SELECT id
                                  FROM airports
                                 WHERE city = 'Fiftyville')
       AND year = 2023
       AND month = 7
       AND day = 29
)

,CTE_PASSPORTS AS (
    SELECT *
      FROM passengers
     WHERE flight_id = (SELECT id
                          FROM CTE_FLIGHTS
                         WHERE date_time = (SELECT MIN(date_time)
                                             FROM CTE_FLIGHTS))
)

-- FIND WHO THE THIEF IS
,CTE_THIEF AS (
    SELECT P.*
      FROM people AS P
      JOIN CTE_PEOPLE_LEAVING_BAKERY AS PLB ON P.license_plate = PLB.license_plate
      JOIN bank_accounts AS BA ON P.id = BA.person_id
      JOIN CTE_WITHDREW_MONEY AS WM ON BA.account_number = WM.account_number
      JOIN CTE_PHONE_CALL AS PC ON P.phone_number = PC.caller
      JOIN CTE_PASSPORTS AS PP ON P.passport_number = PP.passport_number
)

-- FIND WHAT CITY THE THIEF ESCAPED TO
,CTE_CITY AS (
    SELECT DISTINCT A.*
      FROM airports AS A 
      JOIN CTE_FLIGHTS AS F ON A.id = F.destination_airport_id
      JOIN CTE_PASSPORTS AS PP ON F.id = PP.flight_id
)

-- FIND WHO THE THIEF'S ACCOMPLICE IS WHO HELPED THEM ESCAPE
,CTE_ACCOMPLICE AS (
    SELECT P.*
    FROM people AS P
    JOIN CTE_PHONE_CALL AS PC ON P.phone_number = PC.receiver
    JOIN CTE_THIEF AS T ON PC.caller = T.phone_number
)

,CTE_SOLUTION AS (
    SELECT 'Who is the thief?' AS QUESTION
           ,name AS ANSWER
      FROM CTE_THIEF

    UNION ALL

    SELECT 'What city the thief escaped to?' AS QUESTION
           ,city AS ANSWER
      FROM CTE_CITY
      
    UNION ALL

    SELECT 'Who the thief''s accomplice is who helped them escape?' AS QUESTION
           ,name AS ANSWER
      FROM CTE_ACCOMPLICE
)

SELECT *
  FROM CTE_SOLUTION;