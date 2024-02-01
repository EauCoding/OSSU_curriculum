SELECT bc_movies.title
FROM (
    SELECT *
    FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE people.name = 'Bradley Cooper'
) AS bc_movies
JOIN (
    SELECT *
    FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE people.name = 'Jennifer Lawrence'
) AS jl_movies ON bc_movies.movie_id = jl_movies.movie_id;