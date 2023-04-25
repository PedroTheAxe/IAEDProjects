<html>
<body>
<h3> Insira uma nova anomalia do item: <?=$_GET['id']?></h3>
<form action = "validation_anomalia.php" method ="post">
<p><input type="hidden" name="id"
value="<?=$_GET['id']?>"/></p>
<p>Zona: <input type="text" name="zona" required/><p>
<p>Imagem: <input type="text" name="imagem" required/><p>
<p>Lingua: <input type="text" name="lingua" required/><p>
<p>Descricao: <input type="text" name="descricao" required/><p>
<p>Email: <input type="email" name="email" required/><p>
<p> Tipo de Anomalia:</p> 
    <input type="radio" name="anomaliaredacao" value="true"/>Redacao
    <input type="radio" name="anomaliaredacao" value="false"/>Traducao

<p><input type="submit" name="submit" value="Submit"/></p>
<?php
echo("<p><a
href=\"local.php\">Voltar a pagina anterior </a></p>\n");
?>
</form>
</body>
</html>