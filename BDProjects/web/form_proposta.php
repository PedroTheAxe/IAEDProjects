<html>
<body>
<h3> Insira uma nova proposta de correcao para a anomalia: <?=$_GET['aid']?></h3>
<form action = "insert_proposta.php" method ="post">
<p><input type="hidden" name="aid"
value="<?=$_GET['aid']?>"/></p>
<p>Email: <input type="email" name="email" required/><p>
<p>Texto: <input type="text" name="texto" required/><p>

<p><input type="submit" name="submit" value="Submit"/></p>
<?php
echo("<p><a
href=\"correction.php\">Voltar a pagina anterior </a></p>\n");
?>
</form>
</body>
</html>