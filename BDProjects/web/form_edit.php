<html>
<body>
<h3> Insira um novo texto para a proposta de correcao:</h3>
<form action = "insert_edit.php" method ="post">
<p><input type="hidden" name="email"
value="<?=$_GET['email']?>"/></p>
<p><input type="hidden" name="nro"
value="<?=$_GET['nro']?>"/></p>
<p>Texto: <input type="text" name="texto" required/><p>

<p><input type="submit" name="submit" value="Submit"/></p>
<?php
echo("<p><a
href=\"correction.php\">Voltar a pagina anterior </a></p>\n");
?>
</form>
</body>
</html>