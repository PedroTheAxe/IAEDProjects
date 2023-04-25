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

$sql = "Select * from local_publico ORDER BY nome;";

$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Locais Publicos</th></tr>\n");
echo("<tr><td>Nome</td><td>Latitude</td><td>Longitude</td></tr>");


//Tabela dos Locais Publicos

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['nome']}</td>\n");
echo("<td>{$row['latitude']}</td>\n");
echo("<td>{$row['longitude']}</td>\n");
echo("</tr>\n");
}
echo("</table>\n");

$result = pg_free_result($result) or die('ERROR:' . pg_last_error());
pg_close($connection);
 
?>
<h3> Insira dois locais publicos </h3>
<form action = "list_area.php" method ="post">
<p>Local Publico 1: <input type="text" name="loc1" required/><p>
<p>Local Publico 2: <input type="text" name="loc2" required/><p>
<p><input type="submit" name="submit" value="Submit"/></p>
<?php
echo("<p><a
href=\"homepage.php\">Voltar a pagina anterior </a></p>\n");
?>
</form>
</body>
</html>