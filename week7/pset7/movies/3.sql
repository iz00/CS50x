-- Show the titles of all movies released on or after 2018, in alphabetical order
SELECT title
  FROM movies
 WHERE year > 2017
 ORDER BY title;
