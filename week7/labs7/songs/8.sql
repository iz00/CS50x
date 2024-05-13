-- Show the names of the songs that feature other artists, which contain 'feat.' in their names
SELECT name
  FROM songs
 WHERE name LIKE '%feat.%';
