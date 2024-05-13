-- Show the titles of all movies that both Bradley Cooper and Jennifer Lawrence starred in
SELECT title
  FROM movies
  JOIN stars
    ON movies.id = stars.movie_id
  JOIN people
    ON stars.person_id = people.id
 WHERE name IN
       ('Bradley Cooper', 'Jennifer Lawrence')
 GROUP BY title
HAVING COUNT(title) > 1;
