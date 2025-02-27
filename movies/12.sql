SELECT title
FROM movies
WHERE id IN (
    SELECT s1.movie_id
    FROM stars s1
    JOIN stars s2 ON s1.movie_id = s2.movie_id
    WHERE s1.person_id = (SELECT id FROM people WHERE name = 'Bradley Cooper')
    AND s2.person_id = (SELECT id FROM people WHERE name = 'Jennifer Lawrence')
);
