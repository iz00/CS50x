-- Show the titles and the ratings of all movies released in 2010, ordered first by highest rating, then alphabetically by title
SELECT title, rating
  FROM movies
  JOIN ratings
    ON movies.id = ratings.movie_id
 WHERE year = 2010
 ORDER BY rating DESC, title;
