SELECT AVG(rating)
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movie_id IN (
    SELECT id
    FROM movies
    WHERE year = 2012
);
