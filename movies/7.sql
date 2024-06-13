SELECT title, rating
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movie_id IN (
    SELECT id
    FROM movies
    WHERE year = 2010
)
ORDER BY rating DESC, title ASC;
