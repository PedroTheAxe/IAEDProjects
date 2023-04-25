<html>
<body>
<?php

$host = "db.ist.utl.pt";
$user = "ist193607";
$port = 5432;
$password = "jtck9665";
$dbname = $user;
$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$lat=$_GET['lat'];
$lon=$_GET['lon'];
$descricao= $_GET['desc'];
$localizacao= $_GET['loc'];
$id = $_GET['id'];

$sql = "SELECT max(id) FROM item;";
$result = pg_query($sql) or die('ERROR: '.pg_last_error());
$i_maxcount=pg_fetch_result($result,0,0)+1;

$sql = "INSERT INTO item VALUES($1,$2,$3,$4,$5);";
$result = pg_prepare($connection,"my_query",$sql);
$result = pg_execute($connection,"my_query",array($i_maxcount,$descricao,$localizacao,$lat,$lon));

$sql = "INSERT INTO duplicado VALUES($1,$2);";
$result = pg_prepare($connection,"my_query4",$sql);
$result = pg_execute($connection,"my_query4",array($id,$i_maxcount));

$result = pg_free_result($result) or die('ERROR:' . pg_last_error());
echo("<p> Item duplicado com sucesso</p>");
pg_close($connection);
echo("<p><a
href=\"local.php\">Voltar a pagina anterior </a></p>\n");

?>
</body>
</html>