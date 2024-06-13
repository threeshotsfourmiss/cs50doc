SELECT title
FROM movies
WHERE movies.id IN (
    SELECT movies.id
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people on stars.person_id = people.id
    WHERE name = "Bradley Cooper"
) AND movies.id IN (
    SELECT movies.id
    FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people on stars.person_id = people.id
    WHERE name = "Jennifer Lawrence"
);
