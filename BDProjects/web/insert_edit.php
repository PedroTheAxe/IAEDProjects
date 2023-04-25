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


$texto=$_POST['texto'];
$email=$_POST['email'];
$nro=$_POST['nro'];

$date= new DateTime();
$ts = $date->format('Y-m-d H:i:s') . "\n";
$data_hora = $ts ;

$sql = "UPDATE proposta_de_correcao SET texto = $4,data_hora = $3 WHERE email=$1 AND nro=$2;";
$result = pg_prepare($connection,"my_query",$sql);
$result = pg_execute($connection,"my_query",array($email,$nro,$data_hora,$texto));



$result = pg_free_result($result) or die('ERROR:' . pg_last_error());
echo("<p> Proposta editada com sucesso</p>");

pg_close($connection);


echo("<p><a
href=\"correction.php\">Voltar a pagina anterior </a></p>\n");

?>
</body>
</html>