<html>
<body>
<?php
$host = "db.ist.utl.pt";
$user = "ist193607";
$port = 5432;
$password = "1234";
$dbname = $user;
$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$sql = "Select * from utilizador;";

$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<p><a
href=\"homepage.php\">Regressar a pagina inicial </a></p>\n");

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Utilizadores</th></tr>\n");


//Tabela dos Utilizadores

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['email']}</td>\n");
echo("</tr>\n");
}
echo("</table>\n");

$result = pg_free_result($result) or die('ERROR:' . pg_last_error());
pg_close($connection);
 
?>
</body>
</html>