<html>
<body>
<?php
$nome = $_GET['nome'];
$id = $_GET['id'];
$host = "db.ist.utl.pt";
$user ="ist193607";
$port = 5432;
$password = "jtck9665";
$dbname = $user;

$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$sql = "SELECT * FROM incidencia 
WHERE item_id = $id;";

$result = pg_query($sql) or die('ERROR: ' . pg_last_error());

$num = pg_num_rows($result);

echo("<p>Tem $num anomalias associadas a este item, tem a certeza
que pretende remove-lo?</p>");

$result = pg_free_result($result) or die('ERROR:' . pg_last_error());

pg_close($connection);

echo("<p><a href=\"delete_item.php?nome=$nome&id=$id\">Sim</a>\n</p>");
echo("<p><a href=\"local.php\">Nao, pretendo regressar a pagina anterior</a>\n</p>");

?>
</body>
</html>