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

$loc1 = $_POST['loc1'];
$loc2 = $_POST['loc2'];

$sql1 = "SELECT * FROM local_publico WHERE nome = $1;";
$result1 = pg_prepare($connection,"my_query1",$sql1);
$result1 = pg_execute($connection,"my_query1",array($loc1));

$sql2 = "SELECT * FROM local_publico WHERE nome = $1;";
$result2 = pg_prepare($connection,"my_query2",$sql2);
$result2 = pg_execute($connection,"my_query2",array($loc2));

if(pg_num_rows($result1) == 0 || pg_num_rows($result2) == 0 ) {

	echo("Inseriu locais publicos incorretos.\n");
	$result1 = pg_free_result($result1) or die('ERROR:' . pg_last_error());	
	$result2 = pg_free_result($result2) or die('ERROR:' . pg_last_error());
	pg_close($connection);
	echo("<p><a
	href=\"form_area.php\">Regressar a pagina anterior </a></p>\n");

} else {

	$valueloc1 = pg_fetch_assoc($result1);
	$valueloc2 = pg_fetch_assoc($result2);

	$sql3 = "SELECT a.id AS a_id, a.zona AS a_zona, a.lingua AS a_lingua, a.ts AS a_ts, 
			a.descricao AS a_descricao, it.latitude AS i_latitude, it.longitude AS i_longitude 
			FROM anomalia a JOIN incidencia i ON a.id = i.anomalia_id
			JOIN item it ON i.item_id = it.id;";
	$result3 = pg_query($sql3) or die('ERROR: '.pg_last_error());

	echo("<table border=\"1\" cellspacing=\"5\">\n");
	echo("<tr><th>Anomalias</th></tr>\n");
	echo("<tr><td>Id</td><td>Zona</td><td>Lingua</td><td>Timestamp</td><td>Descricao</td></tr>");

	while($row = pg_fetch_assoc($result3)){

		if(($row['i_latitude'] >= $valueloc1['latitude'] && $row['i_latitude'] <= $valueloc2['latitude'] && $row['i_longitude'] >= $valueloc1['longitude'] && $row['i_longitude'] <= $valueloc2['longitude'] ||
			($row['i_latitude'] >= $valueloc1['latitude'] && $row['i_latitude'] <= $valueloc2['latitude'] && $row['i_longitude'] <= $valueloc1['longitude'] && $row['i_longitude'] >= $valueloc2['longitude']) ||
			($row['i_latitude'] <= $valueloc1['latitude'] && $row['i_latitude'] >= $valueloc2['latitude'] && $row['i_longitude'] >= $valueloc1['longitude'] && $row['i_longitude'] <= $valueloc2['longitude']) ||
			($row['i_latitude'] <= $valueloc1['latitude']&& $row['i_latitude'] >= $valueloc2['latitude'] && $row['i_longitude'] <= $valueloc1['longitude'] && $row['i_longitude'] >= $valueloc2['longitude']))) { 
			echo("<tr>\n");
			echo("<td>{$row['a_id']}</td>\n");
			echo("<td>{$row['a_zona']}</td>\n");
			echo("<td>{$row['a_lingua']}</td>\n");
			echo("<td>{$row['a_ts']}</td>\n");
			echo("<td>{$row['a_descricao']}</td>\n");
			echo("</tr>\n");
		}
			
	}
	echo("</table>\n");
}

echo("<p><a
href=\"homepage.php\">Regressar a pagina inicial </a></p>\n");

$result1 = pg_free_result($result1) or die('ERROR:' . pg_last_error());	
$result2 = pg_free_result($result2) or die('ERROR:' . pg_last_error());
$result3 = pg_free_result($result3) or die('ERROR:' . pg_last_error());	
pg_close($connection);
 
?>
</body>
</html>