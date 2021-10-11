--list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred in
SELECT title from movies WHERE id IN
(SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Johnny Depp")
INTERSECT
SELECT movie_id FROM stars WHERE person_id = (SELECT id FROM people WHERE name = "Helena Bonham Carter"));
