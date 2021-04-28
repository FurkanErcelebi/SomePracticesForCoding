/*
Enter your query here.
Please append a semicolon ";" at the end of the query and enter your query in a single line to avoid error.
*/
select sum(lat_n)
from station
where lat_n > 38.7880
    and lat_n < 137.2345
order by lat_n;
