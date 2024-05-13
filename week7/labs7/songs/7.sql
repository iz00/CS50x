-- Show the average energy of the songs by Drake, using implicit JOIN
SELECT AVG(energy)
  FROM songs, artists
 WHERE songs.artist_id = artists.id
   AND artists.name = 'Drake';
