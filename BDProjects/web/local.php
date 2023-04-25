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

$sql = "Select * from local_publico;";

$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<p><a
href=\"homepage.php\">Regressar a pagina inicial </a></p>\n");

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Locais Publicos</th></tr>\n");


//Tabela dos Locais Publicos

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['nome']}</td>\n");
echo("<td><a
href=\"remove_local.php?nome='{$row['nome']}'\">Remover  
este local publico </a></td>\n");
echo("<td><a
href=\"form_item.php?nome={$row['nome']}&lat={$row['latitude']}&lon={$row['longitude']}\">Inserir novo item neste local</a></td>\n");

echo("</tr>\n");
}
echo("</table>\n");
echo("<p>\n\n</p>");


//Tabela dos items

$sql ="SELECT *
FROM local_publico natural join item
ORDER BY id;";

$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Items</th></tr>\n");
echo("<tr><td>Nome</td><td>Item_ID</td><td>Descricao</td><td>Localizacao</td></tr>");

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['nome']}</td>\n");
echo("<td>{$row['id']}</td>\n");
echo("<td>{$row['descricao']}</td>\n");
echo("<td>{$row['localizacao']}</td>\n");
echo("<td><a
href=\"remove_item.php?nome='{$row['nome']}'&id={$row['id']}\">Remover Item </a></td>\n");
echo("<td><a
href=\"form_anomalia.php?id={$row['id']}\">Inserir uma nova anomalia com este item </a></td>\n");
echo("<td><a
href=\"duplicado_item.php?desc={$row['descricao']}&loc={$row['localizacao']}&lat={$row['latitude']}&lon={$row['longitude']}&id={$row['id']}\">Duplicar este item </a></td>\n");
echo("</tr>\n");
}

echo("</table>\n");
echo("<p>\n\n</p>");

//Tabela das anomalias

$sql ="SELECT l.nome as nome,it.id as itid,it.descricao as itdescricao,a.id as aid,a.zona as azona,at.zona2 as azona2,a.lingua as alingua,at.lingua2 as alingua2,a.ts as ats,a.descricao as adescricao
FROM anomalia a LEFT OUTER JOIN anomalia_traducao at ON a.id=at.id JOIN incidencia i ON a.id = i.anomalia_id
JOIN item it ON it.id=i.item_id
NATURAL JOIN local_publico l
ORDER BY a.id;";

$result = pg_query($sql) or die('ERROR: '.pg_last_error());

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Anomalias</th></tr>\n");
echo("<tr><td>Nome</td><td>Item_ID</td><td>Item_Descricao</td><td>Anomalia_ID</td><td>Anomalia_Zona</td><td>Anomalia_Zona2</td><td>Anomalia_Lingua</td><td>Anomalia_Lingua2</td>
<td>Anomalia_Timestamp</td><td>Anomalia_Descricao</td></tr>");

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['nome']}</td>\n");
echo("<td>{$row['itid']}</td>\n");
echo("<td>{$row['itdescricao']}</td>\n");
echo("<td>{$row['aid']}</td>\n");
echo("<td>{$row['azona']}</td>\n");
echo("<td>{$row['azona2']}</td>\n");
echo("<td>{$row['alingua']}</td>\n");
echo("<td>{$row['alingua2']}</td>\n");
echo("<td>{$row['ats']}</td>\n");
echo("<td>{$row['adescricao']}</td>\n");
echo("<td><a
href=\"remove_anomalia.php?nome='{$row['nome']}'&aid={$row['aid']}&itid={$row['itid']}\">Remover Anomalia </a></td>\n");
}

echo("</table>\n");
echo("<p>\n\n</p>");



echo("<a href=\"form_incidencia.php\">Registar uma nova incidencia</a>\n");


$result = pg_free_result($result) or die('ERROR:' . pg_last_error());
pg_close($connection);
 
?>
</body>
</html>