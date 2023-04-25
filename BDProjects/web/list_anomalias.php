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
$x=$_POST['x'];
$y=$_POST['y'];
$dx=$_POST['dx'];
$dy=$_POST['dy'];
$date= new DateTime();
$ts = $date->format('Y-m-d H:i:s');
$date = $date->modify('-3 month');
$ts2 = $date->format('Y-m-d H:i:s');
$realtimestamp ="'" . $ts . "'";
$realtimestamp2 ="'" . $ts2 . "'";


$sql = "SELECT a.id AS aid,a.zona AS azona,a.lingua AS alingua,a.ts AS ats,a.descricao AS adescricao
FROM anomalia a JOIN incidencia i ON a.id = i.anomalia_id
JOIN item it ON it.id=i.item_id
WHERE a.ts BETWEEN $realtimestamp2 AND $realtimestamp
AND it.latitude BETWEEN ($x-$dx) AND ($x+$dx)
AND it.longitude BETWEEN ($y-$dy) AND ($y + $dy);";


$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Resposta</th></tr>\n");
echo("<tr><td>Anomalia_ID</td><td>Anomalia_Zona</td>
<td>Anomalia_Lingua</td><td>Timestamp</td><td>Anomalia_Descricao</td></tr>");


//Tabela dos Utilizadores

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['aid']}</td>\n");
echo("<td>{$row['azona']}</td>\n");
echo("<td>{$row['alingua']}</td>\n");
echo("<td>{$row['ats']}</td>\n");
echo("<td>{$row['adescricao']}</td>\n");
echo("</tr>\n");
}
echo("</table>\n");

$result = pg_free_result($result) or die('ERROR:' . pg_last_error());


pg_close($connection);
echo("<p><a
href=\"homepage.php\">Regressar a pagina inicial </a></p>\n");
 
?>
</body>
</html>