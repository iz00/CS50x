-- Show the titles of the 5 highest ranking movies that Chadwick Boseman starred in
SELECT title
  FROM people, stars, movies, ratings
 WHERE people.id = stars.person_id
   AND stars.movie_id = movies.id
   AND movies.id = ratings.movie_id
   AND name = 'Chadwick Boseman'
 ORDER BY rating DESC
 LIMIT 5;
