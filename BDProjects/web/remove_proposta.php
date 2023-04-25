<html>
<body>
<?php
$email = $_GET['email'];
$nro = $_GET['nro'];

echo("<p>Tem a certeza que pretende remover esta proposta?</p>");
echo("<p><a href=\"delete_proposta.php?email=$email&nro=$nro\">Sim</a>\n</p>");
echo("<p><a href=\"correction.php\">Nao, pretendo regressar a pagina anterior</a>\n</p>");

?>
</body>
</html>