--list the names of all people who starred in a movie released in 2004, ordered by birth year.
--There should be no repeats (in the case that actors starred in more than one movie that year)
SELECT name FROM people WHERE id IN (SELECT DISTINCT person_id FROM stars WHERE movie_id IN 
(SELECT id FROM movies WHERE year = 2004)) ORDER BY birth;
