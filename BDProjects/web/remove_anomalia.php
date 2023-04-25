<html>
<body>
<?php
$nome = $_GET['nome'];
$aid = $_GET['aid'];
$itid = $_GET['itid'];

echo("<p>Tem a certeza que pretende remover esta anomalia?</p>");

echo("<p><a href=\"delete_anomalia.php?nome=$nome&aid=$aid&itid=$itid\">Sim</a>\n</p>");
echo("<p><a href=\"local.php\">Nao, pretendo regressar a pagina anterior</a>\n</p>");

?>
</body>
</html>