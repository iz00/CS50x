-- Show the number of movies with a rating of 10
SELECT COUNT(*) AS count_max_rating
  FROM ratings
 WHERE rating = 10
