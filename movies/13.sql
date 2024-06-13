SELECT name
FROM people
WHERE people.id IN (
    SELECT people.id
    FROM people
    JOIN stars ON people.id = stars.person_id
    WHERE people.id IN (
        SELECT id
        FROM people
        WHERE name = "Kevin Bacon"
    )

) AND people.id NOT IN (
    SELECT people.id
    FROM people
    WHERE name = "Kevin Bacon"
);
