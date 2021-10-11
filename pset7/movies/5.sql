--list the titles and release years of all Harry Potter mobies, in chronological order
SELECT title, year FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year;
