<html>
<body>
<?php
$nome = $_GET['nome'];
$aid = $_GET['aid'];
$itid = $_GET['itid'];
$host = "db.ist.utl.pt";
$user ="ist193607";
$port = 5432;
$password = "jtck9665";
$dbname = $user;

$connection = pg_connect("host=$host port=$port user=$user password=$password dbname=$dbname")
or die(pg_last_error());

$sql = "SELECT * FROM item it
NATURAL JOIN local_publico
JOIN incidencia i ON i.item_id = it.id
WHERE nome=$nome;";

$result = pg_query($sql) or die('ERROR: ' . pg_last_error());

if(pg_num_rows($result) == 1){
    $sql = "DELETE
    FROM proposta_de_correcao AS p
    USING 
        local_publico AS l,
        item AS it,
        incidencia AS i,
        correcao AS c
    WHERE p.nro=c.nro
    AND   c.anomalia_id=i.anomalia_id
    AND   i.item_id=it.id
    AND   it.latitude=l.latitude
    AND   it.longitude=l.longitude
    AND   l.nome=$nome;";
    
    $sql .="DELETE
    FROM anomalia AS a
    USING
        local_publico AS l,
        item AS it,
        incidencia AS i
    WHERE a.id=i.anomalia_id
    AND   i.item_id=it.id
    AND   it.latitude=l.latitude
    AND   it.longitude=l.longitude
    AND   l.nome=$nome;";

    $sql .="DELETE
    FROM local_publico AS l
    WHERE l.nome = $nome;";

    $result = pg_query($sql) or die('ERROR: ' . pg_last_error());
    echo "<p>Anomalia Removida com sucesso.</p>";
}
else{
    $sql= "DELETE
    FROM proposta_de_correcao AS p
    USING
        correcao AS c
    WHERE p.nro = c.nro
    AND   c.anomalia_id = $aid;";

    $sql.="DELETE
    FROM anomalia AS a
    WHERE id = $aid;";

    $sql.= "DELETE
    FROM incidencia
    where anomalia_id = $aid;";

    $result = pg_query($sql) or die('ERROR: ' . pg_last_error());
    echo "<p>Anomalia Removida com sucesso.</p>";
}
$result = pg_free_result($result) or die ('Error:' . pg_last_error());
pg_close($connection);

echo("<a href=\"local.php\">Voltar a pagina anterior</a>\n");

?>
</body>
</html>