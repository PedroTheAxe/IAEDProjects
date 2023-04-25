<html>
<body>
<?php
$email = $_GET['email'];
$nro = $_GET['nro'];
$host = "db.ist.utl.pt";
$user ="ist193607";
$port = 5432;
$password = "1234";
$dbname = $user;

$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$sql = "DELETE
FROM proposta_de_correcao AS p
WHERE p.email = '$email' AND
p.nro = '$nro';";

$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<p> Proposta removida com sucesso</p>");
    
$result = pg_free_result($result) or die ('Error:' . pg_last_error());
pg_close($connection);

echo("<a href=\"correction.php\">Voltar a pagina anterior</a>\n");

?>
</body>
</html>