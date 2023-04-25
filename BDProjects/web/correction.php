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

$sql = "SELECT p.email as p_email,p.nro as p_nro,p.data_hora as p_data_hora,
c.anomalia_id as p_anomalia_id, a.descricao as a_descricao, p.texto as p_texto
FROM proposta_de_correcao p NATURAL JOIN correcao c
JOIN anomalia a ON a.id=c.anomalia_id;";

$result = pg_query($sql) or die('ERROR '.pg_last_error());

echo("<p><a
href=\"homepage.php\">Regressar a pagina inicial </a></p>\n");

echo("<table border=\"1\" cellspacing=\"5\">\n");
echo("<tr><th>Proposta de Correcao</th></tr>\n");
echo("<tr><td>Email_Proposta</td><td>Numero_Proposta</td>
<td>Data_Hora</td><td>Anomalia_ID</td><td>Descricao_Anomalia</td></tr>");

//Tabela de Propostas de Correcao

while($row = pg_fetch_assoc($result))
{
echo("<tr>\n");
echo("<td>{$row['p_email']}</td>\n");
echo("<td>{$row['p_nro']}</td>\n");
echo("<td>{$row['p_data_hora']}</td>\n");
echo("<td>{$row['p_anomalia_id']}</td>\n");
echo("<td>{$row['a_descricao']}</td>\n");
echo("<td>{$row['p_texto']}</td>\n");
echo("<td><a
href=\"remove_proposta.php?email={$row['p_email']}&nro={$row['p_nro']}\">Remover Proposta </a></td>\n");

echo("<td><a
href=\"form_edit.php?email={$row['p_email']}&nro={$row['p_nro']}\">Editar Proposta </a></td>\n");
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
href=\"form_proposta.php?aid={$row['aid']}\">Registar proposta de correcao para esta anomalia </a></td>\n");
}

echo("</table>\n");
echo("<p>\n\n</p>");


$result = pg_free_result($result) or die('ERROR:' . pg_last_error());
pg_close($connection);
 
?>
</body>
</html>