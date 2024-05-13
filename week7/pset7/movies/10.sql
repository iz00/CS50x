-- Show the names of all people who directed a movie with a rating of at least 9
SELECT DISTINCT(name) AS name
  FROM people
  JOIN directors
    ON people.id = directors.person_id
  JOIN movies
    ON directors.movie_id = movies.id
  JOIN ratings
    ON movies.id = ratings.movie_id
 WHERE rating >= 9;
