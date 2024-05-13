/* Clean data from favorites.db, eliminating leading and trailing whitespaces,
   standardizing capitalization, and fixing misspelled words and acronyms */

UPDATE shows SET title = 'Adventure Time' WHERE title LIKE '%adventure%';

UPDATE shows SET title = 'Anne with an E' WHERE title LIKE '%anne%';

UPDATE shows SET title = 'Archer' WHERE title LIKE '%archer%';

UPDATE shows SET title = 'Arrested Development' WHERE title LIKE '%arrested%';

UPDATE shows SET title = 'Arrow' WHERE title LIKE '%arrow%';

UPDATE shows SET title = 'Atlanta' WHERE title LIKE '%atlanta%';

UPDATE shows SET title = 'Avatar: The Last Airbender' WHERE title LIKE '%avatar%';

UPDATE shows SET title = 'Band of Brothers' WHERE title LIKE '%band%';

UPDATE shows SET title = 'Billions' WHERE title LIKE '%billions%';

UPDATE shows SET title = 'Black Mirror' WHERE title LIKE '%mirror%';

UPDATE shows SET title = 'Blue Mountain State' WHERE title LIKE '%mountain%';

UPDATE shows SET title = 'Breaking Bad' WHERE title LIKE '%breaking%';

UPDATE shows SET title = 'Brooklyn Nine-Nine' WHERE title LIKE '%brooklyn%' OR title LIKE '%99%';

UPDATE shows SET title = 'Cobra Kai' WHERE title LIKE '%cobra%';

UPDATE shows SET title = 'Community' WHERE title LIKE '%community%';

UPDATE shows SET title = 'Criminal Minds' WHERE title LIKE '%criminal%';

UPDATE shows SET title = 'Curb Your Enthusiasm' WHERE title LIKE '%curb%';

UPDATE shows SET title = 'Evacuate Earth' WHERE title LIKE '%evacuate%';

UPDATE shows SET title = 'Family Guy' WHERE title LIKE '%guy%';

UPDATE shows SET title = 'Friday Night Lights' WHERE title LIKE '%friday%';

UPDATE shows SET title = 'Friends' WHERE title LIKE '%friend%';

UPDATE shows SET title = 'Game of Thrones' WHERE title LIKE '%throne%' OR title LIKE '%got%';

UPDATE shows SET title = 'Gilmore Girls' WHERE title LIKE '%gilmore%';

UPDATE shows SET title = 'Good Omens' WHERE title LIKE '%omens%';

UPDATE shows SET title = 'Grace and Frankie' WHERE title LIKE '%grace%';

UPDATE shows SET title = "Grey's Anatomy" WHERE title LIKE '%anatomy%';

UPDATE shows SET title = 'Hannah Montana' WHERE title LIKE '%hannah%';

UPDATE shows SET title = 'How I Met Your Mother' WHERE title LIKE '%mother%';

UPDATE shows SET title = 'Hunter X Hunter' WHERE title LIKE '%hunter%';

UPDATE shows SET title = "It's Always Sunny in Philadelphia" WHERE title LIKE '%sunny%';

UPDATE shows SET title = 'Jeopardy' WHERE title LIKE '%jeopardy%';

UPDATE shows SET title = 'Last Week Tonight with John Oliver' WHERE title LIKE '%oliver%';

UPDATE shows SET title = 'Law & Order' WHERE title LIKE '%law%';

UPDATE shows SET title = 'Lost' WHERE title LIKE '%lost%';

UPDATE shows SET title = 'Mad Men' WHERE title LIKE '%mad%';

UPDATE shows SET title = 'Modern Family' WHERE title LIKE '%modern%';

UPDATE shows SET title = 'Money Heist' WHERE title LIKE '%money%';

UPDATE shows SET title = 'New Amsterdam' WHERE title LIKE '%amsterdam%';

-- Eliminate unwanted whitespaces, without interfering with 'Gilmore Girls'
UPDATE shows SET title = 'New Girl' WHERE title LIKE '%girl';
UPDATE shows SET title = 'New Girl' WHERE title LIKE 'girl%';

UPDATE shows SET title = 'Norsemen' WHERE title LIKE '%norsemen%';

UPDATE shows SET title = 'Parks and Recreation' WHERE title LIKE '%parks%';

UPDATE shows SET title = 'Peaky Blinders' WHERE title LIKE '%Blinder%';

UPDATE shows SET title = 'Reba' WHERE title LIKE '%reba%';

UPDATE shows SET title = 'Regular Show' WHERE title LIKE '%regular%';

UPDATE shows SET title = 'Saturday Night Live' WHERE title LIKE '%saturday%';

UPDATE shows SET title = 'Shark Tank' WHERE title LIKE '%shark%';

UPDATE shows SET title = 'Sherlock' WHERE title LIKE '%sherlock%';

UPDATE shows SET title = 'Silicon Valley' WHERE title LIKE '%silicon%';

UPDATE shows SET title = 'Six Flying Dragons' WHERE title LIKE '%dragon%';

UPDATE shows SET title = 'South Park' WHERE title LIKE '%south%';

UPDATE shows SET title = 'Squid Game' WHERE title LIKE '%squid%';

UPDATE shows SET title = 'Star Trek: The Next Generation' WHERE title LIKE '%trek%';

UPDATE shows SET title = 'Stranger Things' WHERE title LIKE '%strange%';

UPDATE shows SET title = 'Succession' WHERE title LIKE '%succession%';

UPDATE shows SET title = 'Supernatural' WHERE title LIKE '%supernatural%';

UPDATE shows SET title = 'Ted Lasso' WHERE title LIKE '%lasso%';

UPDATE shows SET title = 'The 100' WHERE title LIKE '%100%';

UPDATE shows SET title = 'The Bachelorette' WHERE title LIKE '%bachelorette%';

UPDATE shows SET title = 'The Big Bang Theory' WHERE title LIKE '%Bang%';

UPDATE shows SET title = 'The Crown' WHERE title LIKE '%crown%';

UPDATE shows SET title = "The Flash" WHERE title LIKE '%flash%';

UPDATE shows SET title = 'The Good Place' WHERE title LIKE '%place%';

UPDATE shows SET title = 'The Great British Baking Show' WHERE title LIKE '%baking%';

UPDATE shows SET title = 'The Haunting of Hill House' WHERE title LIKE '%haunting%';

UPDATE shows SET title = 'The Mentalist' WHERE title LIKE '%mentalist%';

UPDATE shows SET title = "The Office" WHERE title LIKE '%office%';

UPDATE shows SET title = 'The Originals' WHERE title LIKE '%original%';

UPDATE shows SET title = "The Queen's Gambit" WHERE title LIKE '%queen%';

UPDATE shows SET title = 'The Simpsons' WHERE title LIKE '%simpson%';

UPDATE shows SET title = 'The Sopranos' WHERE title LIKE '%soprano%';

UPDATE shows SET title = 'The Untamed' WHERE title LIKE '%untamed%';

UPDATE shows SET title = 'The West Wing' WHERE title LIKE '%west%';

UPDATE shows SET title = 'The Wire' WHERE title LIKE '%wire%';

UPDATE shows SET title = 'Top Gear' WHERE title LIKE '%gear%';

UPDATE shows SET title = 'Violet Evergarden' WHERE title LIKE '%violet%';

UPDATE shows SET title = 'WandaVision' WHERE title LIKE '%wanda%';

UPDATE shows SET title = 'White Collar' WHERE title LIKE '%collar%';

UPDATE shows SET title = 'Yellowstone' WHERE title LIKE '%yellowstone%';

-- Eliminate unwanted whitespaces, without interfering with shows with word 'you' in them
UPDATE shows SET title = 'You' WHERE title LIKE '%you';
UPDATE shows SET title = 'You' WHERE title LIKE 'you%';

SELECT title, COUNT(title) AS votes FROM shows GROUP BY title ORDER BY votes DESC, title;
